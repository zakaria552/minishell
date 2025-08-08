# include "minishell.h"

t_vector *test_redirects(void)
{
	t_arena			*arena;
    char 			*prompt;
 	t_vector		*vec;
	t_token			*tok;
	t_command_table	*head;
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
		head = parse_vector_to_commands(arena, vec);
		i = 0;
		while (i < vec->size)
		{
			tok = (t_token *)vec->get(vec, i);
			print_token(tok);
			++i;
		}
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

t_allocators *get_allocators()
{
    static t_allocators arenas;

	if (arenas.global)
		arenas.global = init_arena(ARENA_SIZE);
	return (&arenas);
}
