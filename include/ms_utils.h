/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:26:49 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 19:44:39 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

# include "ms_types.h"

void		free_commands(t_cmd *commands);
void	    free_tokens(t_token *tokens);
void		free_shell(t_shell *shell);

#endif
