#include "minishell.h"
/*
void	split_and_clean_command(t_cmd *cmd, t_arena *arena)
{
	t_vector	*args;
	t_vector	*temp;
	int			i;
	int			j;

	args = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	temp = tokenize_input(cmd->cmd, arena, '\0');
	if (temp->size > 1)
	{
		cmd->cmd = ((t_token *)temp->get(temp, 0))->content;
		clean_command(cmd, temp, true);
	}
	i = -1;
	while (++i < cmd->args->size)
	{
		temp = tokenize_input(get_vector_elem(cmd->args, i), arena, '\0');
	}
}
*/

bool	check_all_empty(t_vector *tokens)
{
	t_token	*tok;
	int		i;

	i = -1;
	while (++i < tokens->size)
	{
		tok = tokens->get(tokens, i);
		if (tok->type != EMPTY)
			return (false);
	}
	return (true);
}

void	split_and_clean_command(t_cmd *cmd, t_arena *arena)
{
	t_vector	*args;
	t_vector	*temp;
	int			i;
	int			j;

	args = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	temp = tokenize_input(cmd->cmd, arena, '\0');
	if (temp->size > 1)
	{
		cmd->cmd = (t_token *)temp->get(temp, 0)->content;
		clean_command(cmd, temp, true);
	}
	i = -1;
	while (++i < cmd->args->size)
	{
		temp = tokenize_input(get_vector_elem(cmd->args, i), arena, '\0');
	}
}

bool	check_all_empty(t_vector *tokens)
{
	t_token	*tok;
	int		i;

	i = -1;
	while (++i < tokens->size)
	{
		tok = tokens->get(tokens, i);
		if (tok->type != EMPTY)
			return (false);
	}
	return (true);
}

bool	check_redirect(t_arena *arena, t_token *token)
{
	char	*error;

	if (ft_strlen(token->content) >= 1)
		return (true);
	error = arena_strjoin(arena, "syntax error, empty redirect: ", \
(char *)get_token_type(token->type));
	syntax_err(2, error);
	return (false);
}

bool	check_command(t_arena *arena, t_cmd *command)
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
