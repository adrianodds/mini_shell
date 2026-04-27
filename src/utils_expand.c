#include "../minishell.h"

static int	append_var_value(t_shell *shell, char *var_name, char *result, int j)
{
	char	*var_value;
	char	*exit_code;
	int		k;

	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		exit_code = ft_itoa(shell->exit_status);
		k = 0;
		while (exit_code[k] && j < 8191)
			result[j++] = exit_code[k++];
		free(exit_code);
		return (j);
	}
	var_value = get_env(shell, var_name);
	if (!var_value)
		return (j);
	k = 0;
	while (var_value[k] && j < 8191)
		result[j++] = var_value[k++];
	return (j);
}

static int	read_var_name(const char *str, int *i, char *var_name)
{
	int	k;

	k = 0;
	if (str[*i] == '?')
	{
		var_name[0] = '?';
		var_name[1] = '\0';
		(*i)++;
		return (1);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_') && k < 255)
		var_name[k++] = str[(*i)++];
	var_name[k] = '\0';
	return (k);
}

static int	handle_dollar(t_shell *shell, const char *str, int *i, char *result)
{
	char	var_name[256];
	int		var_len;

	(*i)++;
	var_len = read_var_name(str, i, var_name);
	if (var_len == 0)
		return (-1);
	return (append_var_value(shell, var_name, result, 0));
}

static int	copy_expanded(char *result, char *tmp, int j)
{
	int	k;

	k = 0;
	while (tmp[k] && j < 8191)
		result[j++] = tmp[k++];
	return (j);
}

static int	handle_quotes_in_expand(const char *str, int *i, char *result, int *q)
{
	if (str[*i] == '"' && !q[1])
	{
		result[q[2]++] = str[(*i)++];
		q[0] = !q[0];
		return (1);
	}
	if (str[*i] == '\'' && !q[0])
	{
		result[q[2]++] = str[(*i)++];
		q[1] = !q[1];
		return (1);
	}
	return (0);
}

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

static void	handle_expand_dollar(t_shell *shell, const char *str, int *i,
		char *result, int *j)
{
	char	tmp[8192];
	int		k;

	k = handle_dollar(shell, str, i, tmp);
	if (k == -1 && *j < 8191)
		result[(*j)++] = '$';
	else if (k >= 0)
	{
		tmp[k] = '\0';
		*j = copy_expanded(result, tmp, *j);
	}
}

char	*expand_variables(t_shell *shell, const char *str)
{
	char	result[8192];
	int		q[3];
	int		i;

	if (!str)
		return (NULL);
	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	i = 0;
	while (str[i] && q[2] < 8191)
	{
		if (handle_quotes_in_expand(str, &i, result, q))
			continue ;
		if (str[i] == '$' && !q[1])
			handle_expand_dollar(shell, str, &i, result, &q[2]);
		else
			result[q[2]++] = str[i++];
	}
	result[q[2]] = '\0';
	return (ft_strdup(result));
}
