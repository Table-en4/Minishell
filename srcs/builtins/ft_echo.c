/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:30:06 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/30 03:15:36 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 1;
	while (arg[j] == 'n')
		j++;
	if (arg[j] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **av)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (av[i] && is_n_option(av[i]))
	{
		no_newline = 1;
		while (av[i] && is_n_option(av[i]))
			i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
