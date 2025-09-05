/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:42 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:37:43 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_and(t_miniparsing *node, t_env *env)
{
    int left_exit;

    left_exit = execute_ast(node->left, env);
    if (left_exit == 0)
        return (execute_ast(node->right, env));
    return (left_exit);
}
