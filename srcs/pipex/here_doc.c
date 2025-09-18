/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:18 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/18 16:41:11 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_herdoc(int sig)
{
	(void)sig;
	signal_handler(SIGINT);
	restore_exec_signals();
	rl_done = 1;
}

void	restore_exec_signals_heredoc(void)
{
	rl_event_hook = 0;
	signal(SIGINT, handle_signal_herdoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
