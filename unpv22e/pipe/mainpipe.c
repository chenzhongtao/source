#include "../lib/unpipc.h"

void	client(int, int), server(int, int);

int
main(int argc, char **argv)
{
    //一个管道的fd[0]为读出端，fd[1]为写入端
	int		pipe1[2], pipe2[2];
	pid_t	childpid;

    //全双工要创建两个管道
	Pipe(pipe1);	/* create two pipes */
	Pipe(pipe2);

	if ( (childpid = Fork()) == 0) {		/* child */
       // 子进程用pipe1[0]来读, pipe2[1]来写,其他两个关掉
		Close(pipe1[1]);
		Close(pipe2[0]);

		server(pipe1[0], pipe2[1]);
		exit(0);
	}
		/* 4parent */
    // 父进程用pipe2[0]来读, pipe1[1]来写,其他两个关掉
	Close(pipe1[0]);
	Close(pipe2[1]);

	client(pipe2[0], pipe1[1]);

	Waitpid(childpid, NULL, 0);		/* wait for child to terminate */
	exit(0);
}


