/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:56:17 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/13 23:47:34 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox.h"
#include "../Libft/incs/libft.h"
#include "../Libft/incs/ft_dprintf.h"

int	main(int argc, char **argv, char **envp)
{
	t_minibox	*minibox;
	char		*cmd;

	minibox = ft_calloc(1, sizeof(t_minibox));
	if (!minibox)
		return (EXIT_FAILURE);
	if (argc != 2)
	{
		cmd = "$USER '$USER' \"$USER\" '\"$USER\"' \"'$USER'\"";
		ft_build_minibox(minibox, cmd, envp);
		ft_display_minibox(minibox);
		ft_destroy_minibox(minibox);
		return (free(minibox), EXIT_SUCCESS);
	}
	cmd = argv[1];
	ft_build_minibox(minibox, cmd, envp);
	ft_display_minibox(minibox);
	ft_destroy_minibox(minibox);
	return (free(minibox), EXIT_SUCCESS);
}
