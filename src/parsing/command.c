#include "minishell.h"

t_cmd	*init_command(t_arena *arena)
{
	t_cmd	*command;

	command = arena_alloc(arena, sizeof(t_cmd), NULL);
	command->args = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	command->redirects = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	return (command);
}

static size_t split_length(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len] && !ft_isspace(str[len]))
		len++;
	return (len);
}

static t_vector *split_string(char *str, t_arena *arena)
{
	t_vector	*output;
	char		*temp;
	ssize_t		len;

	output = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	while (str && *str)
	{
		while (*str && ft_isspace(*str))
			++str;
		if (!*str && output->size > 0)
			break ;
		len = split_length(str);
		temp = arena_alloc(arena, len + 1, str);
		temp[len] = '\0';
		append(output, temp);
		str += len;
	}
	return (output);
}

static void	add_string_to_command(t_cmd *c, char *s, t_token *t, t_arena *a)
{
	t_vector	*temp;
	int			i;

	if (s)
	{
		temp = split_string(s, a);
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
		c->unmatched_quote = t->type;
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
		add_string_to_command(command, temp, tok, arena);
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
