#ifndef MINISHELL_H 
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include "../Libft/incs/libft.h"
#include "../Libft/incs/ft_dprintf.h"

/* # ------------- # */
/*      struct     # */
/* # ------------- # */
typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env    *next;
}   t_env;


/* #---------------# */
/*  signal functions */
/* #---------------# */
void    handle_signal(int sig);

/* # --------------- # */
/*  builtins functions */
/* # --------------- # */
int ft_echo(char **av);
int ft_cd(char **args, t_env **envp);

/* # --------------- # */
/*    builtins utils   */
/* # --------------- # */
char    *get_env(t_env *envp, char *key);
void    set_env_value(t_env **envp, char *key, char *value);
char    *get_home(t_env *envp);
char    *get_oldpwd(t_env *envp);
t_env   *creat_env(char *key, char *value);
t_env   *init_env(char **envp);
char    **pasrse_line(char *line);
void    free_args(char **args);
int     execute_builtin(char **args, t_env **envp);
int     execute_external(char **args, t_env *env_list);
void    free_env_list(t_env *envp);
void    set_env_value(t_env **envp, char *key, char *value);

#endif