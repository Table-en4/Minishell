#include "../incs/libft.h"

char *ft_strtok(char *str, const char *delim)
{
    static char *last;
    char *start;
    
    if (str)
        last = str;
    if (!last)
        return (NULL);
    while (*last && ft_strchr(delim, *last))
        last++;
    if (!*last)
        return (NULL);
    start = last;
    while (*last && !ft_strchr(delim, *last))
        last++;
    if (*last)
        *last++ = '\0';
    return (start);
}
