/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:35:10 by raamayri          #+#    #+#             */
/*   Updated: 2025/08/31 15:34:30 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_set_minibox_error(t_minibox *minibox, t_minicode code)
{
	const char	**minimsg = ft_get_error_msgs();

	if (code < 0 || code >= MINICODE_SIZE)
		return ;
	minibox->error.code = code;
	ft_strlcpy(minibox->error.msg, minimsg[code], MINIMSG_SIZE);
}
