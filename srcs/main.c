/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/11/12 20:24:14 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//variable globale g_aliases
t_alias *g_aliases = NULL;

void replace_alias(t_alias *alias, const char *value)
{
	free(alias->value);
	alias->value = ft_strdup(value);
}

void add_alias(const char *name, const char *value)
{
	t_alias *cur;

	cur = g_aliases;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			replace_alias(cur, value);
			return ;
		}
		cur = cur->next;
	}
	t_alias *new = malloc(sizeof(t_alias));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = g_aliases;
	g_aliases = new;
}

void parse_line_config(char *line)
{
    char    *name;
    char    *value;
    char    *eq;
    char    quote;
    size_t  len;

    if (!line || ft_strncmp(line, "alias ", 6) != 0)
        return ;
    name = line + 6;
    eq = ft_strchr(name, '=');
    if (!eq || eq == name)
        return ;
    *eq = '\0';
    value = eq + 1;
    if (value[0] != '"' && value[0] != '\'')
        return ;
    quote = value[0];
    value++;
    len = ft_strlen(value);
    while (len > 0 && (value[len - 1] == '\n' || value[len - 1] == '\r'))
        value[--len] = '\0';
    if (len == 0 || value[len - 1] != quote)
        return ;
    value[len - 1] = '\0';
    add_alias(name, value);
}

void load_config(t_env *envp)
{
    char *home;
    char *path;
    char *line;
    int  fd;

    (void)envp;
    home = get_env(envp, "HOME");
    if (!home)
        return ;
    path = ft_strjoin(home, "/.minishellrc");
    if (!path)
        return ;
    fd = open(path, O_RDONLY);
    free(path);
    if (fd < 0)
        return ;
    line = get_next_line(fd);
    while (line)
    {
        parse_line_config(line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
}

char *resolve_aliases(const char *line)
{
    t_alias *cur;
    char    *name_end;
    size_t  name_len;

    cur = g_aliases;
    while (cur)
    {
        name_len = ft_strlen(cur->name);
        name_end = (char *)line + name_len;
        if (ft_strncmp(line, cur->name, name_len) == 0
            && (*name_end == ' ' || *name_end == '\0'))
        {
            if (*name_end == '\0')
                return (ft_strdup(cur->value));
            return (ft_strjoin(cur->value, name_end));
        }
        cur = cur->next;
    }
    return (ft_strdup(line));
}

char	*get_prompt(void)
{
	char	cwd[1024];
	char	*pwd;
	char	*prompt;

	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		pwd = "(lost)";
	prompt = ft_strjoin(pwd, "> ");
	if (!prompt)
		return (ft_strdup("> "));
	return (prompt);
}

static int	code_minibox(t_minibox *minibox)
{
	if (minibox->error.code == MINICODE_INPUT_NULL || \
		minibox->error.code == MINICODE_INPUT_BLANK)
		return (0);
	else if (minibox->error.code == MINICODE_ERRNO)
		return (perror("minishell"), 1);
	else if (minibox->error.code == MINICODE_SIGINT)
		return (130);
	return (ft_dprintf(2, "minishell: %s\n", minibox->error.msg), 1);
}

int	handle_minibox(char *line, t_env **env_list, int dbg)
{
	t_minibox	*minibox;
	char		**current_envp;
	char 		*resolved;
	int			exit_code;

	1 && (exit_code = 0), (minibox = ft_calloc(1, sizeof(t_minibox)));
	if (!minibox)
		return (perror("minishell"), free(line), 1);
	current_envp = conv_env_envp(*env_list);
	if (!current_envp)
		return (free(minibox), free(line), 1);
	resolved = resolve_aliases(line);
	if (!resolved)
		return (free_envp(current_envp), free(minibox), free(line), 1);
	ft_build_minibox(minibox, resolved, current_envp);
	free(resolved);
	if (dbg)
		ft_display_minibox(minibox);
	if (minibox->error.code == MINICODE_NONE)
		exit_code = execute_minibox(minibox, env_list);
	else
		exit_code = code_minibox(minibox);
	1 && (free_envp(current_envp), current_envp = NULL);
	return (ft_destroy_minibox(minibox), free(minibox), exit_code);
}

int	main_loop(t_env **env_lst, int dbg)
{
	char		*s[2];
	static int	code = 0;

	while (1)
	{
		1 && (s[1] = get_prompt()), (s[0] = readline(s[1])), free(s[1]);
		if (!s[0])
			return (ft_dprintf(1, "exit\n"), code);
		if (g_signal == 130)
		{
			1 && (code = g_signal), (g_signal = 0), free(s[0]);
			continue ;
		}
		if (!ft_isblank(s[0]))
		{
			add_history(s[0]);
			1 && (g_signal = code, (code = handle_minibox(s[0], env_lst, dbg)));
			if (code >= EXIT_SHELL_CODE)
				return ((g_signal = 0), free(s[0]), code - EXIT_SHELL_CODE);
		}
		else
			code = 0;
		1 && (g_signal = 0), free(s[0]);
	}
	return (code);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	int		exit_code;
	int		dbg;

	dbg = 0;
	if (ac == 2 && !ft_strcmp(av[1], "--debug"))
		dbg = 1;
	env_list = init_env(envp);
	load_config(env_list);
	setup_signals();
	exit_code = main_loop(&env_list, dbg);
	free_env_list(env_list);
	rl_clear_history();
	return (exit_code);
}
