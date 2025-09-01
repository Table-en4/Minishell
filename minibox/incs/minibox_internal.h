/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibox_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:23:54 by raamayri          #+#    #+#             */
/*   Updated: 2025/08/31 17:37:40 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBOX_INTERNAL_H
# define MINIBOX_INTERNAL_H

# include "minibox.h"

# include "../Libft/incs/libft.h"
# include "../Libft/incs/get_next_line.h"
# include "../Libft/incs/ft_printf.h"
# include "../Libft/incs/ft_dprintf.h"
# include "../Libft/incs/ft_sprintf.h"

void		ft_set_minibox_error(t_minibox *minibox, t_minicode code);

void		ft_build_minibox_input(t_minibox *minibox, const char *cmd);
void		ft_build_minibox_lexing(t_minibox *minibox);
void		ft_build_minibox_parsing(t_minibox *minibox);

void		ft_destroy_minibox_input(t_minibox *minibox);
void		ft_destroy_minibox_lexing(t_minibox *minibox);
void		ft_destroy_minibox_parsing(t_minibox *minibox);

const char	**ft_get_token_operators(void);
const char	**ft_get_error_msgs(void);
const char	**ft_get_error_names(void);
const char	**ft_get_token_names(void);

#endif
