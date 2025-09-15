/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:16:27 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/15 14:07:31 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

# define MINISHELL_ASCII_TITLE \
	" __ __    __  __  _         _       _            _  _    __ __\n\
 \\ \\\\ \\  |  \\/  |(_) _ __  (_) ___ | |__    ___ | || |  / // /\n\
  \\ \\\\ \\ | |\\/| || || '_ \\ | |/ __|| '_ \\  / _ \\| || | / // / \n\
  / // / | |  | || || | | || |\\__ \\| | | ||  __/| || | \\ \\\\ \\ \n\
 /_//_/  |_|  |_||_||_| |_||_||___/|_| |_| \\___||_||_|  \\_\\\\_\\\n\
\n"

# define MINISHELL_BORDER_MSG \
	"\
  * Description: A simple Unix shell developed in C language\n\
  * Repository:		https://github.com/zakaria552/minishell\n\
  * Authers:		Zakaria, Niklas\n\
  * Issues:		Feel free to raise any issues or bugs you encounter\n\
  * TTY:         %s\n"

# define PROMPT_PWD "\001\x1b[38;5;93m\002%s\001\x1b[0m\002\n"
# define PROMPT_HOME "\001\x1b[38;5;135m\002%s/\001\x1b[0m\002"
# define PROMPT_CURRENT_DIR "\001\x1b[38;5;93m\002%s\001\x1b[0m\002\n"

// error handlers
void	runtime_err(int err_code, char *msg);
void	syntax_err(int err_code, char *msg);
void	cmd_not_found_err(int err_code, char *cmd, bool path_exist);
void	clean_exit(int err_code, char *msg);
void	shell_err(char *msg);
void	clean_runtime_err(int err_code, char *msg, int *curr_pipe,
			int *next_pipe);

// clean ups
void	clean_up_and_exit(int err_code);
void	clean_up(bool clean_global, bool clean_history);

//  prompt utils
char	*int_tty_prompt(char *prompt_msg, bool update_history,
			bool interactive);
void	border_message(void);

// expand string
char	*expand_str(char *str, t_arena *arena);
char	*alt_expand_str(t_arena *arena, char *str);

#endif
