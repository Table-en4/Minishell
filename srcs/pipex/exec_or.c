/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:52 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/06 15:00:00 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

int	exec_or(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	int	left_exit;

	left_exit = execute_ast(minibox, node->left, env);
	if (left_exit != 0)
		return (execute_ast(minibox, node->right, env));
	return (left_exit);
}
