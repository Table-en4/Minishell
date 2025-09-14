/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:13:59 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/13 20:59:41 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minibox_internal.h"

static int	ft_isspaces(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isspace(str[i++]))
			return (0);
	return (1);
}

void	ft_build_minibox_input(t_minibox *minibox, const char *str, char **envp)
{
	minibox->input = ft_calloc(1, sizeof(t_miniinput));
	if (!minibox->input)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (!str)
		ft_set_minibox_error(minibox, MINICODE_INPUT_NULL);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	minibox->input->value = ft_strdup(str);
	if (!minibox->input->value)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	minibox->input->length = ft_strlen(minibox->input->value);
	if (ft_isspaces(minibox->input->value))
		ft_set_minibox_error(minibox, MINICODE_INPUT_BLANK);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	minibox->input->envp = envp;
}
