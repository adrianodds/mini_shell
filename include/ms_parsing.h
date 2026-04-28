#ifndef MS_PARSING_H
# define MS_PARSING_H

# include "ms_types.h"

void		parse_input(t_shell *shell, char *input);
t_token		*tokenize(t_shell *shell, char *input);
t_cmd		*parse_tokens(t_shell *shell, t_token *tokens);

typedef struct s_parse_ctx
{
	t_shell	*shell;
	t_cmd	**commands;
	t_cmd	**current;
	t_cmd	**last;
	t_token	**token_iter;
}	t_parse_ctx;

#endif
