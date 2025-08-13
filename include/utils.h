#ifndef UTILS_H
#define UTILS_H

#include "arena.h"

// clean_up utils
void    clean_up(t_arena *arena, bool clean_history);
void    clean_exit(t_arena *arena, int err_code, char *msg);
void	ft_error(char *msg);

//  prompt utils
char *read_prompt(t_arena *arena);

#endif
