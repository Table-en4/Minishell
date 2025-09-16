#include "minishell.h"

int	execute_minibox(t_minibox *minibox, t_env *env)
{
	int	exit_code;

	if (!minibox)
		return (1);
	if (minibox->error.code != MINICODE_NONE)
		return (ft_display_minibox_error(minibox->error), 1);
	if (!minibox->parsing)
	{
		return (1);
	}
	return (exit_code = execute_ast(minibox, minibox->parsing, env), exit_code);
}
