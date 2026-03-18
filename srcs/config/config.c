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