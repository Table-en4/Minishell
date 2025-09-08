#include "minishell.h"

void	restore_stdio(int stdio_backup[3])
{
	dup2(stdio_backup[0], STDIN_FILENO);
	dup2(stdio_backup[1], STDOUT_FILENO);
	dup2(stdio_backup[2], STDERR_FILENO);
	close(stdio_backup[0]);
	close(stdio_backup[1]);
	close(stdio_backup[2]);
}

void	apply_redirections(t_fds *fds)
{
	t_fds	*current;
	int		fd;

	current = fds;
	while (current)
	{
		if (current->type == FD_INPUT)
		{
			fd = open(currrent->filename, O_RDONLY);
			if (fd != -1)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		else if (current->type == FD_OUTPUT)
		{
			fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd != -1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		else if (current->type == FD_APPEND)
		{
			fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd != -1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		curerrent = current->next;
	}
}
