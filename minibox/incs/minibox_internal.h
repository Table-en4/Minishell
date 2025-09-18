/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibox_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:23:54 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/17 22:36:16 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBOX_INTERNAL_H
# define MINIBOX_INTERNAL_H

# include <readline/readline.h>
# include <limits.h>
# include <fcntl.h>
# include <stdint.h>
# include <errno.h>
# include <dirent.h>
# include "minibox.h"
# include "../Libft/incs/libft.h"
# include "../Libft/incs/get_next_line.h"
# include "../Libft/incs/ft_printf.h"
# include "../Libft/incs/ft_dprintf.h"
# include "../Libft/incs/ft_sprintf.h"

# define MINITREE_MAX_DEPTH 16

void			ft_set_minibox_error(t_minibox *minibox, t_minicode code);

void			ft_build_minibox_input(t_minibox *minibox, const char *cmd,
					char **envp);
void			ft_build_minibox_lexing(t_minibox *minibox);
void			ft_build_minibox_parsing(t_minibox *minibox);

int				ft_isred(const t_minitoken token);
t_minitype		ft_cnv_token_to_type(const t_minitoken token);
size_t			ft_find_tokens(t_minibox *minibox, t_minilexing **lexing,
					const size_t lexing_len, t_minitoken *tokens);
t_miniparsing	*ft_new_node(t_minibox *minibox, t_miniparsing *parent,
					const t_minitype type);

void			ft_build_parsing_argc(t_minibox *minibox, t_miniparsing *node,
					const t_minilexing *lexing, const size_t lexing_len);
void			ft_build_parsing_argv(t_minibox *minibox, t_miniparsing *node,
					const t_minilexing *lexing, const size_t lexing_len);
char			*ft_get_expand_val(t_minibox *minibox,
					const t_minilexing *lexing);
char			**ft_expand_wildcard(t_minibox *minibox, const char *pattern,
					size_t *count);
void			ft_sort_str_array(char **array, int count);
int				ft_wildcard_match(const char *pattern, const char *str);

size_t			ft_skip_subshell(t_minibox *minibox, t_minilexing **lexing,
					const size_t lexing_len);
void			ft_check_syntax_aop(t_minibox *minibox,
					const t_minilexing *lexing);
void			ft_check_syntax_ss(t_minibox *minibox,
					const t_minilexing *lexing, const size_t lexing_len);
void			ft_check_syntax_cmd(t_minibox *minibox,
					const t_minilexing *lexing, const size_t lexing_len);

t_minifd		*ft_build_parsing_red(t_minibox *minibox,
					const t_minilexing *lexing, const size_t lexing_len);
int				ft_open_heredoc(t_minibox *minibox, t_minifd *node);

void			ft_display_minibox_input(const t_miniinput *input);
void			ft_display_minibox_lexing(const t_minilexing *lexing);
void			ft_display_minibox_parsing(const t_miniparsing *parsing);
void			ft_display_minibox_error(const t_minierror error);

void			ft_destroy_minibox_input(t_minibox *minibox);
void			ft_destroy_minibox_lexing(t_minibox *minibox);
void			ft_destroy_minibox_parsing(t_minibox *minibox);

const char		**ft_get_error_names(void);
const char		**ft_get_error_msgs(void);
const char		**ft_get_token_names(void);
const char		**ft_get_token_operators(void);
const char		**ft_get_type_names(void);

#endif
