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
    int stdin_cpy;
    int stdout_cpy;
    t_env_var *(*get)(char *variable);
    void (*set)(char *var);
    void (*unset)(char *variable);
	char	*pwd;
    bool    pipeline;
    bool    io_err;
} t_local_vars;

// local vars
void    init_local_vars(char **envp);
t_local_vars *get_local_vars();
t_env_var    *init_var(char *envp_var, t_arena *arena);
void    remove_var(char *variable);
t_env_var    *get_var(char *variable);
void    set_var(char *env_var);
void    set_status(int status);
t_vector *sorted_envp_vars(t_local_vars *vars);

// buitins
void    export(t_cmd *cmd);
void    unset(t_cmd *cmd);
void    env(void);
void    builtin_exit(t_cmd *cmd, bool *should_exit);
void    echo(t_cmd *cmd);
void	cd(t_cmd *cmd);
void	pwd(void);

// utils
bool    is_builtin(char *cmd);
bool strmatch(char *s1, char *s2);
char	*pwd_to_string(t_arena *arena);
char	*arena_int_to_string(t_arena *arena, int num);
void    update_shell_level(t_local_vars *vars);
int	long_atoi(const char *nptr, bool *error);

#endif
