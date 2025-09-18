/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_expand.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:56:47 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/18 16:43:36 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static char	*ft_get_env(char *name, char **envp)
{
	static char	buf[32];
	size_t		len;
	size_t		i;

	if (!name || !envp)
		return (NULL);
	i = 0;
	while (i < 32)
		buf[i++] = '\0';
	i = 0;
	len = ft_strlen(name);
	if (ft_strncmp(name, "?", len) == 0)
	{
		ft_sprintf(buf, "%d", (int)g_signal_received);
		return (buf);
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == 61)
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

static void	ft_set_env(t_minibox *mbx, const char *value, char **str,
	size_t ij[2])
{
	char	*env_n;
	char	*env_v;
	char	*tmp_str;

	if (value[ij[0]] && (ft_isalnum(value[ij[0]]) || \
		value[ij[0]] == 95 || value[ij[0]] == 63))
	{
		ij[1] = ij[0];
		while (value[ij[1]] && (ft_isalnum(value[ij[0]]) || \
			value[ij[0]] == 95 || value[ij[0]] == 63))
			ij[1]++;
		env_n = ft_substr(value, ij[0], ij[1] - ij[0]);
		if (!env_n)
			return (ft_set_minibox_error(mbx, MINICODE_ERRNO), free(*str));
		1 && (env_v = ft_get_env(env_n, mbx->input->envp)), free(env_n);
		if (env_v)
			1 && (tmp_str = ft_strjoin(*str, env_v)), ij[0] = ij[1];
		else
			1 && (tmp_str = ft_strdup(*str)), ij[0] = ij[1];
	}
	else
		1 && (tmp_str = ft_strjoin(*str, "$")), ij[0] = ij[1] + 1;
	if (!tmp_str)
		return (ft_set_minibox_error(mbx, MINICODE_ERRNO), free(*str));
	return (free(*str), (*str = tmp_str), (void)env_n);
}

static int	ft_expand_val(t_minibox *minibox, const char *value, char **str,
	size_t ij[2])
{
	char	*sub_str;
	char	*join_str;

	while (value[ij[1]] && value[ij[1]] != 36)
		ij[1]++;
	sub_str = ft_substr(value, ij[0], ij[1] - ij[0]);
	if (!sub_str)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), free(*str), 1);
	1 && (join_str = ft_strjoin(*str, sub_str)), free(sub_str);
	if (!join_str)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), free(*str), 1);
	free(*str);
	1 && (*str = ft_strdup(join_str)), free(join_str);
	if (!*str)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 1);
	if (value[ij[1]] == 36)
	{
		1 && (ij[0] = ij[1] + 1), ft_set_env(minibox, value, str, ij);
		if (minibox->error.code != MINICODE_NONE)
			return (1);
	}
	else
		ij[0] = ij[1];
	return (0);
}

char	*ft_get_expand_val(t_minibox *minibox, const t_minilexing *lexing)
{
	char	*str;
	size_t	ij[2];

	if (lexing->token == MINITOKEN_SQUOTE)
		str = ft_strdup(lexing->value);
	else
	{
		1 && (ij[0] = 0), str = ft_strdup("");
		if (!str)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
		if (minibox->error.code != MINICODE_NONE)
			return (NULL);
		while (lexing->value[ij[0]])
		{
			ij[1] = ij[0];
			ft_expand_val(minibox, lexing->value, &str, ij);
			if (minibox->error.code != MINICODE_NONE)
				return (NULL);
		}
	}
	if (!str)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	return (str);
}
