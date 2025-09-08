/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/08 13:26:53 by molapoug         ###   ########.fr       */
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

int main(int ac, char **av, char **envp)
{
    char *line;
    char cwd[1024];
    t_env *env_list;
    t_minibox minibox;

    (void)ac;
    (void)av;

    env_list = init_env(envp);
    if (!env_list)
        return (ft_putstr_fd("Error: Failed to initialize env\n", 2), 1);

    while (1)
    {
        // Afficher le prompt
        char *pwd = getcwd(cwd, sizeof(cwd));
        char *prompt = ft_strjoin(pwd, "> ");
        line = readline(prompt);
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

        // Construire le minibox avec la ligne de commande
        ft_build_minibox_input(&minibox, line);
        ft_build_minibox_lexing(&minibox);
        ft_build_minibox_parsing(&minibox);

        // Exécuter si pas d'erreur
        if (minibox.error.code == MINICODE_NONE)
        {
            int result = execute_minibox(&minibox, env_list);
            if (result != 0)
                ft_dprintf(2, "Command failed with exit code %d\n", result);
        }
        else
        {
            ft_display_minibox_error(minibox.error);
        }

        // Nettoyer
        ft_destroy_minibox(&minibox);
        free(line);
    }

    free_env_list(env_list);
    return (0);
}
