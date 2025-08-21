#include "minishell.h"

bool    is_builtin(char *cmd)
{
    const char *builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int i;
    
    i = -1;
    while (++i < 7)
    {
        if (strmatch(cmd, (char *)builtins[i]))
            return (true);
    }
    return (false);
}

bool strmatch(char *s1, char *s2)
{ 
    int len1;
    int len2;
    bool match;

    if (!s1 || !s2)
        return false;
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    match = ft_strncmp(s2, s1, len1) == 0;
    return (len1 == len2 && match);
}

void    update_shell_level(t_local_vars *vars)
{
    const t_allocators *allocs = get_allocators();
    t_env_var *var;
    bool err = false;
    int level;
    var = vars->get("SHLVL");
    if (!var)
    {
        vars->set("SHLVL=1");
        return;
    }
    level = long_atoi(var->value, &err);
    if (err || level > MAX_SHELL_LEVEL)
        level = 1;
    else
        level++;
    char *j = arena_strjoin(allocs->global, "SHLVL=", ft_itoa(level));
    vars->set(j);
}

int	long_atoi(const char *nptr, bool *error)
{
	long long	num;
	int	    i;
	int	    sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (nptr[i] && nptr[i] <= '9' && nptr[i] >= '0')
	{
        if (((num * 10) + (nptr[i] - '0')) < num)
            break;
		num = num * 10 + nptr[i] - '0';
		i++;
	}
    if (nptr[i])
        *error = true;
    return (num * sign);
}
