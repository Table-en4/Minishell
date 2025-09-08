/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_lexing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:35:55 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/07 20:08:26 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_display_minibox_lexing(const t_minilexing *lexing)
{
	t_minilexing	*curr_lexing;
	const char		**mininames = ft_get_token_names();
	char			*mininame;
	char			**link;

	if (!lexing)
		return ;
	curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing)
	{
		link = (char *[2]){"├", "│"};
		if (curr_lexing->next == NULL)
			link = (char *[2]){"└", " "};
		mininame = (char *)mininames[curr_lexing->token];
		ft_printf("│    %s─── token: %s\n", link[0], mininame);
		ft_printf("│    %s    ├─── value: [%s]\n", link[1], curr_lexing->value);
		ft_printf("│    %s    └─── length: %d\n", link[1], curr_lexing->length);
		curr_lexing = curr_lexing->next;
	}
}
