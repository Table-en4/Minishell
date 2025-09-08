/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:04:51 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/06 20:30:19 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_destroy_minibox(t_minibox *minibox)
{
	if (!minibox)
		return ;
	if (minibox->input)
		ft_destroy_minibox_input(minibox, minibox->input);
	if (minibox->lexing)
		ft_destroy_minibox_lexing(minibox, minibox->lexing);
	if (minibox->parsing)
		ft_destroy_minibox_parsing(minibox, minibox->parsing);
}
