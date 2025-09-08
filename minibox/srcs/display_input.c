/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:35:57 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/06 22:45:16 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_display_minibox_input(const t_miniinput *input)
{
	if (!input)
		return ;
	ft_printf("│    ├─── value: [%s]\n", input->value);
	ft_printf("│    └─── length: %d\n", input->length);
}
