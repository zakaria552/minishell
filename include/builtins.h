#ifndef BUILTINS_H
#define BUILTINS_H

#include "vector.h"

typedef struct s_env_var
{
    char *variable; // PATH
    char *value; // /usr/bin
    char *joint; // PATH=/usr/bin
} t_env_var;

typedef struct s_local_vars
{
    t_vector *envp;
    int status;
    t_env_var *(*get)(char *variable);
    void (*set)(char *var);
    void (*unset)(char *variable);
} t_local_vars;

// local vars
void    init_local_vars(char **envp);
t_local_vars *get_local_vars();
t_env_var    *init_var(char *envp_var, t_arena *arena);
void    remove_var(char *variable);
t_env_var    *get_var(char *variable);
void    set_var(char *env_var);

#endif