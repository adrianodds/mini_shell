/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:21 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:57:27 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../include/ms_expand.h"

static int	append_var_value(t_shell *shell, char *var_name, char *result,
		int j)
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

int	handle_dollar(t_expand_ctx *ctx, char *tmp)
{
	char	var_name[256];
	int		var_len;

	ctx->i++;
	var_len = read_var_name(ctx->str, &ctx->i, var_name);
	if (var_len == 0)
		return (-1);
	return (append_var_value(ctx->shell, var_name, tmp, 0));
}

int	copy_expanded(char *result, char *tmp, int j)
{
	int	k;

	k = 0;
	while (tmp[k] && j < 8191)
		result[j++] = tmp[k++];
	return (j);
}
