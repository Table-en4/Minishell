/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:57:10 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/17 19:12:35 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_numeric_atoi(char *str, t_env **envp, char **args)
{
	int	i;

	(void)envp;
	(void)args;
	i = 0;
	if (str[i] == '\0')
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", str);
		return (-1);
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				str);
			return (-1);
		}
		i++;
	}
	return (ft_atoi(str));
}

int	ft_exit(char **args, t_env **envp)
{
	int	exit_value;

	(void)envp;
	exit_value = 0;
	if (!args[1])
	{
		ft_dprintf(1, "exit\n");
		return (EXIT_SHELL_CODE);
	}
	else if (!args[2])
	{
		exit_value = ft_numeric_atoi(args[1], envp, args);
		if (exit_value == -1)
		{
			ft_dprintf(1, "exit\n");
			return (EXIT_SHELL_CODE + 2);
		}
		exit_value = exit_value % 256;
		ft_dprintf(1, "exit\n");
		return (EXIT_SHELL_CODE + exit_value);
	}
	else
		return (ft_dprintf(2, "minishell: exit: too many arguments\n"), 1);
	return (0);
}
