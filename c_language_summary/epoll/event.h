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

// 这个data只有64位
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
	struct event_ops *ops; //事件池相关操作函数

	int fd;  //epoll句柄
	int breaker[2];

	int count; //监听的数目 
	// epoll可以存放私有数据，可以把fd,处理函数，其他数据存放起来，这里存放在这里主要
	// 是跟poll统一，因为其没有存放数据的定义
	struct {
		int fd;   /*监听的fd*/
		int events; /* Epoll events 在struct epoll_event有定义 */
		void *data; /* 用户数据，与struct epoll_event中的data不一样*/
		event_handler_t handler; /*处理函数*/
	} *reg; //事件注册，count个

	int used; //已使用的监听数
	int changed; //event_pool 改变标志位，如有新fd注册时就为1

	pthread_mutex_t mutex; //互斥量
	pthread_cond_t cond;  //条件变量

    //epoll_wait函数中参数evcache用来从内核得到事件的集合
	void *evcache; //事件缓存
	int evcache_size; //事件缓存大小
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
