#include "minishell.h"

int main(int argc, char **args, char **envp)
{
    t_allocators *allocs = get_allocators();
    char *prompt;
    t_vector *vec;
    t_vector *commands;
    init_local_vars(envp);
    (void)argc;
    (void)args;
    while (true)
    {
        ft_printf("Status: %d\n", get_local_vars()->status);
        allocs->prompt = init_arena(ARENA_SIZE);
        prompt = read_prompt("minishell> ", true);
        if (!prompt)
            break;
        vec = tokenize_input(prompt, allocs->prompt, '\0');
        // i = -1;
        // while (++i < vec->size)
        //     print_token((t_token *)vec->get(vec, i));
        commands = parse_tokens_to_commands(allocs->prompt, vec);
        // i = -1;
        // while (++i < commands->size)
        //     print_command((t_cmd *)commands->get(commands, i));
        // todos: error handling, cleaning up the heap, refactor, global arena
        handle_here_doc(commands);
        execution(commands, allocs->prompt);
        clean_up(false, false);
    }
    return (0);
}

t_allocators *get_allocators()
{
    static t_allocators arenas;

    if (!arenas.global)
        arenas.global = init_arena(ARENA_SIZE);
    return (&arenas);
}
