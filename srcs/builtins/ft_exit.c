/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:57:10 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/16 17:09:40 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_numeric_atoi(char *str, t_env **envp, char **args)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		ft_dprintf(1, "exit\n");
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", str);
		(rl_clear_history(), free_env_list(*envp), free_args(args));
		exit(2);
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_dprintf(1, "exit\n");
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				str);
			(rl_clear_history(), free_env_list(*envp), free_args(args));
			exit(2);
		}
		i++;
	}
	return (ft_atoi(str));
}

int	ft_exit(char **args, t_env **envp)
{
	int	exit_value;

	exit_value = 0;
	if (!args[1])
	{
		(free_env_list(*envp), free_args(args));
		(rl_clear_history(), ft_dprintf(1, "exit\n"), exit(exit_value));
	}
	else if (!args[2])
	{
		exit_value = ft_numeric_atoi(args[1], envp, args) % 256;
		(free_env_list(*envp), free_args(args));
		(rl_clear_history(), ft_dprintf(1, "exit\n"), exit(exit_value));
	}
	else
		return (ft_dprintf(2, "minishell: exit: too many arguments\n"), 1);
	return (0);
}
