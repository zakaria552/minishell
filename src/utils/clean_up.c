#include "minishell.h"

void    clean_up(t_arena *arena)
{
    arena->destroy(arena);
    clear_history();
}
