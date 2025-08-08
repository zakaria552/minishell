#ifndef EXECUTION_H
#define EXECUTION_H

#include "minishell.h"


void    redirect_io(t_vector *redirect);

// error handler
void    runtime_err(char *msg);

#endif