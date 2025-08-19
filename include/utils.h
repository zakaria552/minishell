#ifndef UTILS_H
#define UTILS_H

#include "minishell.h"

// error handlers
void    runtime_err(int err_code, char *msg);
void    syntax_err(int err_code, char *msg);
void    clean_up(bool clean_global, bool clean_history);
void    cmd_not_found_err(int err_code, char *cmd, bool path_exist);

//  prompt utils
char *read_prompt(char *prompt_msg, bool update_history);

// expand string
char *expand_str(char *str, t_arena *arena);
#endif
