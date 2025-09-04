/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/04 23:14:44 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minilexing    *create_token(char *value)
{
    t_minilexing    *token;

    token = malloc(sizeof(t_minilexing));
    token->value = ft_strdup(value);
	token->next = NULL;
	return token;
}

int main(int ac, char **av, char **envp)
{
    char *line;
    char    cwd[1024];
    char **args;
    t_env *env_list;
    int builtin_result;
    char *pwd;
    char    *value_add;
    
    (void)ac;
    (void)av;
    env_list = init_env(envp);
    if (!env_list)
        return (ft_putstr_fd("Error: Failed to initialize env\n", 2), 1);
    ft_dprintf(1, "Minishell avec cd et echo\n");
    ft_dprintf(1, "cmd: cd, echo, pwd, env, export, unset, exit\n");
    ft_dprintf(1, "Tapez 'exit' pour quitter\n\n");
    while (1)
    {
        pwd = getcwd(cwd, sizeof(cwd));
        value_add = ft_strjoin(pwd, "> ");
        //line = readline("\001\033[0;32m\002minishell> \001\033[0m\002");
        line = readline(value_add);
        if (!line)
        {
            ft_dprintf(1, "\nye!\n");
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
            execute_external(args, env_list);
        free(line);
        free_args(args);
    }
    free_env_list(env_list);
    return (0);
}
