/*
  Copyright (c) 2012 Red Hat, Inc. <http://www.redhat.com>
  This file is part of GlusterFS.

  This file is licensed to you under your choice of the GNU Lesser
  General Public License, version 3 or any later version (LGPLv3 or
  later), or the GNU General Public License, version 2 (GPLv2), in all
  cases as published by the Free Software Foundation.
*/

#include <sys/poll.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "../debug/debug.h"
#include "event.h"


#ifdef HAVE_SYS_EPOLL_H
#include <sys/epoll.h>

//����fd��event_pool�е�����
static int
__event_getindex (struct event_pool *event_pool, int fd, int idx)
{
        int  ret = -1;
        int  i = 0;

        GF_VALIDATE_OR_GOTO ("event", event_pool, out);

        if (idx > -1 && idx < event_pool->used) {
                if (event_pool->reg[idx].fd == fd)
                        ret = idx;
        }

        for (i=0; ret == -1 && i<event_pool->used; i++) {
                if (event_pool->reg[i].fd == fd) {
                        ret = i;
                        break;
                }
        }

out:
        return ret;
}

//�¼����½�����
static struct event_pool *
event_pool_new_epoll (int count)
{
        struct event_pool *event_pool = NULL;
        int                epfd = -1;

        event_pool = calloc (1, sizeof (*event_pool));

        if (!event_pool)
                goto out;
        // �صĴ�С����������Ŀ ����������
        event_pool->count = count;
        //�¼�ע�ᣬcount������������ڴ�
        event_pool->reg = calloc (event_pool->count,
                                     sizeof (*event_pool->reg));

        if (!event_pool->reg) {
                free (event_pool);
                event_pool = NULL;
                goto out;
        }

        // ����һ��epoll�ľ��,�Դ�linux2.6.8֮��count�����Ǳ����Ե�,��ռ��һ��fd
        // ls -alh  /proc/32765/fd/
        // lrwx------. 1 root root 64 Aug 19 20:04 4 -> anon_inode:[eventpoll]
        epfd = epoll_create (count);

        if (epfd == -1) {
                LOG_PRINT(D_LOG_ERR, "epoll fd creation failed (%s)",
                        strerror (errno));
                free (event_pool->reg);
                free (event_pool);
                event_pool = NULL;
                goto out;
        }

        // ����epoll��fd������epoll�������õ�
        event_pool->fd = epfd;
        
        event_pool->count = count;

        pthread_mutex_init (&event_pool->mutex, NULL);
        pthread_cond_init (&event_pool->cond, NULL);

out:
        return event_pool;
}

/*�¼�ע�ắ��*/
int
event_register_epoll (struct event_pool *event_pool, int fd,
                      event_handler_t handler,
                      void *data, int poll_in, int poll_out)
{
        int                 idx = -1;
        int                 ret = -1;
        struct epoll_event  epoll_event = {0, };
        struct event_data  *ev_data = (void *)&epoll_event.data;


        GF_VALIDATE_OR_GOTO ("event", event_pool, out);

        pthread_mutex_lock (&event_pool->mutex);
        {
                //��������������ʹ�ü�����������صĴ�С
                if (event_pool->count == event_pool->used) {
                        event_pool->count *= 2;

                        event_pool->reg = realloc (event_pool->reg,
                                                      event_pool->count *
                                                      sizeof (*event_pool->reg));

                        if (!event_pool->reg) {
                                LOG_PRINT(D_LOG_ERR,
                                        "event registry re-allocation failed");
                                goto unlock;
                        }
                }

                idx = event_pool->used;
                event_pool->used++;

                event_pool->reg[idx].fd = fd;
                /*
                   ��Ե����: ������û�а�����¼���Ӧ���׽��ֻ����������꣬
                   ������׽�����û���µ��¼��ٴε���ʱ����ETģʽ�����޷��ٴδ�
                   epoll_wait�����л�ȡ����¼��� 
                */
                event_pool->reg[idx].events = EPOLLET ;//��Ե����(Edge Triggered)ģʽ  EPOLLPRI; //��ʾ��Ӧ���ļ��������н��������ݿɶ�
                //����Ŀ��ƺ�����˽�������Ǳ������Լ�ʵ�ֵ�reg�У�������epoll�Դ��� epoll_data
                event_pool->reg[idx].handler = handler; //���ƺ���
                event_pool->reg[idx].data = data; // ˽������

                switch (poll_in) {
                case 1:
                        //EPOLLINλ ��1
                        event_pool->reg[idx].events |= EPOLLIN;
                        break;
                case 0:
                        //EPOLLINλ ����
                        event_pool->reg[idx].events &= ~EPOLLIN;
                        break;
                case -1:
                        /* do nothing */
                        break;
                default:
                        LOG_PRINT(D_LOG_ERR,
                                "invalid poll_in value %d", poll_in);
                        break;
                }

                switch (poll_out) {
                case 1:
                        event_pool->reg[idx].events |= EPOLLOUT;
                        break;
                case 0:
                        event_pool->reg[idx].events &= ~EPOLLOUT;
                        break;
                case -1:
                        /* do nothing */
                        break;
                default:
                        LOG_PRINT(D_LOG_ERR,
                                "invalid poll_out value %d", poll_out);
                        break;
                }

                event_pool->changed = 1;

                // .events ��һЩ����
                epoll_event.events = event_pool->reg[idx].events;
                /*
                    typedef union epoll_data {  
                        void *ptr;  
                        int fd;  
                        __uint32_t u32;  
                        __uint64_t u64;  
                    } epoll_data_t;  
                     //����Ȥ���¼��ͱ��������¼�  
                    struct epoll_event {  
                        __uint32_t events; // Epoll events  
                        epoll_data_t data; // User data variable   
                    };  
                */

                // �� epoll_data_t dataռ�õ�64λ�ռ�����fd��inx,���Ҫ�Ÿ�������Ҫ
                // �Լ�����ռ䣬data��ſռ�ĵ�ַ���������ǰ����ݷ���reg��
                ev_data->fd = fd;
                ev_data->idx = idx;

                /*
                epoll���¼�ע�ắ��������ͬ��select()���ڼ����¼�ʱ�����ں�Ҫ����
                ʲô���͵��¼���������������ע��Ҫ�������¼����͡�
                ��һ��������epoll_create()�ķ���ֵ��
                �ڶ���������ʾ������������������ʾ��
                EPOLL_CTL_ADD��ע���µ�fd��epfd�У�
                EPOLL_CTL_MOD���޸��Ѿ�ע���fd�ļ����¼���
                EPOLL_CTL_DEL����epfd��ɾ��һ��fd��
                 
                ��������������Ҫ������fd��
                ���ĸ������Ǹ����ں���Ҫ����ʲô��*/
                ret = epoll_ctl (event_pool->fd, EPOLL_CTL_ADD, fd,
                                 &epoll_event);

                if (ret == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "failed to add fd(=%d) to epoll fd(=%d) (%s)",
                                fd, event_pool->fd, strerror (errno));
                        goto unlock;
                }

                //�����ѵȴ��������������߳�
                pthread_cond_broadcast (&event_pool->cond);
        }
unlock:
        pthread_mutex_unlock (&event_pool->mutex);

out:
        return ret;
}

/*�¼�ע���Ƴ�*/
static int
event_unregister_epoll (struct event_pool *event_pool, int fd, int idx_hint)
{
        int  idx = -1;
        int  ret = -1;

        struct epoll_event epoll_event = {0, };
        struct event_data *ev_data = (void *)&epoll_event.data;
        int                lastidx = -1;

        GF_VALIDATE_OR_GOTO ("event", event_pool, out);

        pthread_mutex_lock (&event_pool->mutex);
        {
                // idx���ܻ��(�����棬�޸�idx����ʧ����?)����������Ҫ�鿴һ��
                idx = __event_getindex (event_pool, fd, idx_hint);

                if (idx == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "index not found for fd=%d (idx_hint=%d)",
                                fd, idx_hint);
                        errno = ENOENT;
                        goto unlock;
                }
                
                //��epfd��ɾ��һ��fd��
                ret = epoll_ctl (event_pool->fd, EPOLL_CTL_DEL, fd, NULL);

                /* if ret is -1, this array member should never be accessed */
                /* if it is 0, the array member might be used by idx_cache
                 * in which case the member should not be accessed till
                 * it is reallocated
                 */

                event_pool->reg[idx].fd = -1;

                if (ret == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "fail to del fd(=%d) from epoll fd(=%d) (%s)",
                                fd, event_pool->fd, strerror (errno));
                        goto unlock;
                }

                //��������һ����ֱ��ɾ����used��һ
                lastidx = event_pool->used - 1;
                if (lastidx == idx) {
                        event_pool->used--;
                        goto unlock;
                }

                //�������һ���������һ���ƶ����ո�ɾ����λ��
                epoll_event.events = event_pool->reg[lastidx].events;
                ev_data->fd = event_pool->reg[lastidx].fd;
                ev_data->idx = idx; //�޸�idx

                //�޸��Ѿ�ע���fd�ļ����¼�, �޸���idx
                ret = epoll_ctl (event_pool->fd, EPOLL_CTL_MOD, ev_data->fd,
                                 &epoll_event);
                if (ret == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "fail to modify fd(=%d) index %d to %d (%s)",
                                ev_data->fd, event_pool->used, idx,
                                strerror (errno));
                        goto unlock;
                }

                /* just replace the unregistered idx by last one */
                event_pool->reg[idx] = event_pool->reg[lastidx];
                event_pool->used--;
        }
unlock:
        pthread_mutex_unlock (&event_pool->mutex);

out:
        return ret;
}


/*�޸��Ѿ�ע���fd�ļ����¼�������*/
static int
event_select_on_epoll (struct event_pool *event_pool, int fd, int idx_hint,
                       int poll_in, int poll_out)
{
        int idx = -1;
        int ret = -1;

        struct epoll_event epoll_event = {0, };
        struct event_data *ev_data = (void *)&epoll_event.data;


        GF_VALIDATE_OR_GOTO ("event", event_pool, out);

        pthread_mutex_lock (&event_pool->mutex);
        {
                idx = __event_getindex (event_pool, fd, idx_hint);

                if (idx == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "index not found for fd=%d (idx_hint=%d)",
                                fd, idx_hint);
                        errno = ENOENT;
                        goto unlock;
                }

                switch (poll_in) {
                case 1:
                        event_pool->reg[idx].events |= EPOLLIN;
                        break;
                case 0:
                        event_pool->reg[idx].events &= ~EPOLLIN;
                        break;
                case -1:
                        /* do nothing */
                        break;
                default:
                        LOG_PRINT(D_LOG_ERR,
                                "invalid poll_in value %d", poll_in);
                        break;
                }

                switch (poll_out) {
                case 1:
                        event_pool->reg[idx].events |= EPOLLOUT;
                        break;
                case 0:
                        event_pool->reg[idx].events &= ~EPOLLOUT;
                        break;
                case -1:
                        /* do nothing */
                        break;
                default:
                        LOG_PRINT(D_LOG_ERR,
                                "invalid poll_out value %d", poll_out);
                        break;
                }

                epoll_event.events = event_pool->reg[idx].events;
                ev_data->fd = fd;
                ev_data->idx = idx;

                ret = epoll_ctl (event_pool->fd, EPOLL_CTL_MOD, fd,
                                 &epoll_event);
                if (ret == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "failed to modify fd(=%d) events to %d",
                                fd, epoll_event.events);
                }
        }
unlock:
        pthread_mutex_unlock (&event_pool->mutex);

out:
        return ret;
}

//�ַ��¼�����
static int
event_dispatch_epoll_handler (struct event_pool *event_pool,
                              struct epoll_event *events, int i)
{
        struct event_data  *event_data = NULL;
        event_handler_t     handler = NULL;
        void               *data = NULL;
        int                 idx = -1;
        int                 ret = -1;


        event_data = (void *)&events[i].data;
        handler = NULL;
        data = NULL;

        pthread_mutex_lock (&event_pool->mutex);
        {
                idx = __event_getindex (event_pool, event_data->fd,
                                        event_data->idx);

                if (idx == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "index not found for fd(=%d) (idx_hint=%d)",
                                event_data->fd, event_data->idx);
                        goto unlock;
                }
                //������
                handler = event_pool->reg[idx].handler;
                //˽������
                data = event_pool->reg[idx].data;
        }
unlock:
        pthread_mutex_unlock (&event_pool->mutex);

        //socket_event_handler
        //���ô�����
        if (handler)
                ret = handler (event_data->fd, event_data->idx, data,
                               (events[i].events & (EPOLLIN|EPOLLPRI)),
                               (events[i].events & (EPOLLOUT)),
                               (events[i].events & (EPOLLERR|EPOLLHUP)));
        return ret;
}


static int
event_dispatch_epoll (struct event_pool *event_pool)
{
        struct epoll_event *events = NULL;
        int                 size = 0;
        int                 i = 0;
        int                 ret = -1;

        GF_VALIDATE_OR_GOTO ("event", event_pool, out);

        while (1) {
                pthread_mutex_lock (&event_pool->mutex);
                {
                        while (event_pool->used == 0)
                                //�����ȴ������ĸı䣬event_resister_epoll�����л���
                                pthread_cond_wait (&event_pool->cond,
                                                   &event_pool->mutex);

                        //��μ��������¼����������·��仺���С
                        if (event_pool->used > event_pool->evcache_size) {
                                free (event_pool->evcache);

                                event_pool->evcache = events = NULL;

                                event_pool->evcache_size =
                                        event_pool->used + 256;

                                events = calloc (event_pool->evcache_size,
                                                    sizeof (struct epoll_event));
                                if (!events)
                                        break;

                                event_pool->evcache = events;
                        }
                }
                pthread_mutex_unlock (&event_pool->mutex);

                //���������ȴ��¼��Ĳ�����������Ҫ������¼���Ŀ
                /*
                �ռ���epoll��ص��¼����Ѿ����͵��¼�������events�Ƿ���õ�epoll_event
                �ṹ�����飬epoll����ѷ������¼���ֵ��events�����У�events�������ǿ�ָ�룬
                �ں�ֻ��������ݸ��Ƶ����events�����У�����ȥ�����������û�̬�з����ڴ棩��
                maxevents��֮�ں����events�ж����� maxevents��ֵ���ܴ��ڴ���epoll_create()ʱ��size��
                ����timeout�ǳ�ʱʱ�䣨���룬0���������أ�-1����ȷ����Ҳ��˵��˵��������������
                ����������óɹ������ض�ӦI/O����׼���õ��ļ���������Ŀ���緵��0��ʾ�ѳ�ʱ��
                */
                ret = epoll_wait (event_pool->fd, event_pool->evcache,
                                  event_pool->evcache_size, -1);

                if (ret == 0)
                        /* timeout */
                        continue;

                if (ret == -1 && errno == EINTR)
                        /* sys call */
                        continue;

                size = ret;

                for (i = 0; i < size; i++) {
                        if (!events || !events[i].events)
                                continue;
                        //EPOLLOUT�¼�ֻ��������ʱ����һ�Σ���ʾ��д������ʱ����Ҫ����������Ҫ��׼��������������
                        //1.ĳ��write��д���˷��ͻ����������ش�����ΪEAGAIN��
                        //2.�Զ˶�ȡ��һЩ���ݣ������¿�д�ˣ���ʱ�ᴥ��EPOLLOUT
                        ret = event_dispatch_epoll_handler (event_pool,
                                                            events, i);
                }
        }

out:
        return ret;
}


struct event_ops event_ops_epoll = {
        .new              = event_pool_new_epoll,
        .event_register   = event_register_epoll,
        .event_select_on  = event_select_on_epoll,
        .event_unregister = event_unregister_epoll,
        .event_dispatch   = event_dispatch_epoll
};

#endif
