/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:46 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:41:41 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **tokens_to_argv(t_minilexing *tokens)
{
    t_minilexing *current;
    char **argv;
    int count;
    int i;

    if (!tokens)
        return (NULL);

    count = 0;
    current = tokens;
    while (current)
    {
        count++;
        current = current->next;
    }

    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);

    current = tokens;
    i = 0;
    while (current && i < count)
    {
        argv[i] = ft_strdup(current->value);
        if (!argv[i])
        {
            while (--i >= 0)
                free(argv[i]);
            free(argv);
            return (NULL);
        }
        current = current->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

int	execute_parsing_node(t_minibox *minibox, t_env *env, t_miniparsing *node)
{
    int     exit_code;
    int     stdio_backup[3];

    if (!node)
        return (0);
    if (node->fds)
    {
        stdio_backup[0] = dup(STDIN_FILENO);
        stdio_backup[1] = dup(STDIN_FILENO);
        stdio_backup[2] = dup(STDIN_FILENO);
        apply_redirections(node->fds);
    }
    if (node->type == MINITYPE_CMD)
        exit_code = exec_command(minibox, env);
    else if (node->type == MINITYPE_PIPE)
        exit_code = exec_pipe_chain(minibox, env, node);
    else if (node->type == MINITYPE_AND)
        exit_code = exec_and_seq(minibox, env, node);
    else if (node->type == MINITYPE_OR)
        exit_code = exec_or_seq(minibox, env, node);
    else if (node->type == MINITYPE_SUBSHELL)
        exit_code = exec_subshell(minibox, env, node);
    else if ( node->type == MINITYPE_REDIN || node->type == MINITYPE_REDOUT ||
        node->type == MINITYPE_REDAPP || node->type == MINITYPE_HEREDOC)
        exit_code = exec_redirection(minibox, env, node);
    else
        exit_code = 1;
    if (!node->fds)
        restore_stdio(stdio_backup);
    return (exit_code);
}

int execute_minibox(t_minibox *minibox, t_env *env)
{
	int	exit_code;

	if (!minibox || !minibox->parsing)
		return (1);
    if (minibox->error.code != MINICODE_NONE)
        return (ft_display_minibox_error(minibox->error), 1);
	exit_code = execute_parsing_node(minibox, env, minibox->parsing);
	return (exit_code);
}

int exec_command(t_minibox *node, t_env *env)
{
    int exit_code;
    int stdio_backup[3];
    int is_built_in;
    char **argv;

    if (!node || !node->lexing)
        return (1);

    argv = tokens_to_argv(node->lexing);
    if (!argv || !argv[0])
    {
        if (argv)
            ft_free_split(argv);
        return (1);
    }

    stdio_backup[0] = dup(STDIN_FILENO);
    stdio_backup[1] = dup(STDOUT_FILENO);
    stdio_backup[2] = dup(STDERR_FILENO);

    if (node->parsing->fds)
        apply_redirections(node->parsing->fds);

    is_built_in = is_builtin(argv[0]);
    if (is_built_in != -1)
        exit_code = execute_builtin(argv, &env);
    else
        exit_code = execute_external(argv, env);

    restore_stdio(stdio_backup);
    ft_free_split(argv);

    return (exit_code);
}