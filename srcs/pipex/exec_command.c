/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:46 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/08 15:44:37 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int exec_pipe(t_miniparsing *node, int input_fd, t_env *env)
{
    int fd[2];
    pid_t   pid;

    if (pipe(fd) == -1)
        return (perror("pipe"), 1);
    pid = fork();
    if (pid == 0)
    {
        dup2(input_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (input_fd != STDIN_FILENO)
            exit(execute_ast(node->left, env));;
    }
}

char    **ft_convert_lexing_to_argv(t_minibox *lexing)
{
    int             count;
    char            **argv;
    t_minilexing    *current;

    current = lexing->lexing;
    count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    argv = malloc(sizeof(char *) * count + 1);
    if (!argv)
        return (NULL);
    current = lexing->lexing;
    count = 0;
    while (current)
    {
        argv[count] = ft_strdup(current->value);
        current = current->next;
        count++;
    }
    return (argv[count] = NULL, argv);
}*/

int execute_minibox(t_minibox *minibox, t_env *env)
{
    return (execute_parsing(minibox, env, minibox->parsing));
}

int execute_parsing(t_minibox *minibox, t_env *env, t_miniparsing *node)
{
    if (!node)
        return (1);
}

int exec_command(t_minibox *node, t_env *env)
{
    char **argv;
    char *path;
    pid_t pid;

    argv = ft_convert_lexing_to_argv(node);
    if (!argv || !argv[0])
        return (1);
    if (is_builtin(argv[0]))
        return (execute_builtin(argv, &env));
    pid = fork();
    if (pid == 0)
    {
        path = find_path(argv[0], env);
        if (!path)
        {
            ft_dprintf(2 ,"minishell: command not found: ");
            ft_putendl_fd(argv[0], 2);
            exit(127);
        }
        execve(path, argv, env_to_tab(env));
        perror("execve");
        exit(126);
    }
    return (waitpid(pid, NULL, 0), 1);
}

