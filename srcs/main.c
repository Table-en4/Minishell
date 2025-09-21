/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/21 13:41:05 by molapoug         ###   ########.fr       */
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
	int			exit_code;

	exit_code = 0;
	minibox = ft_calloc(1, sizeof(t_minibox));
	if (!minibox)
		return (perror("minishell"), free(line), 1);
	ft_build_minibox(minibox, line, envp);
	if (minibox->error.code == MINICODE_NONE)
		exit_code = execute_minibox(minibox, env_list);
	else if (minibox->error.code != MINICODE_INPUT_NULL && \
			minibox->error.code != MINICODE_INPUT_BLANK)
	{
		exit_code = 1;
		if (minibox->error.code == MINICODE_ERRNO)
			perror("minishell");
		else if (minibox->error.code != MINICODE_SIGINT)
			ft_dprintf(2, "minishell: %s\n", minibox->error.msg);
		else
			exit_code = 130;
	}
	return (ft_destroy_minibox(minibox), free(minibox), exit_code);
}

int	main_loop(char **envp, t_env *env_list)
{
	char		*line;
	char		*prompt;
	static int	exit_code = 0;

	signal_handler(exit_code);
	while (1)
	{
		restore_exec_signals();
		1 && (prompt = get_prompt()), (line = readline(prompt)), free(prompt);
		if (!line)
		{
			if (g_signal_received == 130)
				continue ;
			return (ft_dprintf(1, "exit\n"), g_signal_received);
		}
		if (*line == '\0')
		{
			(signal_handler(exit_code), free(line));
			continue ;
		}
		add_history(line);
		exit_code = handle_minibox(line, envp, env_list);
		(signal_handler(exit_code), free(line));
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
