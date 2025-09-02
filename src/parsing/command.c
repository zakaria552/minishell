#include "minishell.h"

t_cmd	*init_command(t_arena *arena)
{
	t_cmd	*command;

	command = arena_alloc(arena, sizeof(t_cmd), NULL);
	command->args = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	command->redirects = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	return (command);
}

static void	add_string_to_command(t_cmd *command, char *str, t_token *tok)
{
	if (str)
	{
		if (command->cmd == NULL)
			command->cmd = str;
		else
			append(command->args, str);
	}
	else
		command->unmatched_quote = tok->type;
}

//updates a command with either a command, an argument, or a redirect
//and moves the index forward by however many tokens were used to do so
void	update_command(t_arena *arena, t_cmd *command, t_vector *vec, int *i)
{
	t_token	*tok;
	char	*temp;

	tok = vec->get(vec, *i);
	if (is_string_type(tok->type))
	{
		temp = concat_string_types(arena, vec, i, true);
		add_string_to_command(command, temp, tok);
	}
	if (is_redirect_type(tok->type))
	{
		*i += 1;
		temp = concat_string_types(arena, vec, i, (tok->type != HERE_DOC));
		if (temp)
		{
			tok->content = temp;
			append(command->redirects, tok);
		}
		else
		{
			command->unmatched_quote = tok->type;
			return ;
		}
	}
}
