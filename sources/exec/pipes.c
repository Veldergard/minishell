#include <unistd.h>
#include "types.h"

void	ft_pipes(t_all *all)
{
	pid_t	pid;
	int		fds[2];

	pipe(fds);
	if ((pid = fork()) == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		all->pipe_pid = -1;
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
		all->pipe_pid = pid;
	}
}
