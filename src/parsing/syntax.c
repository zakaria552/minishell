#include "minishell.h"

bool check_redirect(t_arena *arena, t_token *token)
{
	char *error;

	if (ft_strlen(token->content) >= 1)
		return (true);
	error = arena_strjoin(arena, "syntax error, empty redirect: ",\
	 (char *)get_token_type(token->type));
	syntax_err(2, error);
	return (false);
}

bool check_command(t_arena *arena, t_cmd *command)
{
	int		i;

	if (command->unmatched_quote)
	{
		syntax_err(2, "syntax error, unmatched quote");
		return (false);
	}
	i = -1;
	while (++i < command->redirects->size)
	{
		if (!check_redirect(arena, get_vector_elem(command->redirects, i)))
			return (false);
	}
	if (!command->cmd && i == 0)
	{
		syntax_err(2, "syntax error, empty pipe");
		return (false);
	}
	return (true);
}
