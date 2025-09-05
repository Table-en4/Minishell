/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 19:21:03 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minilexing *create_token(char *value)
{
    t_minilexing    *token;
    
    token = malloc(sizeof(t_minilexing));
    if (!token)
        return NULL;
    token->value = ft_strdup(value);
    token->next = NULL;
    return (token);
}

t_miniparsing *create_command_node(char **args)
{
    t_miniparsing   *node = malloc(sizeof(t_miniparsing));
    int             i = 0;

    if (!node)
        return (NULL);
    node->type = MINITYPE_CMD;
    node->left = NULL;
    node->right = NULL;
    t_minilexing *tokens = NULL;
    t_minilexing *current = NULL;
    while (args[i])
    {
        t_minilexing *new_token = create_token(args[i]);
        if (!new_token)
        {
            while (tokens)
            {
                t_minilexing *tmp = tokens;
                tokens = tokens->next;
                free(tmp->value);
                free(tmp);
            }
            return (free(node), NULL);
        }
        if (!tokens)
            tokens = new_token;
        else
            current->next = new_token;
        current = new_token;
        i++;
    }
    return (node->lexing = tokens, node);
}

void free_tokens(t_minilexing *tokens)
{
    while (tokens)
    {
        t_minilexing *next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}

void free_ast(t_miniparsing *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    free_tokens(node->lexing);
    free(node);
}

int main(int ac, char **av, char **envp)
{
    char *line;
    char cwd[1024];
    char **args;
    t_env *env_list;
    int builtin_result;
    char *pwd;
    char *value_add;
    
    (void)ac;
    (void)av;
    env_list = init_env(envp);
    if (!env_list)
        return (ft_putstr_fd("Error: Failed to initialize env\n", 2), 1);
    ft_dprintf(1, "Minishell avec cd et echo\n");
    ft_dprintf(1, "cmd: cd, echo, pwd, env, export, unset, exit\n");
    ft_dprintf(1, "\e[41mTapez 'exit' pour quitter\e[0m\n\n");
    while (1)
    {
        pwd = getcwd(cwd, sizeof(cwd));
        value_add = ft_strjoin(pwd, "> ");
        line = readline(value_add);
        free(value_add);
        if (!line)
        {
            ft_dprintf(1, "\nbye!\n");
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
        if (ft_strcmp(args[0], "testast") == 0)
        {
            //put un NULL a la fin de la commande pour le \0 ca evite le seg fault
            char *test_args[] = {"echo", "hello my g", NULL};
            t_miniparsing *ast_testing = create_command_node(test_args);
            int result = execute_ast(ast_testing, env_list);
            printf("Resultat de l'execution: %d\n", result);
            free_ast(ast_testing);
        }
        else
        {
            builtin_result = execute_builtin(args, &env_list);
            if (builtin_result == -1)
                execute_external(args, env_list);
        }
        free(line);
        free_args(args);
    }
    return (free_env_list(env_list), 0);
}
