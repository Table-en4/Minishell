/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:18 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/17 21:55:57 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_signal_herdoc(int sig)
{
    if (sig == SIGINT)
    {
        ft_dprintf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_received = 130;
		rl_done = 1;
    }
}

void    restor_exec_signals_herdoc(void)
{
	signal(SIGINT, handle_signal_herdoc);
}