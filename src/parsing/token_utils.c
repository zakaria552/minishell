#include "minishell.h"

int	is_string_delimiter(char c)
{
	if (ft_isspace(c))
		return (1);
	if (c == '|' || c == '>' || c == '<' || c == '$' || c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_legal_expansion_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

ssize_t	expansion_length(char *s)
{
	ssize_t	length;

	length = 1;
	if (s[length] == '?' || s[length] == '_' || ft_isdigit(s[length]))
		return (2);
	while (is_legal_expansion_char(s[length]))
		++length;
	return (length);
}

ssize_t	dummy_length(char *s)
{
	if (*s == '>' && *(s + 1) == '>')
		return (2);
	if (*s == '<' && *(s + 1) == '<')
		return (2);
	return (1);
}
