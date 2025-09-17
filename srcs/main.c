/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/17 21:47:15 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_miniparsing *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

char	*get_prompt(void)
{
	char	cwd[1024];
	char	*pwd;
	char	*prompt;

	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		pwd = ">";
	prompt = ft_strjoin(pwd, "> ");
	if (!prompt)
		return (ft_strdup("> "));
	return (prompt);
}

int	handle_minibox(char *line, char **envp, t_env *env_list)
{
	t_minibox	*minibox;

	minibox = ft_calloc(1, sizeof(t_minibox));
	if (!minibox)
		return (perror("minishell"), free(line), 1);
	ft_build_minibox(minibox, line, envp);
	if (minibox->error.code == MINICODE_NONE)
		g_signal_received = execute_minibox(minibox, env_list);
	else
	{
		if (minibox->error.code == MINICODE_ERRNO)
			(perror("minishell"), signal_handler(1));
		else
		{
			ft_dprintf(2, "minishell: %s\n", minibox->error.msg);
			signal_handler(1);
		}
	}
	ft_destroy_minibox(minibox);
	free(minibox);
	return (g_signal_received);
}

int	main_loop(char **envp, t_env *env_list)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			return (ft_dprintf(1, "\e[46mexit\e[0m \n"), g_signal_received);
		restore_exec_signals();
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		g_signal_received = handle_minibox(line, envp, env_list);
		free(line);
	}
	return (g_signal_received);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = init_env(envp);
	g_signal_received = main_loop(envp, env_list);
	free_env_list(env_list);
	return (g_signal_received);
}
