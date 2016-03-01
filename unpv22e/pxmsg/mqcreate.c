#include	"../lib/unpipc.h"

//����
struct mq_attr	attr;	/* mq_maxmsg and mq_msgsize both init to 0 */


//����һ����Ϣ���� ./mqcreate /tmp.1234
int
main(int argc, char **argv)
{
	int		c, flags;
	mqd_t	mqd;

	flags = O_RDWR | O_CREAT;
	while ( (c = Getopt(argc, argv, "em:z:")) != -1) {
		switch (c) {
		case 'e':
			flags |= O_EXCL; //�ļ����ڻᱨ��
			break;

		case 'm':
            // ÿ�����е������Ϣ��
			attr.mq_maxmsg = atol(optarg);
			break;

		case 'z':
            // ÿ����Ϣ������ֽ���
			attr.mq_msgsize = atol(optarg);
			break;
		}
	}
	if (optind != argc - 1)
		err_quit("usage: mqcreate [ -e ] [ -m maxmsg -z msgsize ] <name>");

	if ((attr.mq_maxmsg != 0 && attr.mq_msgsize == 0) ||
		(attr.mq_maxmsg == 0 && attr.mq_msgsize != 0))
		err_quit("must specify both -m maxmsg and -z msgsize");
    //argv[optind] Ϊname
	mqd = Mq_open(argv[optind], flags, FILE_MODE,
				  (attr.mq_maxmsg != 0) ? &attr : NULL);

	Mq_close(mqd);
	exit(0);
}
