/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:03:59 by molapoug         ###   ########.fr       */
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

int exec_pipe_chain(t_minibox *minibox, t_env *env, t_miniparsing *node)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    int     left_status;
    int     right_status;
    int     stdin_backup;

    if (pipe(pipe_fd) == -1)
        return (perror("pipe"), 1);
    left_pid = fork();
    if (left_pid == -1)
        return(perror("fork"), close(pipe_fd[0]), close(pipe_fd[1]), 1);
    if (left_pid == 0)
    {
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(pipe_fd[1]);
        exit(execute_parsing_node(minibox, env, node->left));
    }
    else
    {
        close(pipe_fd[1]);
        stdin_backup = dup(STDIN_FILENO);
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
            return (perror("dup2"), close(pipe_fd[0]), close(stdin_backup), 1);
        close(pipe_fd[0]);
        right_status = exec_pipe_chain(minibox, env, node->right);
        dup2(stdin_backup, STDIN_FILENO);
        close(stdin_backup);
        return (waitpid(left_pid, &left_status, 0), right_status);
    }
}

int alternative_chain(t_minibox *minibox, t_env *env, t_miniparsing *node)
{
    int     pipe_fd[2][2];
    pid_t   pids[2];
    int     status[2];
    int     i;

    if (!node || node->type != MINITYPE_PIPE)
        return (execute_parsing_node(minibox, env, node));
    if (pipe(pipe_fd[0]) == -1)
        return (perror("pipe"), 1);
    pids[0] = fork();
    if (pids[0] == -1)
        return (perror("fork"), close(pipe_fd[0][0]), close(pipe_fd[0][1]), 1);
    if (pids[0] == 0)
    {
        close(pipe_fd[0][0]);
        dup2(pipe_fd[0][1], STDIN_FILENO);
        close(pipe_fd[0][1]);
        exit(execute_parsing_node(minibox, env, node->left));
    }
    pids[1] = fork();
    if (pids[1] == -1)
    {
        close(pipe_fd[0][0]);
        close(pipe_fd[0][1]);
        kill(pids[0], &status[0], 0);
        return (perror("fork"), 1);
    }
    if (pids[1] == 0)
    {
        close(pipe_fd[0][1]);
        dup2(pipe_fd[0][0], STDIN_FILENO);
        close(pipe_fd[0][0]);
        exit(exec_pipe_chain(minibox, env, node->right));
    }
    close(pipe_fd[0][0]);
    close(pipe_fd[0][1]);
    while (i < 2)
        waitpid(pids[i++], &status[i], 0);
    return (WEXITSTATUS(status[1]));
}
