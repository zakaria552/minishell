#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "arena.h"
#include "utils.h"
#include "vector.h"
#include "parsing.h"
#include "execution.h"

typedef struct s_allocators
{
    t_arena *global;
    t_arena *tmp;
} t_allocators;

t_arena *get_allocator();
t_allocators *get_allocators();

#endif
