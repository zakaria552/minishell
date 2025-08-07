# include "minishell.h"

int main(void)
{
	t_arena		*arena;
    char 		*prompt;
 	t_vector	*vec;
	t_token		*tok;
	int			i;

    while (true)
    {
		arena = init_arena(ARENA_SIZE);
		if (!arena)
        	exit(1);
        prompt = read_prompt();
		if (!prompt)
            break;
		vec = tokenize_input(prompt, arena);
		i = 0;
		while (i < vec->size)
		{
			tok = (t_token *)vec->get(vec, i);
			print_token(tok);
			++i;
		}
        free(prompt);
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
