#ifndef _EVENT_H_
#define _EVENT_H_

#include <pthread.h>

#include "../debug/debug.h"

struct event_pool;
struct event_ops;
struct event_slot_poll;
struct event_slot_epoll;
struct event_data {
	int idx;
	int gen;
} __attribute__ ((__packed__, __may_alias__));


typedef int (*event_handler_t) (int fd, int idx, void *data,
				int poll_in, int poll_out, int poll_err);

#define EVENT_EPOLL_TABLES 1024
#define EVENT_EPOLL_SLOTS 1024
#define EVENT_MAX_THREADS  32

#define GF_VALIDATE_OR_GOTO(name,arg,label)   do {   \
		if (!arg) {                                  \
			errno = EINVAL;                          \
			LOG_PRINT(D_LOG_ERR,                     \
                      "invalid argument: " #arg);	 \
			goto label;                              \
		}                                            \
	} while (0)

struct event_pool {
	struct event_ops *ops;//事件池相关操作函数

	int fd;//epoll句柄
	int breaker[2];

	int count;//监听的数目
	struct event_slot_poll  *reg;
	struct event_slot_epoll *ereg[EVENT_EPOLL_TABLES];
	int slots_used[EVENT_EPOLL_TABLES];

	int used;//已使用的监听数
	int changed;//event_pool 改变标志位，如有新fd注册时就为1

	pthread_mutex_t mutex;//互斥量
	pthread_cond_t cond;//条件变量

    //epoll_wait函数中参数evcache用来从内核得到事件的集合
	void *evcache;//事件缓存
	int evcache_size;//事件缓存大小

        /* NOTE: Currently used only when event processing is done using
         * epoll. */
        int eventthreadcount; /* number of event threads to execute. */
        pthread_t pollers[EVENT_MAX_THREADS]; /* poller thread_id store,
                                                     * and live status */
        int destroy;
        int activethreadcount;
};

struct event_ops {
        struct event_pool * (*new) (int count, int eventthreadcount);

        int (*event_register) (struct event_pool *event_pool, int fd,
                               event_handler_t handler,
                               void *data, int poll_in, int poll_out);

        int (*event_select_on) (struct event_pool *event_pool, int fd, int idx,
                                int poll_in, int poll_out);

        int (*event_unregister) (struct event_pool *event_pool, int fd, int idx);

        int (*event_unregister_close) (struct event_pool *event_pool, int fd,
				       int idx);

        int (*event_dispatch) (struct event_pool *event_pool);

        int (*event_reconfigure_threads) (struct event_pool *event_pool,
                                          int newcount);
        int (*event_pool_destroy) (struct event_pool *event_pool);
};

struct event_pool *event_pool_new (int count, int eventthreadcount);
int event_select_on (struct event_pool *event_pool, int fd, int idx,
		     int poll_in, int poll_out);
int event_register (struct event_pool *event_pool, int fd,
		    event_handler_t handler,
		    void *data, int poll_in, int poll_out);
int event_unregister (struct event_pool *event_pool, int fd, int idx);
int event_unregister_close (struct event_pool *event_pool, int fd, int idx);
int event_dispatch (struct event_pool *event_pool);
int event_reconfigure_threads (struct event_pool *event_pool, int value);
int event_pool_destroy (struct event_pool *event_pool);
int event_dispatch_destroy (struct event_pool *event_pool);
#endif /* _EVENT_H_ */
