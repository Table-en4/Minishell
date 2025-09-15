/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 12:19:09 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal_received = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// Ignorer SIGQUIT dans le shell interactif
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

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
    is_built_in = is_builtin(args[0]);
    if (is_built_in != -1)
        result = execute_builtin(args, &env_list);
    else
        result = execute_external(args, env_list);
    ft_free_split(args);
    return (result);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env		*env_list;
	t_minibox	minibox;
	int			exit_code;
    char        *pwd;
    char        *prompt;
    char       cwd[1024];

	(void)ac;
	(void)av;
	setup_signals();	
	env_list = init_env(envp);
	/*if (!env_list)
		return (ft_putstr_fd("Error: Failed to initialize env\n", 2), 1);*/
	while (1)
	{
        pwd = getcwd(cwd, sizeof(cwd));
        if (!pwd)
            pwd = ">";
        prompt = ft_strjoin(pwd, "\n> ");
        if (!prompt)
            prompt = "> ";
		g_signal_received = 0;		
		line = readline(prompt);		
		if (g_signal_received == SIGINT)
		{
			if (line)
			{
				free(line);
				continue;
			}
		}
		//gestion de Ctrl+D (EOF)
		if (!line)
		{
			ft_dprintf(1, "\e[46m exit \e[0m \n");
			break;
		}
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		ft_memset(&minibox, 0, sizeof(t_minibox));
		//construction de la minibox
		if (ft_build_minibox(&minibox, line, envp) == 0)
		{
			if (minibox.error.code == MINICODE_NONE)
			{
				exit_code = execute_minibox(&minibox, env_list);
				DEBUG_PRINT("Command exit code: %d\n", exit_code);
			}
			else
			{
				ft_display_minibox_error(minibox.error);
				exit_code = 1;
			}
		}
		else
		{
			ft_dprintf(2, "Error building minibox\n");
			exit_code = 1;
		}
		free(line);
		ft_destroy_minibox(&minibox);
	}
	free_env_list(env_list);
	return (exit_code);
}
