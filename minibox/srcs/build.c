/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:14:17 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 21:35:45 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

int	ft_build_minibox(t_minibox *minibox, const char *str, char **envp)
{
	if (!minibox)
		return (-1);
	ft_set_minibox_error(minibox, MINICODE_NONE);
	ft_build_minibox_input(minibox, str, envp);
	if (minibox->error.code != MINICODE_NONE)
		return (minibox->error.code);
	ft_build_minibox_lexing(minibox);
	if (minibox->error.code != MINICODE_NONE)
		return (minibox->error.code);
	ft_build_minibox_parsing(minibox);
	if (minibox->error.code != MINICODE_NONE)
		return (minibox->error.code);
	return (0);
}
