/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibox.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:15:46 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/06 22:27:19 by raamayri         ###   ########.fr       */
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

// TODO: Handle those operators later :
//       &   - background operator
//       =   - assignment operator
//       \   - escape operator
//       ;   - command separator
//       {}  - command group
//       ;;  - case terminator
//       ;&  - fallthrough to next case (same command list)
//       ;;& - fallthrough to next case (new command list)
//       <<< - here-string
//       >&  - duplicate stdout file descriptor
//       <&  - duplicate stdin file descriptor
//       <>  - open file for reading and writing
//       >|  - force overwrite (even if noclobber is set)
typedef enum e_minitoken
{
	MINITOKEN_REDAPP,
	MINITOKEN_HEREDOC,
	MINITOKEN_AND,
	MINITOKEN_OR,
	MINITOKEN_PIPE,
	MINITOKEN_REDOUT,
	MINITOKEN_REDIN,
	MINITOKEN_LPAREN,
	MINITOKEN_RPAREN,
	MINITOKEN_DQUOTE,
	MINITOKEN_SQUOTE,
	MINITOKEN_UQUOTE,
	MINITOKEN_WSPACE,
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
	MINITYPE_AND,
	MINITYPE_OR,
	MINITYPE_PIPE,
	MINITYPE_CMD,
	MINITYPE_SUBSHELL,
	MINITYPE_REDAPP,
	MINITYPE_HEREDOC,
	MINITYPE_REDOUT,
	MINITYPE_REDIN,
	MINITYPE_SIZE
}	t_minitype;

typedef struct s_minifd
{
	t_minitype		type;
	char			*file;
	int				fd;
	struct s_minifd	*next;
	struct s_minifd	*prev;
}	t_minifd;

typedef struct s_miniparsing
{
	t_minitype				type;
	size_t					argc;
	char					**argv;
	t_minifd				*fds;
	struct s_miniparsing	*subshell;
	struct s_miniparsing	*left;
	struct s_miniparsing	*right;
}	t_miniparsing;

# define MINIMSG_SIZE 256

typedef enum e_minicode
{
	MINICODE_NONE,
	MINICODE_ERRNO,
	MINICODE_INPUT_NULL,
	MINICODE_INPUT_BLANK,
	MINICODE_UNCLOSED_QUOTES,
	MINICODE_UNCLOSED_PARENTHESIS,
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
void	ft_display_minibox(const t_minibox *minibox);
void	ft_destroy_minibox(t_minibox *minibox);

#endif
