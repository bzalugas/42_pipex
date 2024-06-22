#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main()
{
	int	fd[2];
	int	pid;
	int	pid2;


	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(2);
	if (pid == 0)
	{
		int x = 23;
		close(fd[0]);
		write(1, "before write\n", 13);
		sleep(3);
		write(fd[1], &x, sizeof(x));
		write(1, "after write\n", 12);
		close(fd[1]);
	}
	else {
		pid2 = fork();
		if (pid2 == -1)
			exit(3);
		if (pid2 == 0)
		{
			int	y;
			close(fd[1]);
			write(1, "before read\n", 12);
			read(fd[0], &y, sizeof(y));
			write(1, "after read\n", 11);
			close(fd[0]);
			printf("Read %d\n", y);
		}
		else
			wait(NULL);
	}
	return 0;
}
