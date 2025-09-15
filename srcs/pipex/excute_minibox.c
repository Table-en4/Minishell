#include "minishell.h"

int	execute_minibox(t_minibox *minibox, t_env *env)
{
	int	exit_code;

	if (!minibox)
		return (1);
	DEBUG_PRINT("error minibox code: %d\n", minibox->error.code);
	DEBUG_PRINT("parsing error : %p\n", (void *)minibox->parsing);
	if (minibox->error.code != MINICODE_NONE)
		return (ft_display_minibox_error(minibox->error), 1);
	if (!minibox->parsing)
	{
		DEBUG_PRINT("no parsing node found\n");
		return (1);
	}
	DEBUG_PRINT("parsing node type: %d\n", minibox->parsing->type);
	return (exit_code = execute_ast(minibox, minibox->parsing, env), exit_code);
}
