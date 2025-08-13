#include "minishell.h"

int main(int argc, char **args, char **envp)
{
  t_arena *arena;
  char *prompt;
  t_vector *vec;
  t_vector *commands;
  int i;

  (void)argc;
  (void)args;
  while (true)
  {
    arena = init_arena(ARENA_SIZE);
    if (!arena)
      exit(1);
    prompt = read_prompt(arena);
    if (!prompt)
      break;
    vec = tokenize_input(prompt, arena, '\0');
    i = -1;
    while (++i < vec->size)
      print_token((t_token *)vec->get(vec, i));
    commands = parse_tokens_to_commands(arena, vec);
    i = -1;
    while (++i < commands->size)
      print_command((t_cmd *)commands->get(commands, i));
    // todos: error handling, cleaning up the heap, refactor, global arena
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
