/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:04:44 by raamayri          #+#    #+#             */
/*   Updated: 2025/08/31 15:35:51 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static void	ft_display_minibox_input(const t_minibox *minibox)
{
	const t_miniinput	*input = minibox->input;

	ft_printf("│    ├─── value: [%s]\n", input->value);
	ft_printf("│    └─── length: %d\n", input->length);
}

static void	ft_display_minibox_lexing(const t_minibox *minibox)
{
	const char		**token_names = ft_get_token_names();
	t_minilexing	*curr_lexing;

	curr_lexing = minibox->lexing;
	while (curr_lexing)
	{
		if (!curr_lexing->next)
		{
			ft_printf("│    └─── token: %s (%d)\n",
				token_names[curr_lexing->token], curr_lexing->token);
			ft_printf("│         ├─── value: [%s]\n", curr_lexing->value);
			ft_printf("│         └─── length: %d\n", curr_lexing->length);
			break ;
		}
		ft_printf("│    ├─── token: %s (%d)\n",
			token_names[curr_lexing->token], curr_lexing->token);
		ft_printf("│    │    ├─── value: [%s]\n", curr_lexing->value);
		ft_printf("│    │    └─── length: %d\n", curr_lexing->length);
		curr_lexing = curr_lexing->next;
	}
}

void	ft_display_minibox(const t_minibox *minibox)
{
	const char	**mininame = ft_get_error_names();

	if (!minibox)
		return ;
	ft_printf("minibox\n");
	ft_printf("├─── input %p\n", minibox->input);
	if (minibox->input)
		ft_display_minibox_input(minibox);
	ft_printf("├─── lexing: %p\n", minibox->lexing);
	if (minibox->lexing)
		ft_display_minibox_lexing(minibox);
	ft_printf("├─── parsing: %p\n", minibox->parsing);
	// TODO: Expand parsing display
	ft_printf("└─── error\n");
	ft_printf("     ├─── code: %s (%d)\n",
		mininame[minibox->error.code], minibox->error.code);
	ft_printf("     └─── msg: [%s]\n", minibox->error.msg);
}
