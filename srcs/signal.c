/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:41 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:59:15 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_signal_received = 0;

void	signal_handler(int sig)
{
	g_signal_received = sig;
}

void	handle_signal(int sig)
{
	t_minibox	*minibox;
	t_env		*env_list;

	(void)env_list;
	(void)minibox;
	if (sig == SIGINT)
	{
		ft_dprintf(1, "Un Ctrl + C a été détecté\n");
		exit(130);
	}
}

void	execution_singals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

void	restore_exec_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
