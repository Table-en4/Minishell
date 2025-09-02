/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lexing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:59:14 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/02 21:46:40 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_destroy_minibox_lexing(t_minibox *minibox)
{
	t_minilexing	*curr_node;
	t_minilexing	*next_node;

	if (!minibox || !minibox->lexing)
		return ;
	while (minibox->lexing->prev)
		minibox->lexing = minibox->lexing->prev;
	curr_node = minibox->lexing;
	while (curr_node)
	{
		next_node = curr_node->next;
		if (curr_node->value)
			free(curr_node->value);
		free(curr_node);
		curr_node = next_node;
	}
	minibox->lexing = NULL;
}
