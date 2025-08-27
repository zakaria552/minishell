#include "minishell.h"

t_cmd	*init_command(t_arena *arena)
{
	t_cmd	*command;

	command = arena_alloc(arena, sizeof(t_cmd), NULL);
	command->args = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	command->redirects = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	return (command);
}


//updates a command with either a command, an argument, or a redirect
//and moves the index forward by however many tokens were used to do so
void	update_command(t_arena *arena, t_cmd *command, t_vector *vec, int *i)
{
	t_token	*tok;
	char	*temp;

	tok = vec->get(vec, *i);
	if(is_string_type(tok->type))
	{
		temp = concat_string_types(arena, vec, i, true);
		if (temp)
		{
			if (command->cmd == NULL)
				command->cmd = temp;
			else
				append(command->args, temp);
		}
		else
			command->unmatched_quote = tok->type;
	}
	if(is_redirect_type(tok->type))
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

/*
void	print_vector_commands(t_vector *vec)
{
	int i;

	i = -1;
	while (++i < vec->size)
		print_command((t_cmd *)vec->get(vec, i));
}

void	print_command(t_cmd *command)
{
	int	i;

	ft_printf("\n***\ncommand: %s\n", command->cmd);
	i = -1;
	while (++i < command->args->size)
		ft_printf("arg%d: %s\n", i, (char *)command->args->get(command->args, i));
	i = -1;
	if (command->redirects->size > 0)
		ft_printf("redirects:\n");
	while (++i < command->redirects->size)
		print_token((t_token *)command->redirects->get(command->redirects, i));
	ft_printf("***\n");
}
*/
