/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/14 21:39:38 by raamayri         ###   ########.fr       */
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
		pwd = "(lost)";
	prompt = ft_strjoin(pwd, "> ");
	if (!prompt)
		return (ft_strdup("> "));
	return (prompt);
}

static int	code_minibox(t_minibox *minibox)
{
	if (minibox->error.code == MINICODE_INPUT_NULL || \
		minibox->error.code == MINICODE_INPUT_BLANK)
		return (0);
	else if (minibox->error.code == MINICODE_ERRNO)
		return (perror("minishell"), 1);
	else if (minibox->error.code == MINICODE_SIGINT)
		return (130);
	return (ft_dprintf(2, "minishell: %s\n", minibox->error.msg), 1);
}

int	handle_minibox(char *line, t_env **env_list, int dbg)
{
	t_minibox	*minibox;
	char		**current_envp;
	int			exit_code;

	1 && (exit_code = 0), (minibox = ft_calloc(1, sizeof(t_minibox)));
	if (!minibox)
		return (perror("minishell"), free(line), 1);
	current_envp = conv_env_envp(*env_list);
	if (!current_envp)
		return (free(minibox), free(line), 1);
	ft_build_minibox(minibox, line, current_envp);
	if (dbg)
		ft_display_minibox(minibox);
	if (minibox->error.code == MINICODE_NONE)
		exit_code = execute_minibox(minibox, env_list);
	else
		exit_code = code_minibox(minibox);
	1 && (free_envp(current_envp), current_envp = NULL);
	return (ft_destroy_minibox(minibox), free(minibox), exit_code);
}

int	main_loop(t_env **env_lst, int dbg)
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
			1 && (code = g_signal), (g_signal = 0), free(ln);
			continue ;
		}
		if (!ft_isblank(ln))
		{
			add_history(ln);
			1 && (g_signal = code, (code = handle_minibox(ln, env_lst, dbg)));
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
	int		dbg;

	dbg = 0;
	if (ac == 2 && !ft_strcmp(av[1], "--debug"))
		dbg = 1;
	env_list = init_env(envp);
	setup_signals();
	exit_code = main_loop(&env_list, dbg);
	free_env_list(env_list);
	return (exit_code);
}
