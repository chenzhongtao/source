#include	"fifo.h"

//�� server_main ���һ������Ե��ϵ�Ŀͻ����������

void	client(int, int);

int
main(int argc, char **argv)
{
	int		readfd, writefd;

	writefd = Open(FIFO1, O_WRONLY, 0);
	readfd = Open(FIFO2, O_RDONLY, 0);

	client(readfd, writefd);

	Close(readfd);
	Close(writefd);

	Unlink(FIFO1);
	Unlink(FIFO2);
	exit(0);
}
