#include "minishell.h"

t_cmd	*init_command(t_arena *arena)
{
	t_cmd	*command;

	command = arena_alloc(arena, sizeof(t_cmd), NULL);
	command->args = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	command->redirects = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	return (command);
}

static void	add_redirect_to_command(t_cmd *command, char *str, t_token *tok)
{
	if (str)
	{
		tok->content = str;
		append(command->redirects, tok);
	}
	else
		command->unmatched_quote = true;
}

static void	add_string_to_command(t_cmd *c, char *s, t_arena *a, bool split)
{
	t_vector	*temp;
	int			i;

	if (s)
	{
		temp = split_string(s, a, split);
		i = -1;
		while (++i < temp->size)
		{	
			if (c->cmd == NULL)
				c->cmd = (char *)temp->get(temp, i);
			else
				append(c->args, (char *)temp->get(temp, i));
		}
	}
	else
		c->unmatched_quote = true;
}

//updates a command with either a command, an argument, or a redirect
//and moves the index forward by however many tokens were used to do so
void	update_command(t_arena *arena, t_cmd *command, t_vector *vec, int *i)
{
	t_token	*tok;
	char	*temp;
	bool	should_split;

	tok = vec->get(vec, *i);
	if (is_string_type(tok))
	{
		should_split = true;
		temp = concat_string_types(arena, vec, i, &should_split);
		add_string_to_command(command, temp, arena, should_split);
	}
	if (is_redirect_type(tok))
	{
		*i += 1;
		should_split = (tok->type != HERE_DOC);
		temp = concat_string_types(arena, vec, i, &should_split);
		add_redirect_to_command(command, temp, tok);
	}
}
