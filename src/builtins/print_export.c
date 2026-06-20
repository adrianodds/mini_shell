/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 16:22:12 by adduarte          #+#    #+#             */
/*   Updated: 2026/06/20 16:28:14 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	compare_envp(char *a, char *b)
{
	int	len_a;
	int	len_b;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (len_a > len_b)
		return (ft_strncmp(a, b, len_a + 1));
	return (ft_strncmp(a, b, len_b + 1));
}

static void	sort_envp(char **sorted, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (compare_envp(sorted[j], sorted[j + 1]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_one_export(char *entry)
{
	char	*eq;

	eq = ft_strchr(entry, '=');
	if (eq)
		printf("declare -x %.*s=\"%s\"\n", (int)(eq - entry), entry, eq + 1);
	else
		printf("declare -x %s\n", entry);
}

void	print_export(t_shell *shell)
{
	char	**sorted;
	int		count;
	int		i;

	count = count_envp(shell->envp);
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return ;
	i = 0;
	while (i < count)
	{
		sorted[i] = shell->envp[i];
		i++;
	}
	sorted[count] = NULL;
	sort_envp(sorted, count);
	i = 0;
	while (sorted[i])
		print_one_export(sorted[i++]);
	free(sorted);
}