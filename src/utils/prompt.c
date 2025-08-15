#include "minishell.h"

char *read_prompt(char *prompt_msg, bool update_history)
{
	t_allocators *allocs = get_allocators();
    char *prompt;
	char *arena_prompt;
    
    prompt = readline(prompt_msg);
	if (!prompt)
		return (NULL);
	arena_prompt = arena_alloc(allocs->prompt, ft_strlen(prompt) + 1, prompt);
	free(prompt);
	if (update_history)
    	add_history(arena_prompt);
    return (arena_prompt);
}
