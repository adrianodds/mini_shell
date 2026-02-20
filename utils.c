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
