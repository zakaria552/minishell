/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:16:20 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/08 10:55:46 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include "arena.h"
# include "utils.h"
# include "vector.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
# include "ms_signals.h"

# define MAX_SHELL_LEVEL 10
# define PROMPT_MSG "\001\x1b[38;5;21m\002> \001\x1b[0m\002"
# define PROMPT_HEREDOC_MSG "\001\x1b[38;5;21m\002here_doc> \001\x1b[0m\002"

typedef struct s_allocators
{
	t_arena	*global;
	t_arena	*prompt;
}	t_allocators;

// shell
void			launch_shell(void);
t_allocators	*get_allocators(void);

extern volatile sig_atomic_t	g_signal;

#endif
