#ifdef __cplusplus
extern "C"{
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <malloc.h>
#include <stdint.h> /*定义了 uint64_t等*/

#include <fcntl.h>
#include <libaio.h>

#include "../count_time/count_time.h"

#ifndef O_DIRECT
/* savannah bug #20050, #20052 */
#define O_DIRECT 0 /* From asm/fcntl.h */
#endif


// 解决问题 warning: implicit declaration of function ‘posix_memalign’
#ifdef USE_XOPEN2K
/* Allocate memory of SIZE bytes with an alignment of ALIGNMENT.  */
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __THROW __nonnull ((1));
#endif

int main(int argc, char *argv[])
{
	// 每次写入32K字节  32768
	const int buffer_size = 1024*1024;
    // 文件大小 2G
    uint64_t file_size = (uint64_t)16*1024*1024;

	// 最大事件数 128
	const int nr_events   = 128;
	int rt;

	io_context_t ctx = {0};

	// 初使化 io_context_t
	//系统调用io_setup会创建一个所谓的"AIO上下文"(即aio_context，后文也叫‘AIO context’等)结构体到在内核中
	rt = io_setup(nr_events, &ctx);
	if ( rt != 0 )
		error(1, rt, "io_setup");

	// 依次读取参数作为文件名加入提交到ctx
	// 获取系统页大小
	
	int pagesize = sysconf(_SC_PAGESIZE);

    CPU_TIME_START
	for (int i=1; i<argc; ++i) {
		struct iocb *cb = (struct iocb*)malloc(sizeof(struct iocb));

        void *buffer;
		// 要使用O_DIRECT, 必须要对齐，页大小对齐
        posix_memalign(&buffer, pagesize, buffer_size);
		
        //主要是设置参数
		io_prep_pwrite(cb, open(argv[i], O_WRONLY| O_CREAT | O_TRUNC | O_DIRECT), buffer, buffer_size, 0);
		rt = io_submit(ctx, 1, &cb);
		if (rt < 0)
			error(1, -rt, "io_submit %s", argv[i]);;
	}

	struct  io_event events[nr_events];
	struct  iocb     *cbs[nr_events];
    struct  io_event event;

	int remain = argc - 1;
	int n      = 0;

	// 接收数据最小返回的请求数为1，最大为nr_events
	// io_getevents() returns the number of events read
	while (remain && (n = io_getevents(ctx, 1, nr_events, events, 0))) {
		int nr_cbs = 0;
		for (int i=0; i<n; ++i) {
			event = events[i];
			struct  iocb     *cb    = event.obj;
			// event.res为unsigned
			//printf("%d receive %d bytes\n", cb->aio_fildes, event.res);
			if (event.res > buffer_size) {
				printf("%s\n", strerror(-event.res));
			}
            
            //写完了
			if (cb->u.c.offset >= file_size) {
				--remain;
				// 释放buffer, fd 与 cb
				free(cb->u.c.buf);
				close(cb->aio_fildes);
				free(cb);
            //还没读完
			} else {
				// 更新cb的offset
				cb->u.c.offset += event.res;
				cbs[nr_cbs++] = cb;
			}
		}

		if (nr_cbs) {
			// 继续接收数据
			TIME_START
			// 测试后的异步io也很耗时，好像有在等待写
			io_submit(ctx, nr_cbs, cbs);
            TIME_END_PRINT("aio_write");
		}
	}
    CPU_TIME_END_PRINT("aio_write");
    //io_destroy的作用是销毁这个上下文aio_context_t
    rt = io_destroy(ctx);
    if (rt < 0) {
        perror("io_destroy error");
        return -1;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif