#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "arena.h"
#include "utils.h"
#include "vector.h"
#include "parsing.h"
#include "execution.h"
#include "builtins.h"
#include "ms_signals.h"

#define MAX_SHELL_LEVEL 10

typedef struct s_allocators
{
    t_arena *global;
    t_arena *prompt;
} t_allocators;

// shell
void launch_shell(bool interactive);
t_allocators *get_allocators();
extern volatile sig_atomic_t	g_signal;

#endif
