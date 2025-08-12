#include "minishell.h"

char *read_prompt(t_arena *arena)
{
    char *prompt;
	char *arena_prompt;
    
    prompt = readline("minishell>> ");
	if (!prompt)
		return (NULL);
	arena_prompt = arena_alloc(arena, ft_strlen(prompt) + 1, prompt);
	free(prompt);
    add_history(arena_prompt);
    return (arena_prompt);
}
