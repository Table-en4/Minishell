/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:27:25 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/02 21:25:22 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

const char	**ft_get_token_names(void)
{
	static const char	*mininames[MINITOKEN_SIZE + 1] = {
	[MINITOKEN_TEXT] = "MINITOKEN_TEXT",
	[MINITOKEN_SQUOTE] = "MINITOKEN_SQUOTE",
	[MINITOKEN_DQUOTE] = "MINITOKEN_DQUOTE",
	[MINITOKEN_REDIN] = "MINITOKEN_REDIN",
	[MINITOKEN_REDOUT] = "MINITOKEN_REDOUT",
	[MINITOKEN_REDAPP] = "MINITOKEN_REDAPP",
	[MINITOKEN_HEREDOC] = "MINITOKEN_HEREDOC",
	[MINITOKEN_AND] = "MINITOKEN_AND",
	[MINITOKEN_OR] = "MINITOKEN_OR",
	[MINITOKEN_LPAREN] = "MINITOKEN_LPAREN",
	[MINITOKEN_RPAREN] = "MINITOKEN_RPAREN",
	[MINITOKEN_PIPE] = "MINITOKEN_PIPE",
	};

	return (mininames);
}

// INFO: Might handle those operators later :
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
const char	**ft_get_token_operators(void)
{
	static const char	*miniops[MINITOKEN_SIZE + 1] = {
	[MINITOKEN_REDAPP] = ">>",
	[MINITOKEN_HEREDOC] = "<<",
	[MINITOKEN_AND] = "&&",
	[MINITOKEN_OR] = "||",
	[MINITOKEN_REDOUT] = ">",
	[MINITOKEN_REDIN] = "<",
	[MINITOKEN_LPAREN] = "(",
	[MINITOKEN_RPAREN] = ")",
	[MINITOKEN_PIPE] = "|",
	[MINITOKEN_SQUOTE] = "'",
	[MINITOKEN_DQUOTE] = "\"",
	};

	return (miniops);
}

const char	**ft_get_error_names(void)
{
	static const char	*mininames[MINICODE_SIZE + 1] = {
	[MINICODE_NONE] = "MINICODE_NONE",
	[MINICODE_ERRNO] = "MINICODE_ERRNO",
	[MINICODE_INPUT_NULL] = "MINICODE_INPUT_NULL",
	[MINICODE_UNDEFINED] = "MINICODE_UNDEFINED",
	};

	return (mininames);
}

const char	**ft_get_error_msgs(void)
{
	static const char	*minimsg[MINICODE_SIZE + 1] = {
	[MINICODE_NONE] = "No error.",
	[MINICODE_ERRNO] = "A system error occurred (see errno).",
	[MINICODE_INPUT_NULL] = "Input Error: Null or blank input.",
	[MINICODE_UNCLOSED_QUOTES] = "Lexing Error: Unclosed quotes.",
	[MINICODE_UNDEFINED] = "Unknown or undefined error.",
	};

	return (minimsg);
}
