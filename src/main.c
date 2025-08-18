#include "minishell.h"
volatile sig_atomic_t	g_signal;

int main(int argc, char **args, char **envp)
{
    t_allocators *allocs = get_allocators();
    char *prompt;
    t_vector *vec;
    t_vector *commands;

	(void)argc;
	(void)args;
	init_local_vars(envp);
	while (true)
	{
		allocs->prompt = init_arena(ARENA_SIZE);
		set_readline_handler();
		prompt = read_prompt("minishell> ", true);
		if (!prompt)
		   break;
		vec = tokenize_input(prompt, allocs->prompt, '\0');
		if (!vec)
		   continue ;
        commands = parse_tokens_to_commands(allocs->prompt, vec);
		if (!commands)
		   continue ;
        handle_here_doc(commands);
        execution(commands, allocs->prompt);
        clean_up(false, false);
    }
    return (0);
}

t_allocators *get_allocators()
{
	static t_allocators arenas;

    if (!arenas.global)
        arenas.global = init_arena(ARENA_SIZE);
    return (&arenas);
}
