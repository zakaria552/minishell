#include "minishell.h"

char *read_prompt(char *prompt_msg, bool update_history)
{
	t_allocators *allocs = get_allocators();
    char *prompt;
	char *arena_prompt;
    
    prompt = readline(prompt_msg);
	if (!prompt)
	{
		if (errno > 0)
			runtime_err(errno, NULL);
		return NULL;
	}
	arena_prompt = arena_alloc(allocs->prompt, ft_strlen(prompt) + 1, prompt);
	free(prompt);
	if (update_history)
    	add_history(arena_prompt);
    return (arena_prompt);
}

char *int_tty_prompt(char *prompt_msg, bool update_history, bool interactive)
{
	t_allocators *allocs = get_allocators();
    char *prompt;
	char *arena_prompt;
	char *line;
    
	if (interactive)
    	return read_prompt(prompt_msg, update_history);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return NULL;
	prompt = ft_strtrim(line, "\n");
	if (!prompt)
	{
		free(line);
		return NULL;
	}
	free(line);
	arena_prompt = arena_strdup(allocs->prompt, prompt);
	free(prompt);
    return (arena_prompt);
}
