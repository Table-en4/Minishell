#include "minishell.h"

int valide_id(char *name)
{
    int i;

    i = 1;
    if (!name || !name[0])
        return (0);
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int export_assign(t_env **envp, char *arg)
{
    char    *pos;
    char    *key;
    char    *value;
    char    *copy;

    pos = ft_strchr(arg, '=');
    if (!pos)
        return (0);
    *pos = '\0';
    key = arg;
    value = pos + 1;
    if (!valide_id(key))
    {
        *pos = '=';
        return (ft_dprintf(2, "bad export : '%s': identifier", arg), 1);
    }
    copy = ft_strdup(key);
    *pos = '=';
    set_env_value(envp, copy, value);
    free(copy);
    return (0);
}

//ajouter la gestion d'export sans value
int export_no_value(t_env **envp, char *arg)
{
    char    *exist;

    if (!valide_id(arg))
        return (ft_dprintf(2, "export: '%s': not valid\n", arg), 1);
    exist = get_env(*envp, arg);
    if (exist)
        return (0);
    else
        return (set_env_value(envp, arg, ""), 0);
    return (0);
}

//ajouter la gestion d'export tout court et modifier
//la fonction execute_builtins dans exec_builtin.c
int ft_export(char **args, t_env **envp)
{
    int i;
    int error_count;
    t_env *current;
    if (!args[1])
    {
        current = *envp;
        while (current)
        {
            ft_dprintf(1, "\e[31m declare -x\e[0m %s=%s\n", current->key, current->value);
            current = current->next;
        }
        return (0);
    }
    error_count = 0;
    i = 1;
    while (args[i])
    {
        if (ft_strchr(args[i], '='))
        {
            if (export_no_value(envp, args[i]) != 0)
                error_count++;
        }
        else
        {
            if (export_no_value(envp, args[i]) != 0)
                error_count++;
        }
        i++;
    }
    if (error_count > 0)
        return (1);
    return (0);
}
