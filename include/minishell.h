#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "libft.h"
#include "arena.h"
#include "utils.h"
#include "vector.h"
#include "parsing.h"
#include "execution.h"

t_arena *get_allocator();

#endif
