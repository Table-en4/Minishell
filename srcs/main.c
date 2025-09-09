/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/08 21:20:33 by molapoug         ###   ########.fr       */
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

t_minibox *create_command_node(char **args)
{
    t_minibox *node = malloc(sizeof(t_minibox));
    if (!node)
        return (NULL);
    
    node->parsing = malloc(sizeof(t_miniparsing));
    if (!node->parsing)
        return (free(node), NULL);
    
    node->parsing->type = MINITYPE_CMD;
    node->parsing->left = NULL;
    node->parsing->right = NULL;
    
    t_minilexing *tokens = NULL;
    t_minilexing *current = NULL;
    int i = 0;

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
            free(node->parsing);
            free(node);
            return NULL;
        }
        if (!tokens)
            tokens = new_token;
        else
            current->next = new_token;
        current = new_token;
        i++;
    }
    node->lexing = tokens;
    return (node);
}

void free_token_list(t_minilexing *tokens)
{
    while (tokens)
    {
        t_minilexing *tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_ast(t_miniparsing *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

//version simplifiée pour contourner le problème de minibox temporairement
int execute_simple_command(char *line, t_env *env_list)
{
    char **args;
    char *trimmed;
    int result;
    int is_built_in;
    
    trimmed = ft_strtrim(line, " \t\n");
    if (!trimmed || !*trimmed)
    {
        if (trimmed)
            free(trimmed);
        return (0);
    }
    args = ft_split(trimmed, ' ');
    free(trimmed);
    if (!args || !args[0])
    {
        if (args)
            ft_free_split(args);
        return (1);
    }
    DEBUG_PRINT("Executing simple command: '%s'\n", args[0]);
    is_built_in = is_builtin(args[0]);
    if (is_built_in != -1)
        result = execute_builtin(args, &env_list);
    else
        result = execute_external(args, env_list);
    ft_free_split(args);
    return (result);
}

int main(int ac, char **av, char **envp)
{
    char *line;
    char cwd[1024];
    t_env *env_list;
    t_minibox minibox;
    int use_simple_mode = 1;

    (void)ac;
    (void)av;
    DEBUG_PRINT("Starting minishell\n");
    if (!envp || !envp[0])
    {
        ft_putstr_fd("Error: No environment variables\n", 2);
        return (1);
    }
    env_list = init_env(envp);
    if (!env_list)
        return (ft_putstr_fd("Error: Failed to initialize env\n", 2), 1);
    if (!get_env(env_list, "PATH"))
    {
        ft_putstr_fd("Warning: PATH not found, setting default\n", 2);
        set_env_value(&env_list, "PATH", "/bin:/usr/bin:/usr/local/bin");
    }
    DEBUG_PRINT("PATH: %s\n", get_env(env_list, "PATH"));
    while (1)
    {
        char *pwd = getcwd(cwd, sizeof(cwd));
        if (!pwd)
            pwd = "unknown";
            
        char *prompt = ft_strjoin(pwd, "> ");
        if (!prompt)
            prompt = ft_strdup("> ");
            
        line = readline(prompt);
        if (prompt)
            free(prompt);

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
        if (use_simple_mode)
        {
            // Mode simple sans minibox pour tester
            DEBUG_PRINT("Using simple mode for: '%s'\n", line);
            int result = execute_simple_command(line, env_list);
            if (result != 0)
                DEBUG_PRINT("Command failed with exit code %d\n", result);
        }
        else
        {
            ft_memset(&minibox, 0, sizeof(t_minibox));
            DEBUG_PRINT("Processing line: '%s'\n", line);
            ft_build_minibox_input(&minibox, line);
            DEBUG_PRINT("Error in build_minibox_input\n");
            ft_build_minibox_lexing(&minibox);
            DEBUG_PRINT("Error in build_minibox_lexing\n");
            ft_destroy_minibox(&minibox);
            ft_build_minibox_parsing(&minibox);
            DEBUG_PRINT("Error in build_minibox_parsing\n");
            ft_destroy_minibox(&minibox);
            DEBUG_PRINT("Error code before execution: %d\n", minibox.error.code);
            if (minibox.error.code == MINICODE_NONE)
            {
                DEBUG_PRINT("Executing minibox...\n");
                int result = execute_minibox(&minibox, env_list);
                DEBUG_PRINT("Execution result: %d\n", result);
            }
            else
            {
                DEBUG_PRINT("Minibox has error, displaying...\n");
                ft_display_minibox_error(minibox.error);
            }

            ft_destroy_minibox(&minibox);
        }

        free(line);
    }

    free_env_list(env_list);
    return (0);
}
