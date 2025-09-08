/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:34:19 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/06 22:49:45 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_display_minibox_error(const t_minierror error)
{
	const char	**mininames = ft_get_error_names();
	char		*mininame;

	mininame = (char *)mininames[error.code];
	ft_printf("     ├─── code: %s\n", mininame);
	ft_printf("     └─── msg: [%s]\n", error.msg);
}
