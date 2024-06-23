#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../include/libft.h"

int	main(int ac, char *av[], char *env[])
{
	int	fd[2];
	int	pid;
	int	pid2;
	int	fdin;
	int	fdout;
	char	**cmd;

	if (pipe(fd) == -1)
		return (1);
	fdin = open(av[1], O_RDONLY);
	if (fdin == -1)
		return (2);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid == 0)
	{
			//child
		cmd = ft_split(av[2], ' ');
		if (access(cmd[0], O_EXEC) == -1)
			exit(4);
		else
		{
			write(1, "here\n", 5);
			dup2(fdin, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			close(fdin);
			execve(cmd[0], cmd, env);
		}
	}
	int	status;
	//parent
	fdout = open(av[4], O_WRONLY);
	if (fdout == -1)
		return (5);
	pid2 = fork();
	if (pid2 == -1)
		return (6);
	if (pid2 == 0)
	{
		//2nd child
		cmd = ft_split(av[3], ' ');
		if (access(cmd[0], O_EXEC) == -1)
			return (7);
		else
		{
			ft_printf("fdout = %d\n", fdout);
			dup2(fd[0], STDIN_FILENO);
			dup2(fdout, STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			close(fdout);
			execve(cmd[0], cmd, env);
		}
	}
	//parent
	close(fd[0]);
	close(fd[1]);
	ft_printf("waiting for %d and %d\n", pid, pid2);
	waitpid(pid, &status, 0);
	ft_printf("%d stopped\n", pid);
	waitpid(pid2, &status, 0);
	ft_printf("%d stopped\n", pid2);
	return (WEXITSTATUS(status));
	return 23;
}
