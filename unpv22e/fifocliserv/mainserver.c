#include	"fifo.h"

void	server(int, int);

int
main(int argc, char **argv)
{
	int		readfifo, writefifo, dummyfd, fd;
	char	*ptr, buff[MAXLINE], fifoname[MAXLINE];
	pid_t	pid;
	ssize_t	n;

		/* 4create server's well-known FIFO; OK if already exists */
	if ((mkfifo(SERV_FIFO, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("can't create %s", SERV_FIFO);

	/* 4open server's well-known FIFO for reading and writing */
    // 阻塞到第一个客户端打开为写
	readfifo = Open(SERV_FIFO, O_RDONLY, 0);
    // 打开为写，从来不用，为了保证所有客户端都退出后还有一个进程打开为写(如果没有会怎么样呢?
    // 如何没有下面的readline不会阻塞会拿上返回0)
	dummyfd = Open(SERV_FIFO, O_WRONLY, 0);		/* never used */

	while ( (n = Readline(readfifo, buff, MAXLINE)) > 0) {
		if (buff[n-1] == '\n')
			n--;			/* delete newline from readline() */
		buff[n] = '\0';		/* null terminate pathname */
        // 客户端发来 pid + 空格 + 路径名
		if ( (ptr = strchr(buff, ' ')) == NULL) {
			err_msg("bogus request: %s", buff);
			continue;
		}

		*ptr++ = 0;			/* null terminate PID, ptr = pathname */
		pid = atol(buff);
		snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long) pid);
        // 打开客户端的命令管道
		if ( (writefifo = open(fifoname, O_WRONLY, 0)) < 0) {
			err_msg("cannot open: %s", fifoname);
			continue;
		}

        // 向客户端写结果
		if ( (fd = open(ptr, O_RDONLY)) < 0) {
				/* 4error: must tell client */
			snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n",
					 strerror(errno));
			n = strlen(ptr);
            
			Write(writefifo, ptr, n);
			Close(writefifo);
	
		} else {
				/* 4open succeeded: copy file to FIFO */
			while ( (n = Read(fd, buff, MAXLINE)) > 0)
				Write(writefifo, buff, n);
			Close(fd);
			Close(writefifo);
		}
    }
    return 0;
}
