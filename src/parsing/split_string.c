#include "minishell.h"

static size_t	split_length(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len] && !ft_isspace(str[len]))
		len++;
	return (len);
}

t_vector	*split_string(char *str, t_arena *arena, bool split)
{
	t_vector	*output;
	char		*temp;
	ssize_t		len;

	output = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	if (!split)
	{
		append(output, str);
		return (output);
	}
	while (str && *str)
	{
		while (*str && ft_isspace(*str))
			++str;
		if (!*str && output->size > 0)
			break ;
		len = split_length(str);
		temp = arena_alloc(arena, len + 1, str);
		temp[len] = '\0';
		append(output, temp);
		str += len;
	}
	return (output);
}
