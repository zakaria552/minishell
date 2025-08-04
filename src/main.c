# include "minishell.h"

int main(void)
{
    const t_arena *arena = get_allocator();
    char *prompt;
  
    while (true)
    {
		arena = init_arena(ARENA_SIZE);
		if (!arena)
        	exit(1);
        prompt = read_prompt();
		if (!prompt)
            break;
		parse_input(prompt, arena);
        free(prompt);
		clean_up((t_arena *)arena);
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
