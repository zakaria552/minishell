# include "minishell.h"

int main(void)
{
    t_arena *arena;
    char 	*prompt;

  
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
