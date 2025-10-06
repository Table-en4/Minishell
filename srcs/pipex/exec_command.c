/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:46 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/18 15:14:27 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_with_redirections(char **argv, t_env **env, t_minifd *fds)
{
	int	stdio_backup[3];
	int	exit_code;

	init_stdio_backup_exec(stdio_backup);
	if (apply_redirections(fds, stdio_backup) < 0)
	{
		restore_stdio(stdio_backup);
		return (1);
	}
	if (!should_fork(argv[0]))
		exit_code = execute_builtin_no_fork(argv, env);
	else
		exit_code = run_command(argv, *env);
	restore_stdio(stdio_backup);
	return (exit_code);
}

static int	handle_no_fork_builtin_exit(char **argv, t_env **env)
{
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		ft_dprintf(1, "exit\n");
		free_env_list(*env);
		exit(g_signal_received);
	}
	return (1);
}

int	execute_builtin_no_fork(char **argv, t_env **env)
{
	if (!argv || !argv[0])
		return (1);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, env));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, env));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, env));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (handle_no_fork_builtin_exit(argv, env));
	return (execute_builtin(argv, env));
}

int	should_fork(char *cmd)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	if (ft_strcmp(cmd, "export") == 0)
		return (0);
	if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	return (1);
}

int	exec_command(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	char	**argv;

	(void)minibox;
	if (!node || !node->argv || !node->argv[0])
		return (1);
	argv = node->argv;
	if (!node->fds)
	{
		if (!should_fork(argv[0]))
			return (execute_builtin_no_fork(argv, &env));
		return (run_command(argv, env));
	}
	return (exec_with_redirections(argv, &env, node->fds));
}
