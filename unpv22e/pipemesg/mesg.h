#include	"../lib/unpipc.h"

/* Our own "messages" to use with pipes, FIFOs, and message queues. */

	/* 4want sizeof(struct mymesg) <= PIPE_BUF */
// 数据大小
#define	MAXMESGDATA	(PIPE_BUF - 2*sizeof(long))

	/* 4length of mesg_len and mesg_type */
// 头部大小
#define	MESGHDRSIZE	(sizeof(struct mymesg) - MAXMESGDATA)

// 对消息的封装，保证了有多个客户端同时写时可以把数据分开
struct mymesg {
  long	mesg_len;	/* #bytes in mesg_data, can be 0 数据大小*/
  long	mesg_type;	/* message type, must be > 0 */
  char	mesg_data[MAXMESGDATA];
};

ssize_t	 mesg_send(int, struct mymesg *);
void	 Mesg_send(int, struct mymesg *);
ssize_t	 mesg_recv(int, struct mymesg *);
ssize_t	 Mesg_recv(int, struct mymesg *);
