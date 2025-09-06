/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:42 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/06 14:56:41 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_and(t_minibox *node, t_env *env)
{
    int left_exit;

    left_exit = execute_ast(node, env, node->parsing->left);
    if (left_exit == 0)
        return (execute_ast(node, env, node->parsing->right));
    return (left_exit);
}
