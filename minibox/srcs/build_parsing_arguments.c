/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:25:24 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/13 23:35:08 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static char	*ft_get_env(const char *name, char **envp)
{
	size_t	name_len;
	int		i;

	if (!name || !envp)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0)
		{
			if (envp[i][name_len] == '=')
				return (envp[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

static size_t	ft_get_expanded_len(const char *value, char **envp,
	t_minitoken token)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*var_name;
	char	*var_value;
	int		in_squote;

	len = 0;
	i = 0;
	in_squote = 0;
	while (value[i])
	{
		if (token == MINITOKEN_UQUOTE && value[i] == '\'')
		{
			in_squote = !in_squote;
			len++;
			i++;
			continue ;
		}
		if (!in_squote && value[i] == '$'
			&& (ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			j = i + 1;
			while (ft_isalnum(value[j]) || value[j] == '_')
				j++;
			var_name = ft_substr(value, i + 1, j - (i + 1));
			if (var_name)
			{
				var_value = ft_get_env(var_name, envp);
				if (var_value)
					len += ft_strlen(var_value);
				free(var_name);
			}
			i = j;
		}
		else
			1 && (len++, i++);
	}
	return (len);
}

static void	ft_do_expand(char *expanded, const char *value, char **envp,
	t_minitoken token)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*var_name;
	char	*var_value;
	int		in_squote;

	i = 0;
	k = 0;
	in_squote = 0;
	while (value[i])
	{
		if (token == MINITOKEN_UQUOTE && value[i] == '\'')
		{
			in_squote = !in_squote;
			expanded[k++] = value[i++];
			continue ;
		}
		if (!in_squote && value[i] == '$'
			&& (ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			j = i + 1;
			while (ft_isalnum(value[j]) || value[j] == '_')
				j++;
			var_name = ft_substr(value, i + 1, j - (i + 1));
			if (var_name)
			{
				var_value = ft_get_env(var_name, envp);
				if (var_value)
					k += ft_strlcpy(&expanded[k], var_value,
							ft_strlen(var_value) + 1);
				free(var_name);
			}
			i = j;
		}
		else
			expanded[k++] = value[i++];
	}
	expanded[k] = '\0';
}

static char	*ft_expand_argv(t_minibox *minibox, const t_minilexing *lexing)
{
	char	*expanded_value;
	size_t	expanded_len;

	if (lexing->token == MINITOKEN_SQUOTE)
		return (ft_strdup(lexing->value));
	if (!minibox->input || !minibox->input->envp)
		return (ft_strdup(lexing->value));
	expanded_len = ft_get_expanded_len(lexing->value, minibox->input->envp,
			lexing->token);
	expanded_value = ft_calloc(expanded_len + 1, sizeof(char));
	if (!expanded_value)
		return (NULL);
	ft_do_expand(expanded_value, lexing->value, minibox->input->envp,
		lexing->token);
	return (expanded_value);
}

void	ft_build_parsing_argv(t_minibox *minibox, t_miniparsing *node,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing && i < lexing_len)
	{
		if (ft_isred(curr_lexing->token))
		{
			1 && (i++), curr_lexing = curr_lexing->next;
			if (curr_lexing && curr_lexing->token == MINITOKEN_WSPACE && i++)
				curr_lexing = curr_lexing->next;
		}
		else if (curr_lexing->token != MINITOKEN_WSPACE)
		{
			node->argv[j] = ft_expand_argv(minibox, curr_lexing);
			if (!node->argv[j++])
				ft_set_minibox_error(minibox, MINICODE_ERRNO);
			if (minibox->error.code != MINICODE_NONE)
				return ;
		}
		1 && (i++), curr_lexing = curr_lexing->next;
	}
}

void	ft_build_parsing_argc(t_miniparsing *node,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			i;

	i = 0;
	curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing && i < lexing_len)
	{
		if (ft_isred(curr_lexing->token))
		{
			1 && (i++), curr_lexing = curr_lexing->next;
			if (curr_lexing && curr_lexing->token == MINITOKEN_WSPACE && i++)
				curr_lexing = curr_lexing->next;
		}
		else if (curr_lexing->token != MINITOKEN_WSPACE)
			node->argc++;
		i++;
		curr_lexing = curr_lexing->next;
	}
}
