/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:30 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/06 14:53:18 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_ast(t_minibox *node, t_env *env, t_miniparsing *value)
{
    if (!node)
        return (1);
    if (value->type == MINITYPE_CMD)
        return (exec_command(node, env));
    else if (value->type == MINITYPE_PIPE)
        return (exec_pipe(node, STDIN_FILENO, env));
    else if (value->type == MINITYPE_AND)
        return (exec_and(node, env));
    else if (value->type == MINITYPE_OR)
        return (exec_or(node, env));
    else if (value->type == MINITYPE_REDIN
          || value->type == MINITYPE_REDOUT
          || value->type == MINITYPE_REDAPP
          || value->type == MINITYPE_HEREDOC)
        return (exec_redirection(node, env));
    else if (value->type == MINITYPE_SUBSHELL)
        return (exec_subshell(node, env));
    return (1);
}
