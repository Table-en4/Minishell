/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:46 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/16 16:42:46 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	int		exit_code;
	int		stdio_backup[3];
	char	**argv;

	(void)minibox;
	if (!node || !node->argv || !node->argv[0])
		return (1);
	argv = node->argv;
	stdio_backup[0] = dup(STDIN_FILENO);
	stdio_backup[1] = dup(STDOUT_FILENO);
	stdio_backup[2] = dup(STDERR_FILENO);
	if (apply_redirections(node->fds, stdio_backup) < 0)
	{
		restore_stdio(stdio_backup);
		return (1);
	}
	if (!should_fork(argv[0]))
		exit_code = execute_builtin_no_fork(argv, &env);
	else
		exit_code = run_command(argv, env);
	restore_stdio(stdio_backup);
	return (exit_code);
}

int	execute_builtin_no_fork(char **argv, t_env **env)
{
	if (!argv || !argv[0])
		return (1);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, env));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, env));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, env));
	else if (ft_strcmp(argv[0], "exit") == 0)
	{
		ft_dprintf(1, "exit\n");
		free_env_list(*env);
		exit(0);
	}
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
/*
int	run_command(char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**envp;
	int		sig;

	if (!argv || !argv[0])
		return (1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (is_builtin(argv[0]) != -1)
		{
			exit(execute_builtin(argv, &env));
		}
		else
		{
			envp = conv_env_envp(env);
			if (!envp)
				exit(1);
			cmd_path = find_path(argv[0], env);
			if (!cmd_path)
			{
				ft_dprintf(2, "%s: command not found\n", argv[0]);
				free_envp(envp);
				exit(127);
			}
			if (execve(cmd_path, argv, envp) == -1)
			{
				perror(argv[0]);
				free(cmd_path);
				free_envp(envp);
				exit(126);
			}
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				ft_dprintf(1, "\n");
			return (128 + sig);
		}
		return (1);
	}
	return (perror("fork"), 1);
}*/
