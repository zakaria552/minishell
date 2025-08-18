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

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    match = ft_strncmp(s2, s1, len1) == 0;
    return (len1 == len2 && match);
}
