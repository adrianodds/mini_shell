#include "../../minishell.h"

static char	*alloc_remove_quotes(const char *str, int *len)
{
	char	*result;

	if (!str)
		return (NULL);
	*len = ft_strlen(str);
	result = malloc(*len + 1);
	return (result);
}

static int	handle_quote_remove(const char *str, int *i, char *in_quote,
		char *quote_char)
{
	if (!*in_quote && (str[*i] == '\'' || str[*i] == '"'))
	{
		*in_quote = 1;
		*quote_char = str[*i];
		(*i)++;
		return (1);
	}
	if (*in_quote && str[*i] == *quote_char)
	{
		*in_quote = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		len;
	int		i;
	int		j;
	char	in_quote;
	char	quote_char;

	result = alloc_remove_quotes(str, &len);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (i < len)
	{
		if (handle_quote_remove(str, &i, &in_quote, &quote_char))
			continue ;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
