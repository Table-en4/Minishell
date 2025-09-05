/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:38:13 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_subshell(t_miniparsing *node, t_env *env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
        exit(execute_ast(node->left, env));
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
