#include	"../lib/unpipc.h"

//属性
struct mq_attr	attr;	/* mq_maxmsg and mq_msgsize both init to 0 */


//创建一个消息队列 ./mqcreate /tmp.1234
int
main(int argc, char **argv)
{
	int		c, flags;
	mqd_t	mqd;

	flags = O_RDWR | O_CREAT;
	while ( (c = Getopt(argc, argv, "em:z:")) != -1) {
		switch (c) {
		case 'e':
			flags |= O_EXCL; //文件存在会报错
			break;

		case 'm':
            // 每个队列的最大消息数
			attr.mq_maxmsg = atol(optarg);
			break;

		case 'z':
            // 每个消息的最大字节数
			attr.mq_msgsize = atol(optarg);
			break;
		}
	}
	if (optind != argc - 1)
		err_quit("usage: mqcreate [ -e ] [ -m maxmsg -z msgsize ] <name>");

	if ((attr.mq_maxmsg != 0 && attr.mq_msgsize == 0) ||
		(attr.mq_maxmsg == 0 && attr.mq_msgsize != 0))
		err_quit("must specify both -m maxmsg and -z msgsize");
    //argv[optind] 为name
	mqd = Mq_open(argv[optind], flags, FILE_MODE,
				  (attr.mq_maxmsg != 0) ? &attr : NULL);

	Mq_close(mqd);
	exit(0);
}
