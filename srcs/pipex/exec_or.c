/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:52 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:37:53 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_or(t_miniparsing *node, t_env *env)
{
    int left_exit;

    left_exit = execute_ast(node->left, env);
    if (left_exit != 0)
        return (execute_ast(node->right, env));
    return (left_exit);
}
