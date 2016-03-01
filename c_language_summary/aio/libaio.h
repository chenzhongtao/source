/* /usr/include/libaio.h
 *
 * Copyright 2000,2001,2002 Red Hat, Inc.
 *
 * Written by Benjamin LaHaise <bcrl@redhat.com>
 *
 * libaio Linux async I/O interface
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */
#ifndef __LIBAIO_H
#define __LIBAIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <string.h>

struct timespec;
struct sockaddr;
struct iovec;

typedef struct io_context *io_context_t;

typedef enum io_iocb_cmd {
	IO_CMD_PREAD = 0,
	IO_CMD_PWRITE = 1,

	IO_CMD_FSYNC = 2,
	IO_CMD_FDSYNC = 3,

	IO_CMD_POLL = 5, /* Never implemented in mainline, see io_prep_poll */
	IO_CMD_NOOP = 6,
	IO_CMD_PREADV = 7,
	IO_CMD_PWRITEV = 8,
} io_iocb_cmd_t;

#if defined(__i386__) /* little endian, 32 bits */
#define PADDED(x, y)	x; unsigned y
#define PADDEDptr(x, y)	x; unsigned y
#define PADDEDul(x, y)	unsigned long x; unsigned y
#elif defined(__ia64__) || defined(__x86_64__) || defined(__alpha__)
#define PADDED(x, y)	x, y
#define PADDEDptr(x, y)	x
#define PADDEDul(x, y)	unsigned long x
#elif defined(__powerpc64__) /* big endian, 64 bits */
#define PADDED(x, y)	unsigned y; x
#define PADDEDptr(x,y)	x
#define PADDEDul(x, y)	unsigned long x
#elif defined(__PPC__)  /* big endian, 32 bits */
#define PADDED(x, y)	unsigned y; x
#define PADDEDptr(x, y)	unsigned y; x
#define PADDEDul(x, y)	unsigned y; unsigned long x
#elif defined(__s390x__) /* big endian, 64 bits */
#define PADDED(x, y)	unsigned y; x
#define PADDEDptr(x,y)	x
#define PADDEDul(x, y)	unsigned long x
#elif defined(__s390__) /* big endian, 32 bits */
#define PADDED(x, y)	unsigned y; x
#define PADDEDptr(x, y) unsigned y; x
#define PADDEDul(x, y)	unsigned y; unsigned long x
#else
#error	endian?
#endif

struct io_iocb_poll {
	PADDED(int events, __pad1);
};	/* result code is the set of result flags or -'ve errno */

struct io_iocb_sockaddr {
	struct sockaddr *addr;
	int		len;
};	/* result code is the length of the sockaddr, or -'ve errno */

struct io_iocb_common {
	PADDEDptr(void	*buf, __pad1);
	PADDEDul(nbytes, __pad2);
	long long	offset;
	long long	__pad3;
	unsigned	flags;
	unsigned	resfd;
};	/* result code is the amount read or -'ve errno */

struct io_iocb_vector {
	const struct iovec	*vec;
	int			nr;
	long long		offset;
};	/* result code is the amount read or -'ve errno */

struct iocb {
	PADDEDptr(void *data, __pad1);	/* Return in the io completion event */
	PADDED(unsigned key, __pad2);	/* For use in identifying io requests */

	short		aio_lio_opcode;	
	short		aio_reqprio;
	int		aio_fildes;

	union {
		struct io_iocb_common		c;
		struct io_iocb_vector		v;
		struct io_iocb_poll		poll;
		struct io_iocb_sockaddr	saddr;
	} u;
};

struct io_event {
	PADDEDptr(void *data, __pad1);
	PADDEDptr(struct iocb *obj,  __pad2);
	PADDEDul(res,  __pad3);
	PADDEDul(res2, __pad4);
};

#undef PADDED
#undef PADDEDptr
#undef PADDEDul

typedef void (*io_callback_t)(io_context_t ctx, struct iocb *iocb, long res, long res2);

/* library wrappers */
extern int io_queue_init(int maxevents, io_context_t *ctxp);
/*extern int io_queue_grow(io_context_t ctx, int new_maxevents);*/
extern int io_queue_release(io_context_t ctx);
/*extern int io_queue_wait(io_context_t ctx, struct timespec *timeout);*/
extern int io_queue_run(io_context_t ctx);

/* Actual syscalls */
//所有的系统调用
extern int io_setup(int maxevents, io_context_t *ctxp);
extern int io_destroy(io_context_t ctx);
/*
SYNOPSIS
       #include <libaio.h>

       int io_submit(aio_context_t ctx_id, long nr, struct iocb **iocbpp);

       Link with -laio.

DESCRIPTION
       io_submit()  queues  nr  I/O  request blocks for processing in the AIO context ctx_id.  iocbpp should be an array of nr AIO control blocks, which
       will be submitted to context ctx_id.

RETURN VALUE
       On success, io_submit() returns the number of iocbs submitted (which may be 0 if nr is zero).  
       For the failure return, see NOTES.

ERRORS
       EAGAIN Insufficient resources are available to queue any iocbs.

       EBADF  The file descriptor specified in the first iocb is invalid.

       EFAULT One of the data structures points to invalid data.

       EINVAL The aio_context specified by ctx_id is invalid.  nr is less than 0.  
       The iocb at *iocbpp[0] is not properly initialized, or the  operation
              specified is invalid for the file descriptor in the iocb.

       ENOSYS io_submit() is not implemented on this architecture.
        当一个IO控制块（struct iocb cb）初始化完毕，把这个指针放入一个数组中( cbs[0] = &cb)，
        因为io_submit系统调用需要接受一个二维指针。在io_submit(ctx, 1, cbs)中， 
        参数分别为IO上下文（aio_context_t）、数组（struct iocb）大小、数组地址(cbs)

        返回值:
        A) ret = (提交的iocb的数目)
	表示所有的iocb都被接受并处理

    B) 0 < ret <  (提交的iocb的数目)
    	io_submit() 系统调用会从传入的cbs中一个一个处理iocb，如果提交的某个iocb失败，将停止并且返回iocb的索引号。没办法知晓错     误的具体原因，但是如果第一个iocb提交失败，参看C条。
    C) ret < 0
           有两种原因：
    	1) 在io_submit()开始之前发生了某种错误(e.g.比如AIO context非法). 
    	2) 提交第一个iocb(cbx[0])失败

       */
extern int io_submit(io_context_t ctx, long nr, struct iocb *ios[]);
extern int io_cancel(io_context_t ctx, struct iocb *iocb, struct io_event *evt);
/*
当提交了iocb之后，可以不用等待IO完成去做其他的操作。对于每一个已经完成的IO请求(成功或失败），
内核都会创建一个io_event结构。io_getevent()系统调用可以用来获取这一结构。这需要做以下操作。
*/
extern int io_getevents(io_context_t ctx_id, long min_nr, long nr, struct io_event *events, struct timespec *timeout);


static inline void io_set_callback(struct iocb *iocb, io_callback_t cb)
{
	iocb->data = (void *)cb;
}


//下面是封装好的用户空间的函数
/*
   内核当前支持的AIO 命令有:
    
   IOCB_CMD_PREAD
   读; 对应系统调用pread().

   IOCB_CMD_PWRITE
   写，对应系统调用pwrite().

   IOCB_CMD_FSYNC
   同步文件数据到磁盘，对应系统调用fsync()

   IOCB_CMD_FDSYNC
   同步文件数据到磁盘，对应系统调用fdatasync()
     IOCB_CMD_PREADV
   读，对应系统调用readv()

   IOCB_CMD_PWRITEV
   写，对应系统调用writev()
   IOCB_CMD_NOOP
   只是内核使用
*/
static inline void io_prep_pread(struct iocb *iocb, int fd, void *buf, size_t count, long long offset)
{
	memset(iocb, 0, sizeof(*iocb)); //置零
	iocb->aio_fildes = fd;      //文件fd
	iocb->aio_lio_opcode = IO_CMD_PREAD;
	iocb->aio_reqprio = 0;
	iocb->u.c.buf = buf;        //缓存地址
	iocb->u.c.nbytes = count;   //缓存大小
	iocb->u.c.offset = offset;  //文件offset
}

static inline void io_prep_pwrite(struct iocb *iocb, int fd, void *buf, size_t count, long long offset)
{
	memset(iocb, 0, sizeof(*iocb));
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_PWRITE;
	iocb->aio_reqprio = 0;
	iocb->u.c.buf = buf;
	iocb->u.c.nbytes = count;
	iocb->u.c.offset = offset;
}

static inline void io_prep_preadv(struct iocb *iocb, int fd, const struct iovec *iov, int iovcnt, long long offset)
{
	memset(iocb, 0, sizeof(*iocb));
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_PREADV;
	iocb->aio_reqprio = 0;
	iocb->u.c.buf = (void *)iov;
	iocb->u.c.nbytes = iovcnt;
	iocb->u.c.offset = offset;
}

static inline void io_prep_pwritev(struct iocb *iocb, int fd, const struct iovec *iov, int iovcnt, long long offset)
{
	memset(iocb, 0, sizeof(*iocb));
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_PWRITEV;
	iocb->aio_reqprio = 0;
	iocb->u.c.buf = (void *)iov;
	iocb->u.c.nbytes = iovcnt;
	iocb->u.c.offset = offset;
}

/* Jeff Moyer says this was implemented in Red Hat AS2.1 and RHEL3.
 * AFAICT, it was never in mainline, and should not be used. --RR */
static inline void io_prep_poll(struct iocb *iocb, int fd, int events)
{
        memset(iocb, 0, sizeof(*iocb));
        iocb->aio_fildes = fd;
        iocb->aio_lio_opcode = IO_CMD_POLL;
        iocb->aio_reqprio = 0;
        iocb->u.poll.events = events;
}

static inline int io_poll(io_context_t ctx, struct iocb *iocb, io_callback_t cb, int fd, int events)
{
        io_prep_poll(iocb, fd, events);
        io_set_callback(iocb, cb);
        return io_submit(ctx, 1, &iocb);
}

static inline void io_prep_fsync(struct iocb *iocb, int fd)
{
	memset(iocb, 0, sizeof(*iocb));
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_FSYNC;
	iocb->aio_reqprio = 0;
}

static inline int io_fsync(io_context_t ctx, struct iocb *iocb, io_callback_t cb, int fd)
{
	io_prep_fsync(iocb, fd);
	io_set_callback(iocb, cb);
	return io_submit(ctx, 1, &iocb);
}

static inline void io_prep_fdsync(struct iocb *iocb, int fd)
{
	memset(iocb, 0, sizeof(*iocb));
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_FDSYNC;
	iocb->aio_reqprio = 0;
}

static inline int io_fdsync(io_context_t ctx, struct iocb *iocb, io_callback_t cb, int fd)
{
	io_prep_fdsync(iocb, fd);
	io_set_callback(iocb, cb);
	return io_submit(ctx, 1, &iocb);
}

static inline void io_set_eventfd(struct iocb *iocb, int eventfd)
{
	iocb->u.c.flags |= (1 << 0) /* IOCB_FLAG_RESFD */;
	iocb->u.c.resfd = eventfd;
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBAIO_H */
