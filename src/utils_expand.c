#include "../minishell.h"

static int	append_var_value(t_shell *shell, char *var_name, char *result, int j)
{
	char	*var_value;
	char	*exit_code;
	int		k;

	if (ft_strcmp(var_name, "?") == 0)
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

char	*remove_quotes(const char *str)
{
	char	*result;
	int		len;
	int		i;
	int		j;
	char	in_quote;
	char	quote_char;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 1);
	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (i < len)
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '"'))
		{
			in_quote = 1;
			quote_char = str[i++];
		}
		else if (in_quote && str[i] == quote_char)
		{
			in_quote = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*expand_variables(t_shell *shell, const char *str)
{
	char	result[8192];
	char	tmp[8192];
	int		i;
	int		j;
	int		k;
	int		in_double_quote;
	int		in_single_quote;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (str[i] && j < 8191)
	{
		if (str[i] == '"' && !in_single_quote)
		{
			result[j++] = str[i++];
			in_double_quote = !in_double_quote;
		}
		else if (str[i] == '\'' && !in_double_quote)
		{
			result[j++] = str[i++];
			in_single_quote = !in_single_quote;
		}
		else if (str[i] == '$' && !in_single_quote)
		{
			k = handle_dollar(shell, str, &i, tmp);
			if (k == -1 && j < 8191)
				result[j++] = '$';
			else
			{
				tmp[k] = '\0';
				k = 0;
				while (tmp[k] && j < 8191)
					result[j++] = tmp[k++];
			}
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (ft_strdup(result));
}
