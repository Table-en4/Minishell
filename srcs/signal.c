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

void    handle_signal(int sig)
{
    t_minibox *minibox;
    t_env *env_list;

     (void)env_list;
     (void)minibox;
    if (sig == SIGINT)
    {
        ft_dprintf(1, "Un Ctrl + C a été détecté\n");
        exit(130);
    }
}

void    execution_singals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL); // ctrl + "\"
    signal(SIGTSTP, SIG_DFL); // ctrl + z
}

void    restore_exec_signals(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}
