#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "wrapper_fun.h"
//#include "error.h"
//#include "../debug/debug.h"


#define	SA	struct sockaddr
#define	SERV_PORT		 2015
#define	MAXLINE	4096			/* max line length */




void
my_str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE] = {0};//recvline[MAXLINE];
	struct iovec iov[2];
    char	buf1[MAXLINE] = {0};
    char	buf2[MAXLINE] = {0};
    ssize_t size;

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		Writen(sockfd, sendline, strlen(sendline));
        //Send(sockfd, sendline, strlen(sendline), 0);
        memcpy(buf1, sendline, strlen(sendline));
        memcpy(buf2, sendline, strlen(sendline));
        iov[0].iov_base=buf1;
        iov[0].iov_len=strlen(buf1);
        iov[1].iov_base=buf2;
        iov[1].iov_len=strlen(buf2);
        //Writev(sockfd,iov,2);

        struct msghdr msg = {0, };
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_iov = iov;
        msg.msg_iovlen = 2;
        //msg.msg_control = control_un.control;
        //msg.msg_controllen = sizeof(control_un.control);
        Sendmsg(sockfd, &msg, 0);
  
       

		//if (Readline(sockfd, recvline, MAXLINE) == 0)
		//	err_quit("str_cli: server terminated prematurely");

		//Fputs(recvline, stdout);
	}
}



int32_t main(int32_t argc, char **argv)
{
    int	sockfd;
	struct sockaddr_in	servaddr;
    int serv_port;

	if (argc != 3)
		err_quit("usage: tcpcli <IPaddress> <port>");

    serv_port = atoi(argv[2]);
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(serv_port);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	my_str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}

#ifdef __cplusplus
}
#endif
