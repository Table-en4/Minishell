/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_minibox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:21:04 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/18 15:07:35 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_minibox(t_minibox *minibox, t_env *env)
{
	if (!minibox)
		return (1);
	if (minibox->error.code != MINICODE_NONE)
		return (ft_dprintf(STDERR_FILENO, "%s\n", minibox->error.msg), 1);
	if (!minibox->parsing)
		return (1);
	return (execute_ast(minibox, minibox->parsing, env));
}
