/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:43:53 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:47:26 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include "../Libft/incs/libft.h"
#include "../Libft/incs/ft_dprintf.h"
#include "../minibox/incs/minibox.h"
#include "../minibox/incs/minibox_internal.h"

#define FOUT 2
#define FIN 3

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

// DEBUG Macros
#ifdef DEBUG
# define DEBUG_PRINT(fmt, ...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
# define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

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
int ft_pwd(char **arg, t_env **envp);

//AST READ AND GESTION
int	execute_ast(t_minibox *minibox, t_miniparsing *node, t_env *env);

//exec cmd
int	execute_builtin_no_fork(char **argv, t_env **env);
int	should_fork(char *cmd);
int	run_command(char **argv, t_env *env);
int	exec_command(t_minibox *minibox, t_miniparsing *node, t_env *env);
int	exec_pipe(t_minibox *minibox, t_miniparsing *node, t_env *env);
int	exec_and(t_minibox *minibox, t_miniparsing *node, t_env *env);
int	exec_or(t_minibox *minibox, t_miniparsing *node, t_env *env);
int exec_subshell(t_minibox *minibox, t_miniparsing *node, t_env *env);
int exec_redirection(t_minibox *minibox, t_miniparsing *node, t_env *env);

/*#-------------------#*/
/*#---builtins utils--#*/
/*#-------------------#*/
char    *get_env(t_env *envp, char *key);
char	**env_to_tab(t_env *envp);
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
int     is_builtin(char *cmd);
char    *find_path(char *cmd, t_env *env);
void	ft_free_split(char **result);
void	restore_stdio(int stdio_backup[3]);
int     apply_redirections(t_minifd *fds, int stdio_backup[3]);

//utils pour l'exec
int	execute_minibox(t_minibox *minibox, t_env *env);
int	execute_node(t_minibox *minibox, t_miniparsing *node, t_env *env);

#endif