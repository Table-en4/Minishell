/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:55:25 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/06 20:28:35 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_destroy_minibox_input(t_minibox *minibox, t_miniinput *input)
{
	if (!minibox || !minibox->input || !input)
		return ;
	if (input->value)
		free(input->value);
	free(input);
	minibox->input = NULL;
}
