/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:47:08 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_subshell(t_minibox *minibox, t_env *env, t_miniparsing *node)
{
    pid_t   pid;
    int     status;
    int     exit_code;

    if (!node || !node->subshell)
        return (1);
    pid = fork();
    if (pid == -1)
        return (perror("fork"), 1);
    if (pid == 0)
    {
        exit_code = execute_parsing_node(minibox, env, node->subshell);
        exit(exit_code);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            exit_code = 128 + WTERMSIG(status);
        else
        exit_code = 1;
    }
    return (exit_code);
}
