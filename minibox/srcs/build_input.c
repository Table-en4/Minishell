/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:13:59 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 21:43:40 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_isspaces(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isspace(str[i++]))
			return (0);
	return (1);
}

void	ft_build_minibox_input(t_minibox *minibox, const char *cmd, char **envp)
{
	if (!cmd)
		ft_set_minibox_error(minibox, MINICODE_INPUT_NULL);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (ft_isspaces(cmd))
		ft_set_minibox_error(minibox, MINICODE_INPUT_BLANK);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	minibox->input = ft_calloc(1, sizeof(t_miniinput));
	if (!minibox->input)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	minibox->input->envp = envp;
	minibox->input->cmd = ft_strdup(cmd);
	if (!minibox->input->cmd)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
}
