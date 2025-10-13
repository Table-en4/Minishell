/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/13 19:37:55 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main_loop(char **envp, t_env *env_lst)
{
	char		*ln;
	char		*prompt;
	static int	code = 0;

	while (1)
	{
		restore_exec_signals();
		1 && (prompt = get_prompt()), (ln = readline(prompt)), free(prompt);
		if (!ln)
			return (ft_dprintf(1, "exit\n"), code);
		if (g_signal == 130)
		{
			1 && (code = g_signal), (g_signal = 0);
			continue ;
		}
		if (!ft_isblank(ln))
		{
			add_history(ln);
			1 && (g_signal = code, (code = handle_minibox(ln, envp, env_lst)));
		}
		else
			1 && (g_signal = 0), (code = 0);
		1 && (g_signal = 0), free(ln);
	}
	return (code);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	int		exit_code;

	(void)ac;
	(void)av;
	env_list = init_env(envp);
	setup_signals();
	exit_code = main_loop(envp, env_list);
	free_env_list(env_list);
	return (exit_code);
}
