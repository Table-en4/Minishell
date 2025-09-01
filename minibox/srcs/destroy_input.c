/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:55:25 by raamayri          #+#    #+#             */
/*   Updated: 2025/08/28 18:04:12 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_destroy_minibox_input(t_minibox *minibox)
{
	if (!minibox || !minibox->input)
		return ;
	if (minibox->input->value)
		free(minibox->input->value);
	free(minibox->input);
	minibox->input = NULL;
}
