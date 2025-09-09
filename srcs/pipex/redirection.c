/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:28:31 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/08 21:28:31 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void restore_stdio(int stdio_backup[3])
{
    DEBUG_PRINT("Restoring stdio\n");
    
    if (stdio_backup[0] != -1)
    {
        if (dup2(stdio_backup[0], STDIN_FILENO) == -1)
            perror("dup2 stdin");
        close(stdio_backup[0]);
    }
    if (stdio_backup[1] != -1)
    {
        if (dup2(stdio_backup[1], STDOUT_FILENO) == -1)
            perror("dup2 stdout");
        close(stdio_backup[1]);
    }
    if (stdio_backup[2] != -1)
    {
        if (dup2(stdio_backup[2], STDERR_FILENO) == -1)
            perror("dup2 stderr");
        close(stdio_backup[2]);
    }
}

void apply_redirections(t_minifd *fds)
{
    t_minifd *current;
    int fd;
    
    current = fds;
    while (current)
    {        
        if (current->type == FAPPEND)
        {
            fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("open append");
                return;
            }
            if (dup2(fd, STDOUT_FILENO) == -1)
                perror("dup2 append");
            close(fd);
        }/*
        else if (current->type == FOUT)
        {
            fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("open output");
                return;
            }
            if (dup2(fd, STDOUT_FILENO) == -1)
                perror("dup2 output");
            close(fd);
        }
        else if (current->type == FIN)
        {
            fd = open(current->file, O_RDONLY);
            if (fd == -1)
            {
                perror("open input");
                return;
            }
            if (dup2(fd, STDIN_FILENO) == -1)
                perror("dup2 input");
            close(fd);
        }*/
        current = current->next;
    }
}