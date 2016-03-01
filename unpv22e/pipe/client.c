#include "../lib/unpipc.h"

void
client(int readfd, int writefd)
{
	size_t	len;
	ssize_t	n;
	char	buff[MAXLINE];

	/* 4read pathname 读入一个文件名*/
	Fgets(buff, MAXLINE, stdin);
	len = strlen(buff);		/* fgets() guarantees null byte at end */
	if (buff[len-1] == '\n')
		len--;				/* delete newline from fgets() */

	/* 4write pathname to IPC channel 向服务端写*/
	Write(writefd, buff, len);

	/* 4read from IPC, write to standard output 向标准输出输出文件内容*/
	while ( (n = Read(readfd, buff, MAXLINE)) > 0)
		Write(STDOUT_FILENO, buff, n);
}
