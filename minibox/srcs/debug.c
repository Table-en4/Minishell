/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:56:17 by raamayri          #+#    #+#             */
/*   Updated: 2025/08/31 17:18:43 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox.h"
#include "../Libft/incs/libft.h"
#include "../Libft/incs/ft_dprintf.h"

static char	*ft_join_args(int argc, char **argv)
{
	char	*res;
	size_t	res_len[2];
	size_t	i;

	i = 0;
	res_len[0] = 0;
	while (i < (size_t)argc)
		res_len[0] += ft_strlen(argv[i++]) + 1;
	if (res_len[0] == 0)
		return (NULL);
	res = ft_calloc(res_len[0], sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < (size_t)argc)
	{
		res_len[1] = ft_strlen(res);
		ft_strlcpy(&res[res_len[1]], argv[i], res_len[0] - res_len[1]);
		if (i++ < (size_t)argc - 1)
			ft_strlcat(res, " ", res_len[0]);
	}
	return (res);
}

int	main(int argc, char **argv)
{
	t_minibox	*minibox;
	char		*cmd;
	int			err;

	if (argc == 1)
		return (EXIT_SUCCESS);
	minibox = ft_calloc(1, sizeof(t_minibox));
	if (!minibox)
		return (EXIT_FAILURE);
	cmd = ft_join_args(argc - 1, &argv[1]);
	if (!cmd)
		return (free(minibox), EXIT_FAILURE);
	err = ft_build_minibox(minibox, cmd);
	if (err < 0)
	{
		ft_dprintf(STDERR_FILENO, "Error: Minibox is NULL.\n");
		return (free(cmd), EXIT_FAILURE);
	}
	ft_display_minibox(minibox);
	ft_destroy_minibox(minibox);
	return (free(minibox), free(cmd), EXIT_SUCCESS);
}
