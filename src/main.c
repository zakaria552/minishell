# include "minishell.h"

int main(void)
{
	t_arena			*arena;
    char 			*prompt;
 	t_vector		*vec;
	t_vector		*commands;
	int				i;

    while (true)
    {
		arena = init_arena(ARENA_SIZE);
		if (!arena)
        	exit(1);
        prompt = read_prompt(arena);
		if (!prompt)
            break;
		vec = tokenize_input(prompt, arena, '\0');
		i = -1;
		while (++i < vec->size)
			print_token((t_token *)vec->get(vec, i));

		commands = parse_tokens_to_commands(arena, vec);
		i = -1;
		while (++i < commands->size)
			print_command((t_cmd *)commands->get(commands, i));
		clean_up((t_arena *)arena, false);
    }
	return (0);
}

t_arena *get_allocator()
{
    static t_arena *arena;
    if (!arena)
        arena = init_arena(ARENA_SIZE);
    return (arena);
}
