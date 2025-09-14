/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:04:51 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/12 17:18:41 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_destroy_minibox(t_minibox *minibox)
{
	if (!minibox)
		return ;
	if (minibox->input)
		ft_destroy_minibox_input(minibox);
	if (minibox->lexing)
		ft_destroy_minibox_lexing(minibox);
	if (minibox->parsing)
		ft_destroy_minibox_parsing(minibox);
}
