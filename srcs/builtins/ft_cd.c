/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:04:38 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/29 12:48:27 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **av)
{
    DIR *doss;
    //struct dirent *entre;
    
    if (ft_strcmp(av[1], "cd") ==0)
    {
        doss = opendir(av[2]);
        if (doss == NULL)
            chdir("/usr");
        else
            chdir(av[2]);
    }
    return (0);
}