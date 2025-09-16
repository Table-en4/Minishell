/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_wildcard.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:57:18 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 18:58:50 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_count_wildcard_matches(t_minibox *mbx, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (ft_set_minibox_error(mbx, MINICODE_ERRNO), -1);
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == 46 && pattern[0] != 46) && \
			ft_wildcard_match(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	if (closedir(dir) == -1)
		ft_set_minibox_error(mbx, MINICODE_ERRNO);
	return (count);
}

static char	**ft_handle_no_wildcard_matches(t_minibox *minibox,
	const char *pattern)
{
	char	**matches;

	matches = ft_calloc(2, sizeof(char *));
	if (matches)
		matches[0] = ft_strdup(pattern);
	if (!matches || !matches[0])
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	return (matches);
}

static char	**ft_set_wildcard_matches(t_minibox *minibox, const char *pattern,
	int count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				i;

	dir = opendir(".");
	if (!dir)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), NULL);
	matches = ft_calloc(count + 1, sizeof(char *));
	if (!matches)
	{
		closedir(dir);
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), NULL);
	}
	1 && (i = 0), entry = readdir(dir);
	while (i < count && entry)
	{
		if (!(entry->d_name[0] == 46 && pattern[0] != 46) && \
			ft_wildcard_match(pattern, entry->d_name))
			matches[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	if (closedir(dir) == -1)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	return (matches);
}

char	**ft_expand_wildcard(t_minibox *minibox, const char *pattern,
	size_t *count)
{
	char	**matches;
	int		match_count;

	match_count = ft_count_wildcard_matches(minibox, pattern);
	if (match_count == -1)
		return (NULL);
	if (match_count == 0)
	{
		matches = ft_handle_no_wildcard_matches(minibox, pattern);
		if (minibox->error.code != MINICODE_NONE)
			return (NULL);
		return ((*count = 1), matches);
	}
	matches = ft_set_wildcard_matches(minibox, pattern, match_count);
	if (minibox->error.code != MINICODE_NONE)
		return (NULL);
	ft_sort_str_array(matches, match_count);
	return ((*count = match_count), matches);
}
