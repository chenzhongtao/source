#include	"../lib/unpipc.h"

int
main(int argc, char **argv)
{
	size_t	n;
	char	buff[MAXLINE], command[MAXLINE];
	FILE	*fp;

	/* 4read pathname 读入路径名*/
	Fgets(buff, MAXLINE, stdin);
	n = strlen(buff);		/* fgets() guarantees null byte at end */
	if (buff[n-1] == '\n')
		n--;				/* delete newline from fgets() */

	snprintf(command, sizeof(command), "cat %s", buff);
    
	fp = Popen(command, "r");

		/* 4copy from pipe to standard output */
    // 读进命令的标准输出
	while (Fgets(buff, MAXLINE, fp) != NULL)
        // 再把内容写到标准输出
		Fputs(buff, stdout);

	Pclose(fp);
	exit(0);
}
