/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:30 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:57:13 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:30 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/15 14:00:00 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	if (!minibox || !node)
		return (1);
	return (execute_node(minibox, node, env));
}

int	execute_node(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	if (node->type == MINITYPE_CMD)
		return (exec_command(minibox, node, env));
	else if (node->type == MINITYPE_PIPE)
		return (exec_pipe(minibox, node, env));
	else if (node->type == MINITYPE_AND)
		return (exec_and(minibox, node, env));
	else if (node->type == MINITYPE_OR)
		return (exec_or(minibox, node, env));
	else if (node->type == MINITYPE_SUBSHELL)
		return (exec_subshell(minibox, node, env));
	else if (node->type == MINITYPE_REDIN || node->type == MINITYPE_REDOUT ||
		node->type == MINITYPE_REDAPP || node->type == MINITYPE_HEREDOC)
		return (exec_redirection(minibox, node, env));
	return (1);
}
