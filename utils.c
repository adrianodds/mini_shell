#include "minishell.h"

void free_args(char **args)
{
    int	i;

	i = 0;
	if (!args)
		return;
	while(args[i])
		free(args[i++]);
	free(args);
}

char	*join_key_value(const char *key, const char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if(!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

static char *get_var_value(char **envp, const char *var_name, int name_len)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, name_len) == 0 &&
			(envp[i][name_len] == '=' || envp[i][name_len] == '\0'))
		{
			if (envp[i][name_len] == '=')
				return (envp[i] + name_len + 1);
			return ("");
		}
		i++;
	}
	return ("");
}

char	*expand_variables(char *str, char **envp)
{
	char	*result;
	char	*pos;
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		var_len;
	int		before_len;

	if (!str)
		return (ft_strdup(""));
	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*str)
	{
		pos = ft_strchr(str, '$');
		if (!pos)
		{
			tmp = ft_strjoin(result, str);
			free(result);
			return (tmp);
		}
		before_len = pos - str;
		tmp = ft_substr(str, 0, before_len);
		if (!tmp)
			return (free(result), NULL);
		var_name = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		if (!var_name)
			return (NULL);
		result = var_name;
		str = pos + 1;
		if (*str == '?')
		{
			var_value = ft_itoa(g_exit_status);
			if (!var_value)
				return (free(result), NULL);
			tmp = ft_strjoin(result, var_value);
			free(var_value);
			free(result);
			result = tmp;
			if (!result)
				return (NULL);
			str++;
			continue ;
		}
		var_len = 0;
		while (str[var_len] && (ft_isalnum(str[var_len]) || str[var_len] == '_'))
			var_len++;
		if (var_len == 0)
		{
			tmp = ft_strjoin(result, "$");
			free(result);
			result = tmp;
			if (!result)
				return (NULL);
			str++;
			continue ;
		}
		var_name = ft_substr(str, 0, var_len);
		if (!var_name)
			return (free(result), NULL);
		var_value = get_var_value(envp, var_name, var_len);
		tmp = ft_strjoin(result, var_value);
		free(result);
		free(var_name);
		result = tmp;
		if (!result)
			return (NULL);
		str += var_len;
	}
	return (result);
}
