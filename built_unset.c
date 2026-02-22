#include "minishell.h"

static char **env_remove(char **env, int idx)
{
    int count;
    int i;
    int j;
    char **new_env;

    count = 0;
    i = 0;
    j = 0;
    while(env[count])
        count++;
    new_env = malloc(sizeof(char *) * count);
    if (!new_env)
        return (NULL);
    while(i < count)
    {
        if (i != idx)
        {
            new_env[j] = env[i];
            j++;
        }
        else
            free(env[i]);
        i++;
    }
    new_env[j] = NULL;
    free(env);
    return (new_env);

}

int builtin_unset(char **args, char ***envp)
{
    int i;
    int idx;
    int key_len;

    if (!args[1])
        return (0);
    i = 1;
    while(args[i])
    {
        if(!is_valid_identifier(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            i++;
            continue;
        }
        key_len = ft_strlen(args[i]);
        idx = env_find_index(*envp, args[i], key_len);
        if(idx >= 0)
            *envp = env_remove(*envp, idx);
        i++;
    }
    return (0);
}
