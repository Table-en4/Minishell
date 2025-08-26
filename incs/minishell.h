#ifndef MINISHELL_H 
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/* #---------------# */
/*  signal functions */
/* #---------------# */
void    handle_signal(int sig);

#endif