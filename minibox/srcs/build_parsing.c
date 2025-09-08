/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:19:05 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/06 21:23:27 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

// WARN: Test for the cmd : echo 'Test...' | cat && echo Done.
void	ft_build_minibox_parsing(t_minibox *minibox)
{
	t_miniparsing	*parsing;

	parsing = ft_calloc(1, sizeof(t_miniparsing));
	if (!parsing)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	minibox->parsing = parsing;
	parsing->type = MINITYPE_AND;
	parsing->fds = NULL;
	parsing->argc = 0;
	parsing->argv = NULL;
	parsing->subshell = NULL;

	parsing->left = ft_calloc(1, sizeof(t_miniparsing));
	if (!parsing->left)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->left->type = MINITYPE_PIPE;
	parsing->left->fds = NULL;
	parsing->left->argc = 0;
	parsing->left->argv = NULL;
	parsing->left->subshell = NULL;

	parsing->left->left = ft_calloc(1, sizeof(t_miniparsing));
	if (!parsing->left->left)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->left->left->type = MINITYPE_CMD;
	parsing->left->left->fds = NULL;
	parsing->left->left->argc = 2;
	parsing->left->left->argv = ft_calloc(3, sizeof(char *));
	if (!parsing->left->left->argv)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->left->left->argv[0] = ft_strdup("echo");
	parsing->left->left->argv[1] = ft_strdup("Test...");
	if (!parsing->left->left->argv[0] || !parsing->left->left->argv[1])
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->left->left->subshell = NULL;
	parsing->left->left->left = NULL;
	parsing->left->left->right = NULL;

	parsing->left->right = ft_calloc(1, sizeof(t_miniparsing));
	if (!parsing->left->right)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->left->right->type = MINITYPE_CMD;
	parsing->left->right->fds = NULL;
	parsing->left->right->argc = 1;
	parsing->left->right->argv = ft_calloc(2, sizeof(char *));
	if (!parsing->left->right->argv)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->left->right->argv[0] = ft_strdup("cat");
	if (!parsing->left->right->argv[0])
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->left->right->subshell = NULL;
	parsing->left->right->left = NULL;
	parsing->left->right->right = NULL;

	parsing->right = ft_calloc(1, sizeof(t_miniparsing));
	if (!parsing->right)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->right->type = MINITYPE_CMD;
	parsing->right->fds = NULL;
	parsing->right->argc = 2;
	parsing->right->argv = ft_calloc(3, sizeof(char *));
	if (!parsing->right->argv)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->right->argv[0] = ft_strdup("echo");
	parsing->right->argv[1] = ft_strdup("Done.");
	if (!parsing->right->argv[0] || !parsing->right->argv[1])
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	parsing->right->subshell = NULL;
	parsing->right->left = NULL;
	parsing->right->right = NULL;

	minibox->parsing = parsing;
}
