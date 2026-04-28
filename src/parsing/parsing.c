/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:16 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:16:17 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_input(t_shell *shell, char *input)
{
	shell->tokens = tokenize(shell, input);
	if (!shell->tokens)
		return ;
	shell->commands = parse_tokens(shell, shell->tokens);
}
