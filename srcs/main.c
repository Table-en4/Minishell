#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char *line;
    char **args;
    t_env *env_list;
    int builtin_result;
    
    (void)ac;
    (void)av;
    
    env_list = init_env(envp);
    if (!env_list)
        return (ft_putstr_fd("Error: Failed to initialize environment\n", 2), 1);
    
    ft_dprintf(1, "Minishell avec cd et echo\n");
    ft_dprintf(1, "Commandes disponibles: cd, echo, pwd, env, exit\n");
    ft_dprintf(1, "Tapez 'exit' pour quitter\n\n");
    
    while (1)
    {
        line = readline("\001\033[0;32m\002minishell> \001\033[0m\002");
        if (!line)
        {
            ft_dprintf(1, "\nGoodbye!\n");
            break;
        }
        if (*line == '\0')
        {
            free(line);
            continue;
        }
        add_history(line);
        args = pasrse_line(line);
        if (!args || !args[0])
        {
            free(line);
            free_args(args);
            continue;
        }
        builtin_result = execute_builtin(args, &env_list);
        if (builtin_result == -1)
        {
            execute_external(args, env_list);
        }
        free(line);
        free_args(args);
    }
    free_env_list(env_list);
    return (0);
}