#include "minishell.h"

char *read_prompt(void)
{
    char *prompt;
    
    prompt = readline("minishell>> ");
    if (!prompt)
        return (NULL);
    add_history(prompt);
    return (prompt);
}
