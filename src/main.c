# include "minishell.h"

t_vector *test_redirects(void)
{
	t_vector *v = init_vector(1, NULL, NULL);
	t_token *tok = malloc(sizeof(t_token));

	tok->type = INPUT_REDIR;
	tok->content = ft_strdup("Makefile");
	tok->read_chars = 0;
	v->push(v, tok);
	return v;
}

t_vector *commands(void)
{
	t_vector *v = init_vector(1, NULL, NULL);
	t_cmd *cmd = malloc(sizeof(t_cmd));

	cmd->cmd = ft_strdup("cat");
	v->push(v, cmd);
	cmd->redirects = test_redirects();
	cmd->args = malloc(sizeof(char *) * 3);
	cmd->args[2] = NULL;
	cmd->args[0] = cmd->cmd;
	cmd->args[1] = ((t_token *)cmd->redirects->get(cmd->redirects, 0))->content;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = ft_strdup("cat");
	v->push(v, cmd);
	cmd->redirects = init_vector(1, NULL, NULL);
	ft_printf("reached here\n");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[1] = NULL;
	cmd->args[0] = cmd->cmd;
	return v;
}

int main(int argc, char **args, char **envp)
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
        //prompt = read_prompt();
		//if (!prompt)
        //    break;
		vec = tokenize_input(prompt, arena);
		ft_printf("--------->\n");
		vec = commands();
		ft_printf("args: %s", ((t_cmd *)vec->get(vec, 0))->args[1]);
		execution(vec, arena, envp);
		exit(1);
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
