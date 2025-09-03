#include "minishell.h"

int ft_pwd(char **arg, t_env **envp)
{
    char cwd[1024];

    (void)arg;
    (void)envp;
    if (getcwd(cwd, sizeof(cwd)))
        return (ft_dprintf(1, "%s\n", cwd), 0);
    return (perror("pwd"), 1);
}