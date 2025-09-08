/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:27:25 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/07 20:55:40 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

const char	**ft_get_type_names(void)
{
	static const char	*mininames[MINITYPE_SIZE + 1] = {
	[MINITYPE_AND] = "MINITYPE_AND",
	[MINITYPE_OR] = "MINITYPE_OR",
	[MINITYPE_PIPE] = "MINITYPE_PIPE",
	[MINITYPE_CMD] = "MINITYPE_CMD",
	[MINITYPE_SUBSHELL] = "MINITYPE_SUBSHELL",
	[MINITYPE_REDAPP] = "MINITYPE_REDAPP",
	[MINITYPE_HEREDOC] = "MINITYPE_HEREDOC",
	[MINITYPE_REDOUT] = "MINITYPE_REDOUT",
	[MINITYPE_REDIN] = "MINITYPE_REDIN",
	};

	return (mininames);
}

const char	**ft_get_token_names(void)
{
	static const char	*mininames[MINITOKEN_SIZE + 1] = {
	[MINITOKEN_REDAPP] = "MINITOKEN_REDAPP",
	[MINITOKEN_HEREDOC] = "MINITOKEN_HEREDOC",
	[MINITOKEN_AND] = "MINITOKEN_AND",
	[MINITOKEN_OR] = "MINITOKEN_OR",
	[MINITOKEN_PIPE] = "MINITOKEN_PIPE",
	[MINITOKEN_REDOUT] = "MINITOKEN_REDOUT",
	[MINITOKEN_REDIN] = "MINITOKEN_REDIN",
	[MINITOKEN_LPAREN] = "MINITOKEN_LPAREN",
	[MINITOKEN_RPAREN] = "MINITOKEN_RPAREN",
	[MINITOKEN_DQUOTE] = "MINITOKEN_DQUOTE",
	[MINITOKEN_SQUOTE] = "MINITOKEN_SQUOTE",
	[MINITOKEN_UQUOTE] = "MINITOKEN_UQUOTE",
	[MINITOKEN_WSPACE] = "MINITOKEN_WSPACE",
	};

	return (mininames);
}

const char	**ft_get_token_operators(void)
{
	static const char	*miniops[MINITOKEN_SIZE + 1] = {
	[MINITOKEN_REDAPP] = ">>",
	[MINITOKEN_HEREDOC] = "<<",
	[MINITOKEN_AND] = "&&",
	[MINITOKEN_OR] = "||",
	[MINITOKEN_PIPE] = "|",
	[MINITOKEN_REDOUT] = ">",
	[MINITOKEN_REDIN] = "<",
	[MINITOKEN_LPAREN] = "(",
	[MINITOKEN_RPAREN] = ")",
	};

	return (miniops);
}

const char	**ft_get_error_names(void)
{
	static const char	*mininames[MINICODE_SIZE + 1] = {
	[MINICODE_NONE] = "MINICODE_NONE",
	[MINICODE_ERRNO] = "MINICODE_ERRNO",
	[MINICODE_INPUT_NULL] = "MINICODE_INPUT_NULL",
	[MINICODE_INPUT_BLANK] = "MINICODE_INPUT_BLANK",
	[MINICODE_UNCLOSED_QUOTES] = "MINICODE_UNCLOSED_QUOTES",
	[MINICODE_UNCLOSED_PARENTHESIS] = "MINICODE_UNCLOSED_PARENTHESIS",
	[MINICODE_UNDEFINED] = "MINICODE_UNDEFINED",
	};

	return (mininames);
}

const char	**ft_get_error_msgs(void)
{
	static const char	*minimsg[MINICODE_SIZE + 1] = {
	[MINICODE_NONE] = "No error.",
	[MINICODE_ERRNO] = "System error (see errno).",
	[MINICODE_INPUT_NULL] = "Null input.",
	[MINICODE_INPUT_BLANK] = "Blank input.",
	[MINICODE_UNCLOSED_QUOTES] = "Unclosed quotes.",
	[MINICODE_UNCLOSED_PARENTHESIS] = "Unclosed parenthesis.",
	[MINICODE_UNDEFINED] = "Unknown or undefined error.",
	};

	return (minimsg);
}
