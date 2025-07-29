# include "minishell.h"

int main(int argc, char **args)
{
    const t_arena *arena = init_arena(ARENA_SIZE);
    char *prompt;

    if (!arena)
        exit(1);
    while (true)
    {
        prompt = read_prompt();
        if (!prompt)
            break;
        free(prompt);
    }
    clean_up(arena);
    return (0);
}
