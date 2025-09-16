/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:35:57 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 21:39:17 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_display_minibox_input(const t_miniinput *input)
{
	if (!input)
		return ;
	ft_printf("│    ├─── envp: ");
	if (!input->envp)
		ft_printf("NULL\n");
	else if (!input->envp[0])
		ft_printf("[]\n");
	else
	{
		ft_printf("[[%s]", input->envp[0]);
		if (input->envp[1])
			ft_printf("...");
		ft_printf("]\n");
	}
	ft_printf("│    └─── cmd: [%s]\n", input->cmd);
}
