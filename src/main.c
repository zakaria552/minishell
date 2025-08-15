#include "minishell.h"

int main(int argc, char **args, char **envp)
{
    t_allocators *allocs = get_allocators();
    char *prompt;
    t_vector *vec;
    t_vector *commands;

	(void)argc;
	(void)args;
	(void)i;
  while (true)
  {
     arena = init_arena(ARENA_SIZE);
	set_readline_handler();
     if (!arena)
       exit(1);
     prompt = read_prompt(arena);
     if (!prompt)
       break;
     vec = tokenize_input(prompt, arena, '\0');
     commands = parse_tokens_to_commands(arena, vec);
	if (!commands)
	{
		clean_up((t_arena *)arena, false);
		continue ;
	}
     handle_here_doc(commands);
     execution(commands, arena, envp);
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

t_allocators *get_allocators()
{
    static t_allocators arenas;

    if (arenas.global)
        arenas.global = init_arena(ARENA_SIZE);
    return (&arenas);
}
