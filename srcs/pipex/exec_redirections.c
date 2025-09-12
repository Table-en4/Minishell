/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:07 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:51:00 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int exec_redirection_improved(t_minibox *minibox, t_env *env, t_miniparsing *node)
{
    int fd;
    int save_fd;
    int exit_code;

    if (!node || !node->left)
        return (1);
    if (node->type == MINITYPE_REDIN)
    {
        fd = open(node->argv[0], O_RDONLY);
        if (fd == -1)
            return (perror(node->argv[0]), 1);
        save_fd = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO);
        close(fd);
        exit_code = execute_parsing_node(minibox, env, node->left);
        dup2(save_fd, STDIN_FILENO);
        close(save_fd);
    }
    else if (node->type == MINITYPE_REDOUT)
    {
        fd = open(node->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (perror(node->argv[0]), 1);
        save_fd = dup(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        exit_code = execute_parsing_node(minibox, env, node->left);
        dup2(save_fd, STDOUT_FILENO);
        close(save_fd);
    }
    else if (node->type == MINITYPE_REDAPP)
    {
        fd = open(node->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return (perror(node->argv[0]), 1);
        save_fd = dup(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        exit_code = execute_parsing_node(minibox, env, node->left);
        dup2(save_fd, STDOUT_FILENO);
        close(save_fd);
    }
    else if (node->type == MINITYPE_HEREDOC)
        exit_code = exec_heredoc(minibox, env, node);
    else
        exit_code = 1;
    return (exit_code);
}
