/*
  Copyright (c) 2008-2012 Red Hat, Inc. <http://www.redhat.com>
  This file is part of GlusterFS.

  This file is licensed to you under your choice of the GNU Lesser
  General Public License, version 3 or any later version (LGPLv3 or
  later), or the GNU General Public License, version 2 (GPLv2), in all
  cases as published by the Free Software Foundation.
*/

#ifndef _EVENT_H_
#define _EVENT_H_


#include <pthread.h>

struct event_pool;
struct event_ops;

// ���dataֻ��64λ
struct event_data {
	int fd;
	int idx;
} __attribute__ ((__packed__, __may_alias__));


typedef int (*event_handler_t) (int fd, int idx, void *data,
				int poll_in, int poll_out, int poll_err);

#define GF_VALIDATE_OR_GOTO(name,arg,label)   do {   \
		if (!arg) {                                  \
			errno = EINVAL;                          \
			LOG_PRINT(D_LOG_ERR,                     \
                      "invalid argument: " #arg);	 \
			goto label;                              \
		}                                            \
	} while (0)

struct event_pool {
	struct event_ops *ops; //�¼�����ز�������

	int fd;  //epoll���
	int breaker[2];

	int count; //��������Ŀ 
	// epoll���Դ��˽�����ݣ����԰�fd,���������������ݴ����������������������Ҫ
	// �Ǹ�pollͳһ����Ϊ��û�д�����ݵĶ���
	struct {
		int fd;   /*������fd*/
		int events; /* Epoll events ��struct epoll_event�ж��� */
		void *data; /* �û����ݣ���struct epoll_event�е�data��һ��*/
		event_handler_t handler; /*������*/
	} *reg; //�¼�ע�ᣬcount��

	int used; //��ʹ�õļ�����
	int changed; //event_pool �ı��־λ��������fdע��ʱ��Ϊ1

	pthread_mutex_t mutex; //������
	pthread_cond_t cond;  //��������

    //epoll_wait�����в���evcache�������ں˵õ��¼��ļ���
	void *evcache; //�¼�����
	int evcache_size; //�¼������С
};

struct event_ops {
        struct event_pool * (*new) (int count);

        int (*event_register) (struct event_pool *event_pool, int fd,
                               event_handler_t handler,
                               void *data, int poll_in, int poll_out);

        int (*event_select_on) (struct event_pool *event_pool, int fd, int idx,
                                int poll_in, int poll_out);

        int (*event_unregister) (struct event_pool *event_pool, int fd, int idx);

        int (*event_dispatch) (struct event_pool *event_pool);
};

struct event_pool * event_pool_new (int count);
int event_select_on (struct event_pool *event_pool, int fd, int idx,
		     int poll_in, int poll_out);
int event_register (struct event_pool *event_pool, int fd,
		    event_handler_t handler,
		    void *data, int poll_in, int poll_out);
int event_unregister (struct event_pool *event_pool, int fd, int idx);
int event_dispatch (struct event_pool *event_pool);

#endif /* _EVENT_H_ */
