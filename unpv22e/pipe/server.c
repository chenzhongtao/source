#include "../lib/unpipc.h"

void
server(int readfd, int writefd)
{
	int		fd;
	ssize_t	n;
	char	buff[MAXLINE+1];

	/* 4read pathname from IPC channel �����ļ���*/
	if ( (n = Read(readfd, buff, MAXLINE)) == 0)
		err_quit("end-of-file while reading pathname");
	buff[n] = '\0';		/* null terminate pathname */
    /*���ļ�*/
	if ( (fd = open(buff, O_RDONLY)) < 0) {
			/* 4error: must tell client */
		snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n",
				 strerror(errno));
		n = strlen(buff);
		Write(writefd, buff, n);

	} else {
			/* 4open succeeded: copy file to IPC channel ��ͻ�������ļ�����*/
		while ( (n = Read(fd, buff, MAXLINE)) > 0)
			Write(writefd, buff, n);
		Close(fd);
	}
}
