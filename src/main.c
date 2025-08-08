# include "minishell.h"

t_vector *test_redirects(void)
{
	t_vector *v = init_vector(1, NULL, NULL);
	t_token *tok = malloc(sizeof(t_token));

	tok->type = INPUT_REDIR;
	tok->content = ft_strdup("file1");
	tok->read_chars = 0;
	v->push(v, tok);
	return v;
}

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
		ft_printf("--------->\n");
		redirect_io(test_redirects());
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
