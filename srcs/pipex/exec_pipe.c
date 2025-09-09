/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/08 21:28:31 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_pipe(t_minibox *node, int input_fd, t_env *env)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int     left_status;
    int     right_status;

    if (pipe(pipe_fd) == -1)
        return (1);

    left_pid = fork();
    if (left_pid == -1)
        return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
    
    if (left_pid == 0)
    {
        close(pipe_fd[0]);
        if (input_fd != STDIN_FILENO)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        exit(execute_ast(node, env, node->parsing->left));
    }

    right_pid = fork();
    if (right_pid == -1)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        waitpid(left_pid, &left_status, 0);
        return (1);
    }

    if (right_pid == 0)
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        exit(execute_ast(node, env, node->parsing->right));
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    if (input_fd != STDIN_FILENO)
        close(input_fd);

    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);

    return (WEXITSTATUS(right_status));
}