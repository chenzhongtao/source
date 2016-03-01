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
#include <unistd.h>

#include <fcntl.h>

#include "../count_time/count_time.h"

#define _XOPEN_SOURCE 500

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


	// 依次读取参数作为文件名加入提交到ctx
	// 获取系统页大小
	
	int pagesize = sysconf(_SC_PAGESIZE);
    int *fds = (int*)malloc(sizeof(int)*argc);
    void *buffer;
	// 要使用O_DIRECT, 必须要对齐，页大小对齐
    posix_memalign(&buffer, pagesize, buffer_size);
    CPU_TIME_START
	for (int i=1; i<argc; ++i) {
        //主要是设置参数
		fds[i-1] = open(argv[i], O_WRONLY| O_CREAT | O_TRUNC | O_DIRECT);
	}

	for (uint64_t offset =0; offset<file_size; offset+= buffer_size) {

    	for (int i=1; i<argc; ++i) {
            //主要是设置参数
            TIME_START
            pwrite(fds[i-1], buffer, buffer_size, offset);
            TIME_END_PRINT("aio_write");
    	}
    }
    CPU_TIME_END_PRINT("write");


    return 0;
}

#ifdef __cplusplus
}
#endif