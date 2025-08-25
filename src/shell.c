#include "minishell.h"

void launch_shell(void)
{
    t_allocators *allocs;
    t_vector *commands;
    char *prompt;

	allocs = get_allocators();
	while (true)
	{
		allocs->prompt = init_arena(ARENA_SIZE);
		set_readline_handler();
		prompt = int_tty_prompt(PROMPT_MSG, true, isatty(STDIN_FILENO));
		if (!prompt)
		   break;
		commands = tokenize_input(prompt, allocs->prompt, '\0');
		if (!commands)// || g_signal == 130)
		{
			clean_up(false, false);
	//		g_signal = 0;
			continue ;
		}
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