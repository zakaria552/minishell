# include "minishell.h"

//TODO:cleanup and perror, strerror setting before exit
int	ft_exit(void)
{
	exit(1);
}

int main(void)
{
    t_arena 	*arena;
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
			tok = *(t_token **)vec->get(vec, i);
			print_token(tok);
			++i;
		}
        free(prompt);
		clean_up((t_arena *)arena, false);
    }
	return (0);
}
