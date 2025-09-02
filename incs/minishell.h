/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:43:53 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/02 17:01:13 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include "../Libft/incs/libft.h"
#include "../Libft/incs/ft_dprintf.h"

/*#-----------------#*/
/*#------struct-----#*/
/*#-----------------#*/
typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env    *next;
}   t_env;

typedef struct s_cd
{
    char    *go_dir;
    char    *home;
    char    *old_pwd;
}   t_cd;

typedef struct s_blt
{
    char    *pos;
    char    *key;
    char    *value;
    char    *copy;
}   t_blt;

/*#------------------#*/
/*#-signal functions-#*/
/*#------------------#*/
void    handle_signal(int sig);

/*#--------------------#*/
/*#-builtins functions-#*/
/*#--------------------#*/
int ft_echo(char **av);
int ft_cd(char **args, t_env **envp);
int ft_export(char **args, t_env **envp);
int ft_env(char **args, t_env **envp);
int ft_unset(char **args, t_env **envp);

/*#-------------------#*/
/*#---builtins utils--#*/
/*#-------------------#*/
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
void    free_env_node(t_env *node);
void    set_env_value(t_env **envp, char *key, char *value);
int     valide_id(char *name);
char    **conv_env_envp(t_env *env_list);
void    free_envp(char **envp);
int     export_no_value(t_env **envp, char *arg);
int     unset_env(t_env **envp, char *key);

#endif
