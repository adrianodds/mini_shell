#include "../minishell.h"

char	**split_str(char *str, char *delim)
{
	char	**result;
	int		count;
	int		i;
	char	*copy;
	char	*token;

	count = 0;
	copy = ft_strdup(str);
	token = strtok(copy, delim);
	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}
	free(copy);
	result = malloc(sizeof(char *) * (count + 1));
	copy = ft_strdup(str);
	i = 0;
	token = strtok(copy, delim);
	while (token)
	{
		result[i] = ft_strdup(token);
		i++;
		token = strtok(NULL, delim);
	}
	result[i] = NULL;
	free(copy);
	return (result);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_commands(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;
	t_redir	*redir;
	t_redir	*next_redir;
	int		i;

	current = commands;
	while (current)
	{
		next = current->next;
		i = 0;
		while (current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		redir = current->redirects;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->file);
			free(redir);
			redir = next_redir;
		}
		free(current);
		current = next;
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		free(shell->envp[i]);
		i++;
	}
	free(shell->envp);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->commands)
		free_commands(shell->commands);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	result = malloc(n + 1);
	i = 0;
	while (i < n && s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = NULL;
	while (*s)
	{
		if (*s == (char)c)
			result = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (result);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
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
			quote_char = str[i];
			i++;
		}
		else if (in_quote && str[i] == quote_char)
		{
			in_quote = 0;
			i++;
		}
		else
		{
			result[j] = str[i];
			i++;
			j++;
		}
	}
	result[j] = '\0';
	return (result);
}

char	*expand_variables(t_shell *shell, const char *str)
{
	char	*result;
	char	buffer[8192];
	int		i;
	int		j;
	int		in_double_quote;
	int		in_single_quote;
	char	var_name[256];
	char	*var_value;
	int		k;
	int		vlen;

	if (!str)
		return (NULL);
	result = buffer;
	i = 0;
	j = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (str[i] && j < 8191)
	{
		if (str[i] == '"' && !in_single_quote)
		{
			result[j++] = str[i];
			in_double_quote = !in_double_quote;
			i++;
		}
		else if (str[i] == '\'' && !in_double_quote)
		{
			result[j++] = str[i];
			in_single_quote = !in_single_quote;
			i++;
		}
		else if (str[i] == '$' && in_double_quote)
		{
			i++;
			k = 0;
			if (str[i] == '?')
			{
				var_name[0] = '?';
				var_name[1] = '\0';
				i++;
				k = 1;
			}
			else
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && k < 255)
				{
					var_name[k] = str[i];
					k++;
					i++;
				}
				var_name[k] = '\0';
			}
			if (ft_strcmp(var_name, "?") == 0)
			{
				var_value = ft_itoa(shell->exit_status);
				vlen = 0;
				while (var_value[vlen] && j < 8191)
				{
					result[j++] = var_value[vlen++];
				}
				free(var_value);
			}
			else if (k > 0)
			{
				var_value = get_env(shell, var_name);
				if (var_value)
				{
					vlen = 0;
					while (var_value[vlen] && j < 8191)
					{
						result[j++] = var_value[vlen++];
					}
				}
			}
			else if (j < 8191)
			{
				result[j++] = '$';
			}
		}
		else if (str[i] == '$' && !in_single_quote && !in_double_quote)
		{
			i++;
			k = 0;
			if (str[i] == '?')
			{
				var_name[0] = '?';
				var_name[1] = '\0';
				i++;
				k = 1;
			}
			else
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && k < 255)
				{
					var_name[k] = str[i];
					k++;
					i++;
				}
				var_name[k] = '\0';
			}
			if (ft_strcmp(var_name, "?") == 0)
			{
				var_value = ft_itoa(shell->exit_status);
				vlen = 0;
				while (var_value[vlen] && j < 8191)
				{
					result[j++] = var_value[vlen++];
				}
				free(var_value);
			}
			else if (k > 0)
			{
				var_value = get_env(shell, var_name);
				if (var_value)
				{
					vlen = 0;
					while (var_value[vlen] && j < 8191)
					{
						result[j++] = var_value[vlen++];
					}
				}
			}
			else if (j < 8191)
			{
				result[j++] = '$';
			}
		}
		else
		{
			result[j] = str[i];
			i++;
			j++;
		}
	}
	result[j] = '\0';
	return (ft_strdup(result));
}

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		temp;
	int		is_negative;

	is_negative = n < 0;
	temp = n;
	len = 1;
	if (is_negative)
		len++;
	temp = is_negative ? -n : n;
	temp /= 10;
	while (temp > 0)
	{
		len++;
		temp /= 10;
	}
	result = malloc(len + 1);
	result[len] = '\0';
	temp = is_negative ? -n : n;
	len--;
	while (len > 0)
	{
		result[len] = (temp % 10) + '0';
		temp /= 10;
		len--;
	}
	if (is_negative)
		result[0] = '-';
	else
		result[0] = (temp % 10) + '0';
	return (result);
}
