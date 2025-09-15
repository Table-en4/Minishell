/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:47:08 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_subshell(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	pid_t	pid;
	int		status;
	int		exit_code;
	int		stdio_backup[3] = {-1, -1, -1};

	if (!node || !node->subshell)
		return (1);
		
	pid = fork();
    //enfant
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		//apply des redir subshell
		if (node->fds && apply_redirections(node->fds, stdio_backup) < 0)
			exit(1);
		//exec du contenu du subshell
		exit_code = execute_ast(minibox, node->subshell, env);
		exit(exit_code);
	}
    //parent
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
				ft_dprintf(1, "\n");
			exit_code = 128 + sig;
		}
		else
			exit_code = 1;
	}
	else
	{
		perror("fork");
		exit_code = 1;
	}
	return (exit_code);
}
