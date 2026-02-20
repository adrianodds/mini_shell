#include "minishell.h"

static int env_find_index(char **env, const char *key, int key_len)
{
    int i;

    i = 0;
    while(env[i])
    {
        if(ft_strncmp(env[i], key, key_len) == 0 &&
            (env[i][key_len] == '=' || env[i][key_len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}

static char **env_add(char **env, const char *entry)
{
    int count;
    char **new_env;
    int i;

    count = 0;
    while(env[count])
        count++;
    new_env = malloc(sizeof(char *) * (count + 2));
    if(!new_env)
        return (env);
    i = 0;
    while( i < count)
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = ft_strdup(entry);
    if (!new_env[i])
    {
        free(new_env);
        return (env);
    }
    new_env[i + 1] = NULL;
    free(env);
    return (new_env);
}

static char **env_set(char **env, const char *key, const char *value)
{
    int key_len;
    int idx;
    char *entry;

    key_len = ft_strlen(key);
    idx = env_find_index(env, key, key_len);
    if(value)
        entry = ft_strjoin(key, value);
    else
        entry = ft_strdup(key);
    if(!entry)
        return (env);
    if(idx >= 0)
    {
        free(env[idx]);
        env[idx] = entry;
        return (env);
    }
    return (env_add(env, entry));
}

static void export_print(char **env)
{
   int i;
   char *eq;

   i = 0;
   while(env[i])
   {
    eq = ft_strchr(env[i], '=');
    if (eq)
    {
        *eq = '\0';
        ft_printf("declare -x %s=\"%s\"\n", env[i], eq + 1);
        *eq = '=';
    }
    else
        ft_printf("declare -x %s\n", env[i]);
    i++;
   }
}

int builtin_export(char **args, char ***envp)
{
    int i = 1;
    int status = 0;

    if (!args[1])
    {
        export_print(*envp);
        return 0;
    }
    while (args[i])
    {
        char *arg = args[i];
        char *eq = ft_strchr(arg, '=');

        if (!is_valid_identifier(arg))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(arg, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            status = 1;
            i++;
            continue;
        }
        if (eq)
        {
            *eq = '\0';
            *envp = env_set(*envp, arg, eq + 1);
            *eq = '=';
        }
        else
        {
            int idx = env_find_index(*envp, arg, ft_strlen(arg));
            if (idx < 0)
                *envp = env_add(*envp, arg);
        }
        i++;
    }
    return status;
}
