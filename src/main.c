# include "minishell.h"

//TODO:cleanup and perror, strerror setting before exit
int	ft_exit(void)
{
	exit(1);
}

int main(void)
{
    const t_arena *arena = get_allocator();
    char *prompt;
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
			tok = *(t_token **)vec->get(vec, i);
			print_token(tok);
			++i;
		}
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
