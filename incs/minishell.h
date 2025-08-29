#ifndef MINISHELL_H 
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <dirent.h>
#include "../Libft/incs/libft.h"
#include "../Libft/incs/ft_dprintf.h"

/* # ------------- # */
/*      struct     # */
/* # ------------- # */


/* #---------------# */
/*  signal functions */
/* #---------------# */
void    handle_signal(int sig);

/* # --------------- # */
/*  builtins functions */
/* # --------------- # */
int ft_echo(char **av);
int ft_cd(char **av);

#endif