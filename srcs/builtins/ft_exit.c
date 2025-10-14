/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:57:10 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/14 18:25:54 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args, t_env **envp)
{
	int	exit_value;

	exit_value = 0;
	if (!args[1])
	{
		(free_env_list(*envp), free_args(args));
		(ft_dprintf(1, "exit\n"), exit(exit_value));
	}
	else if (!args[2])
	{
		exit_value = ft_atoi(args[1]) % 256;
		(free_env_list(*envp), free_args(args));
		(ft_dprintf(1, "exit\n"), exit(exit_value));
	}
	else
		return (ft_dprintf(2, "exit: too many arguments\n"), 1);
	return (0);
}
