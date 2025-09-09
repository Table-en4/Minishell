/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:07 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/08 21:28:31 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_redirection(t_minibox *node, t_env *env)
{
    int fd;
    int save_fd;
    int exit_code;

    if (!node || !node->parsing || !node->lexing || !node->lexing->value)
        return (1);

    if (node->parsing->type == MINITYPE_REDIN)
    {
        fd = open(node->lexing->value, O_RDONLY);
        if (fd == -1)
        {
            perror(node->lexing->value);
            return (1);
        }
        save_fd = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO);
        close(fd);
        exit_code = execute_ast(node, env, node->parsing->left);
        dup2(save_fd, STDIN_FILENO);
        close(save_fd);
    }
    else if (node->parsing->type == MINITYPE_REDOUT)
    {
        fd = open(node->lexing->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror(node->lexing->value);
            return (1);
        }
        save_fd = dup(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        exit_code = execute_ast(node, env, node->parsing->left);
        dup2(save_fd, STDOUT_FILENO);
        close(save_fd);
    }
    else if (node->parsing->type == MINITYPE_REDAPP)
    {
        fd = open(node->lexing->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror(node->lexing->value);
            return (1);
        }
        save_fd = dup(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        exit_code = execute_ast(node, env, node->parsing->left);
        dup2(save_fd, STDOUT_FILENO);
        close(save_fd);
    }
    else if (node->parsing->type == MINITYPE_HEREDOC)
    {
        // TODO: Implementer heredoc
        exit_code = 0;
    }
    else
        exit_code = 0;
    return (exit_code);
}