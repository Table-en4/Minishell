#include "minibox.h"
#include "minishell.h"

int exec_pipe(t_miniparsing *node, int input_fd, t_env *env)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int     status;
    int     exit_code;

    if (pipe(pipe_fd) == -1)
        return (1);
    left_pid = fork();
    if (left_pid == -1)
        return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
    if (left_pid == 0)
    {
        if (input_fd != STDIN_FILENO)
            dup2(input_fd, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        exit(execute_ast(node->left, env));
    }
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
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &status, 0);
    return (WEXITSTATUS(exit_code));
}
