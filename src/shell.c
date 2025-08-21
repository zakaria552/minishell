#include "minishell.h"

void launch_shell(bool interactive)
{
    t_allocators *allocs;
    t_vector *commands;
    t_vector *vec;
    char *prompt;

	allocs = get_allocators();
	while (true)
	{
		allocs->prompt = init_arena(ARENA_SIZE);
		set_readline_handler();
		prompt = int_tty_prompt("", true, interactive);
		if (!prompt)
		   break;
		vec = tokenize_input(prompt, allocs->prompt, '\0');
		if (!vec)
		   continue ;
        commands = parse_tokens_to_commands(allocs->prompt, vec);
		if (!commands)
		   continue ;
        handle_here_doc(commands);
        execute_commands(commands, allocs->prompt);
        clean_up(false, false);
    }
}

t_allocators *get_allocators()
{
	static t_allocators arenas;

    if (!arenas.global)
        arenas.global = init_arena(ARENA_SIZE);
    return (&arenas);
}