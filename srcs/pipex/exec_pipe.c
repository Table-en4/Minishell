/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:37:58 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int left_exec(pid_t left_pid, t_miniparsing *node, int input_fd, t_env *env)
{
    int pip_fd[2];

    if (pipe(pip_fd) == -1)
        return (1);
    left_pid = fork();
    if (left_pid == -1)
        return (close(pip_fd[0]), close(pip_fd[1]), 1);
    if (left_pid == 0)
    {
        if (input_fd != STDIN_FILENO)
            dup2(input_fd, STDIN_FILENO);
        dup2(pip_fd[1], STDOUT_FILENO);
        close(pip_fd[0]);
        close(pip_fd[1]);
        exit(execute_ast(node->left, env));
    }
    return (0);
}

int right_exec(pid_t right_pid, t_miniparsing *node, int input_fd, t_env *env)
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
        return (1);
    right_pid = fork();
    if (right_pid == -1)
        return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
    if (right_pid == 0)
    {
        if (input_fd != STDIN_FILENO)
            dup2(input_fd, STDIN_FILENO);
        dup2(pipe_fd[0], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        exit(execute_ast(node->right, env));
    }
    return (0);
}

int exec_pipe(t_miniparsing *node, int input_fd, t_env *env)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int     status;
    int     exit_code;

    left_pid = fork();
    right_pid = fork();
    left_exec(left_pid, node, input_fd, env);
    right_exec(right_pid, node, input_fd, env);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &exit_code, 0);
    return (WEXITSTATUS(exit_code));
}
