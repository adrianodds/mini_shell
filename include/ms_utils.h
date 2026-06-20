/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:26:49 by carmoliv          #+#    #+#             */
/*   Updated: 2026/06/20 15:06:11 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

# include "ms_types.h"

typedef struct s_rq
{
	int		i;
	int		j;
	char	quote_char;
}	t_rq;

void		free_commands(t_cmd *commands);
void		free_tokens(t_token *tokens);
void		free_shell(t_shell *shell);

#endif
