/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibox_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:23:54 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/07 21:00:50 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBOX_INTERNAL_H
# define MINIBOX_INTERNAL_H

# include <fcntl.h>
# include "minibox.h"
# include "../Libft/incs/libft.h"
# include "../Libft/incs/get_next_line.h"
# include "../Libft/incs/ft_printf.h"
# include "../Libft/incs/ft_dprintf.h"
# include "../Libft/incs/ft_sprintf.h"

void	ft_set_minibox_error(t_minibox *minibox, t_minicode code);

void	ft_build_minibox_input(t_minibox *minibox, const char *cmd);
void	ft_build_minibox_lexing(t_minibox *minibox);
void	ft_build_minibox_parsing(t_minibox *minibox);

void	ft_display_minibox_input(const t_miniinput *input);
void	ft_display_minibox_lexing(const t_minilexing *lexing);
void	ft_display_minibox_parsing(const t_miniparsing *parsing);
void	ft_display_minibox_error(const t_minierror error);

void	ft_destroy_minibox_input(t_minibox *minibox, t_miniinput *input);
void	ft_destroy_minibox_lexing(t_minibox *minibox, t_minilexing *lexing);
void	ft_destroy_minibox_parsing(t_minibox *minibox, t_miniparsing *parsing);

typedef const char	t_cchar;

t_cchar	**ft_get_error_names(void);
t_cchar	**ft_get_error_msgs(void);
t_cchar	**ft_get_token_names(void);
t_cchar	**ft_get_token_operators(void);
t_cchar	**ft_get_type_names(void);

#endif
