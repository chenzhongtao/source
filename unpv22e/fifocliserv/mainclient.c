#include	"fifo.h"

int
main(int argc, char **argv)
{
	int		readfifo, writefifo;
	size_t	len;
	ssize_t	n;
	char	*ptr, fifoname[MAXLINE], buff[MAXLINE];
	pid_t	pid;

		/* 4create FIFO with our PID as part of name */
	pid = getpid();
	snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long) pid);
    // 客户端创键一个自己命令管道
	if ((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("can't create %s", fifoname);

		/* 4start buffer with pid and a blank */
	snprintf(buff, sizeof(buff), "%ld ", (long) pid);
	len = strlen(buff);
	ptr = buff + len;

	/* 4read pathname 读入一个文件名*/
        
	Fgets(ptr, MAXLINE - len, stdin);
	len = strlen(buff);		/* fgets() guarantees null byte at end */

		/* 4open FIFO to server and write PID and pathname to FIFO */
    // 打开服务端的命名管道
	writefifo = Open(SERV_FIFO, O_WRONLY, 0);
	Write(writefifo, buff, len);

		/* 4now open our FIFO; blocks until server opens for writing */
    // 打开自己的命名管道
	readfifo = Open(fifoname, O_RDONLY, 0);

		/* 4read from IPC, write to standard output */
    // 读服务端返回的内容
	while ( (n = Read(readfifo, buff, MAXLINE)) > 0)
		Write(STDOUT_FILENO, buff, n);

	Close(readfifo);
    // 删除命名管道
	Unlink(fifoname);
	exit(0);
}
