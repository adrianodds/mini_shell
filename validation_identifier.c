#include "minishell.h"

int is_valid_identifier(const char *arg)
{
    int i;

    i = 0;
    if(!arg || arg[0] == '\0')
        return (0);
    if(arg[i] == '=')
        return (0);
    if(!(ft_isalpha(arg[i]) || arg[i] == '_'))
        return (0);
    i++;
    while(arg[i] && arg[i] != '=')
    {
        if(!(ft_isalnum(arg[i]) || arg[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}
