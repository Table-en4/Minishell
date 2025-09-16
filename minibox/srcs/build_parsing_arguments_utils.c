/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:57:37 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 18:58:05 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

int	ft_wildcard_match(const char *pattern, const char *str)
{
	int	i[2];
	int	j[2];
	int	start;

	1 && (i[0] = 0), (i[1] = 0), (j[0] = 0), (j[1] = 0), start = 0;
	while (str[i[1]] != 0)
	{
		if (pattern[j[1]] == 42)
			1 && (start = 1), (i[0] = j[1]), (j[0] = i[1]), j[1]++;
		else if (pattern[j[1]] == str[i[1]])
			1 && (j[1]++), i[1]++;
		else if (start)
			1 && (j[1] = i[0] + 1), (i[1] = j[0] + 1), j[0]++;
		else
			return (0);
	}
	while (pattern[j[1]] == 42)
		j[1]++;
	return (pattern[j[1]] == 0);
}

void	ft_sort_str_array(char **array, int count)
{
	int			ij[2];
	char		*temp;

	ij[0] = 0;
	while (ij[0] < count - 1)
	{
		ij[1] = 0;
		while (ij[1] < count - ij[0] - 1)
		{
			if (ft_strcmp(array[ij[1]], array[ij[1] + 1]) > 0)
			{
				temp = array[ij[1]];
				array[ij[1]] = array[ij[1] + 1];
				array[ij[1] + 1] = temp;
			}
			ij[1]++;
		}
		ij[0]++;
	}
}
