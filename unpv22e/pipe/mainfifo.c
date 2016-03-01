#include	"../lib/unpipc.h"

#define	FIFO1	"/tmp/fifo.1"
#define	FIFO2	"/tmp/fifo.2"

void	client(int, int), server(int, int);

int
main(int argc, char **argv)
{
	int		readfd, writefd;
	pid_t	childpid;

	/* 4create two FIFOs; OK if they already exist */
    // 创建两个命名管道，如果已存在就继续走
	if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("can't create %s", FIFO1);
	if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
		unlink(FIFO1);
		err_sys("can't create %s", FIFO2);
	}

	if ( (childpid = Fork()) == 0) {		/* child */
        // 命名管道创建后还要opens
        // 这里会阻塞，直到父进程已写的方式打开，无论先读还是先写，都会阻塞有其他进程来写和读
        // 所以这里先打开FIFO1,父进程就要先打开FIFO1，不然会死锁
		readfd = Open(FIFO1, O_RDONLY, 0);
		writefd = Open(FIFO2, O_WRONLY, 0);

		server(readfd, writefd);
		exit(0);
	}
		/* 4parent */
	writefd = Open(FIFO1, O_WRONLY, 0);
	readfd = Open(FIFO2, O_RDONLY, 0);

	client(readfd, writefd);

	Waitpid(childpid, NULL, 0);		/* wait for child to terminate */

	Close(readfd);
	Close(writefd);
    // 管道pipe会在所有进程关闭后自动消失，FIFO需要显式删除
	Unlink(FIFO1);
	Unlink(FIFO2);
	exit(0);
}
