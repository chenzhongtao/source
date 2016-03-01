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

//查找fd在event_pool中的索引
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

//事件池新建函数
static struct event_pool *
event_pool_new_epoll (int count)
{
        struct event_pool *event_pool = NULL;
        int                epfd = -1;

        event_pool = calloc (1, sizeof (*event_pool));

        if (!event_pool)
                goto out;
        // 池的大小，监听的数目 ，可以增加
        event_pool->count = count;
        //事件注册，count个，这里分配内存
        event_pool->reg = calloc (event_pool->count,
                                     sizeof (*event_pool->reg));

        if (!event_pool->reg) {
                free (event_pool);
                event_pool = NULL;
                goto out;
        }

        // 创建一个epoll的句柄,自从linux2.6.8之后，count参数是被忽略的,会占用一个fd
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

        // 保存epoll的fd，其他epoll函数会用到
        event_pool->fd = epfd;
        
        event_pool->count = count;

        pthread_mutex_init (&event_pool->mutex, NULL);
        pthread_cond_init (&event_pool->cond, NULL);

out:
        return event_pool;
}

/*事件注册函数*/
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
                //最大监听数等于已使用监听数，扩大池的大小
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
                   边缘触发: 如果这次没有把这个事件对应的套接字缓冲区处理完，
                   在这个套接字中没有新的事件再次到来时，在ET模式下是无法再次从
                   epoll_wait调用中获取这个事件的 
                */
                event_pool->reg[idx].events = EPOLLET ;//边缘触发(Edge Triggered)模式  EPOLLPRI; //表示对应的文件描述符有紧急的数据可读
                //这里的控制函数和私有数据是保存在自己实现的reg中，而不是epoll自带的 epoll_data
                event_pool->reg[idx].handler = handler; //控制函数
                event_pool->reg[idx].data = data; // 私有数据

                switch (poll_in) {
                case 1:
                        //EPOLLIN位 置1
                        event_pool->reg[idx].events |= EPOLLIN;
                        break;
                case 0:
                        //EPOLLIN位 清零
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

                // .events 是一些参数
                epoll_event.events = event_pool->reg[idx].events;
                /*
                    typedef union epoll_data {  
                        void *ptr;  
                        int fd;  
                        __uint32_t u32;  
                        __uint64_t u64;  
                    } epoll_data_t;  
                     //感兴趣的事件和被触发的事件  
                    struct epoll_event {  
                        __uint32_t events; // Epoll events  
                        epoll_data_t data; // User data variable   
                    };  
                */

                // 用 epoll_data_t data占用的64位空间来放fd和inx,如果要放更多数据要
                // 自己分配空间，data存放空间的地址，这里我们把数据放在reg中
                ev_data->fd = fd;
                ev_data->idx = idx;

                /*
                epoll的事件注册函数，它不同于select()是在监听事件时告诉内核要监听
                什么类型的事件，而是在这里先注册要监听的事件类型。
                第一个参数是epoll_create()的返回值。
                第二个参数表示动作，用三个宏来表示：
                EPOLL_CTL_ADD：注册新的fd到epfd中；
                EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
                EPOLL_CTL_DEL：从epfd中删除一个fd；
                 
                第三个参数是需要监听的fd。
                第四个参数是告诉内核需要监听什么事*/
                ret = epoll_ctl (event_pool->fd, EPOLL_CTL_ADD, fd,
                                 &epoll_event);

                if (ret == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "failed to add fd(=%d) to epoll fd(=%d) (%s)",
                                fd, event_pool->fd, strerror (errno));
                        goto unlock;
                }

                //将唤醒等待改条件的所有线程
                pthread_cond_broadcast (&event_pool->cond);
        }
unlock:
        pthread_mutex_unlock (&event_pool->mutex);

out:
        return ret;
}

/*事件注册移除*/
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
                // idx可能会变(见下面，修改idx可能失败了?)，所以这里要查看一下
                idx = __event_getindex (event_pool, fd, idx_hint);

                if (idx == -1) {
                        LOG_PRINT(D_LOG_ERR,
                                "index not found for fd=%d (idx_hint=%d)",
                                fd, idx_hint);
                        errno = ENOENT;
                        goto unlock;
                }
                
                //从epfd中删除一个fd；
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

                //如果是最后一个，直接删除，used减一
                lastidx = event_pool->used - 1;
                if (lastidx == idx) {
                        event_pool->used--;
                        goto unlock;
                }

                //不是最后一个，把最后一个移动到刚刚删除的位置
                epoll_event.events = event_pool->reg[lastidx].events;
                ev_data->fd = event_pool->reg[lastidx].fd;
                ev_data->idx = idx; //修改idx

                //修改已经注册的fd的监听事件, 修改了idx
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


/*修改已经注册的fd的监听事件的属性*/
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

//分发事件处理
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
                //处理函数
                handler = event_pool->reg[idx].handler;
                //私有数据
                data = event_pool->reg[idx].data;
        }
unlock:
        pthread_mutex_unlock (&event_pool->mutex);

        //socket_event_handler
        //调用处理函数
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
                                //阻塞等待条件的改变，event_resister_epoll函数有唤醒
                                pthread_cond_wait (&event_pool->cond,
                                                   &event_pool->mutex);

                        //如何监听数比事件缓存大，则从新分配缓存大小
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

                //永久阻塞等待事件的产生，返回需要处理的事件数目
                /*
                收集在epoll监控的事件中已经发送的事件。参数events是分配好的epoll_event
                结构体数组，epoll将会把发生的事件赋值到events数组中（events不可以是空指针，
                内核只负责把数据复制到这个events数组中，不会去帮助我们在用户态中分配内存）。
                maxevents告之内核这个events有多大，这个 maxevents的值不能大于创建epoll_create()时的size，
                参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。
                如果函数调用成功，返回对应I/O上已准备好的文件描述符数目，如返回0表示已超时。
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
                        //EPOLLOUT事件只有在连接时触发一次，表示可写，其他时候想要触发，那你要先准备好下面条件：
                        //1.某次write，写满了发送缓冲区，返回错误码为EAGAIN。
                        //2.对端读取了一些数据，又重新可写了，此时会触发EPOLLOUT
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
