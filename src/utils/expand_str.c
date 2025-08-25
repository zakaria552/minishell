#include "minishell.h"

static char			*append_till_next_char(char *dest, char **src, char c,
						t_arena *arena);
static t_env_var	*expand_var(char *str, char c, t_arena *arena);

char	*expand_str(char *str, t_arena *arena)
{
	char		*expanded;
	t_env_var	*var;
	char		*dstr;

	dstr = arena_strdup(arena, str);
	expanded = arena_strdup(arena, "");
	while (dstr && *dstr)
	{
		expanded = append_till_next_char(expanded, &dstr, '$', arena);
		if (!*dstr)
			break ;
		var = expand_var(dstr, '$', arena);
		if (var)
		{
			expanded = arena_strjoin(arena, expanded, var->value);
			dstr += ft_strlen(var->variable) + 1;
			continue ;
		}
		dstr++;
		while (*dstr && *dstr != '$' && !ft_isspace(*dstr))
			dstr++;
	}
	return (expanded);
}

static char	*append_till_next_char(char *dest, char **srcp, char c,
		t_arena *arena)
{
	char	*tmp;
	char	*src;
	int		len;
	int		i;

	src = *srcp;
	i = 0;
	len = ft_strlen(dest);
	while (src[i] && src[i] != c)
		i++;
	len += i;
	tmp = arena->alloc(arena, len + 1, NULL);
	ft_memcpy(tmp, dest, len - i);
	ft_memcpy(tmp + (len - i), src, i);
	*srcp += i;
	return (tmp);
}

static t_env_var	*expand_var(char *str, char c, t_arena *arena)
{
	const t_local_vars	*vars = get_local_vars();
	t_env_var			*var;
	char				*var_name;
	int					i;
	int					len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != c)
		i++;
	i++;
	while (str[i] && str[i] != c && !ft_isspace(str[i]))
	{
		len++;
		i++;
	}
	var_name = arena->alloc(arena, len + 1, NULL);
	while (--len >= 0)
		var_name[len] = str[--i];
	var = vars->get(var_name);
	if (!var)
		return (NULL);
	return (var);
}
