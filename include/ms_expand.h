#ifndef MS_EXPAND_H
# define MS_EXPAND_H

# include "ms_types.h"

typedef struct s_expand_ctx
{
	t_shell		*shell;
	const char	*str;
	int			i;
	char		*result;
	int			pos;
	int			quotes[2];
}	t_expand_ctx;

int			handle_dollar(t_expand_ctx *ctx, char *tmp);
int			copy_expanded(char *result, char *tmp, int j);
void			process_char(t_expand_ctx *ctx);

#endif
