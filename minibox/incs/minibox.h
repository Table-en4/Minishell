/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibox.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:15:46 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/05 12:34:33 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBOX_H
# define MINIBOX_H

# include <stddef.h>

typedef struct s_miniinput
{
	char	*value;
	size_t	length;
}	t_miniinput;

typedef enum e_minitoken
{
	MINITOKEN_REDAPP,
	MINITOKEN_HEREDOC,
	MINITOKEN_AND,
	MINITOKEN_OR,
	MINITOKEN_SQUOTE,
	MINITOKEN_DQUOTE,
	MINITOKEN_REDOUT,
	MINITOKEN_REDIN,
	MINITOKEN_LPAREN,
	MINITOKEN_RPAREN,
	MINITOKEN_PIPE,
	MINITOKEN_TEXT,
	MINITOKEN_SIZE
}	t_minitoken;

typedef struct s_minilexing
{
	t_minitoken			token;
	char				*value;
	size_t				length;
	struct s_minilexing	*next;
	struct s_minilexing	*prev;
}	t_minilexing;

typedef enum e_minitype
{
	MINITYPE_CMD,
	MINITYPE_AND,
	MINITYPE_OR,
	MINITYPE_PIPE,
	MINITYPE_REDIN,
	MINITYPE_REDOUT,
	MINITYPE_REDAPP,
	MINITYPE_HEREDOC,
	MINITYPE_SUBSHELL,
	MINITYPE_SIZE
}	t_minitype;

typedef struct s_miniparsing
{
	t_minitype				type;
	t_minilexing			*lexing;
	struct s_miniparsing	*left;
	struct s_miniparsing	*right;
}	t_miniparsing;

# define MINIMSG_SIZE 256

typedef enum e_minicode
{
	MINICODE_NONE,
	MINICODE_ERRNO,
	MINICODE_INPUT_NULL,
	MINICODE_UNCLOSED_QUOTES,
	MINICODE_UNDEFINED,
	MINICODE_SIZE
}	t_minicode;

typedef struct s_minierror
{
	t_minicode	code;
	char		msg[MINIMSG_SIZE];
}	t_minierror;

typedef struct s_minibox
{	
	t_miniinput		*input;
	t_minilexing	*lexing;
	t_miniparsing	*parsing;
	t_minierror		error;
}	t_minibox;

int		ft_build_minibox(t_minibox *minibox, const char *cmd);
//char	**ft_convert_lexing_to_argv(const t_minilexing *lexing);
void	ft_display_minibox(const t_minibox *minibox);
void	ft_destroy_minibox(t_minibox *minibox);

#endif
