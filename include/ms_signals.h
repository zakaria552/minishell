/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:54:50 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/18 15:41:19 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

void	set_readline_handler(void);
void	set_here_doc_handler(void);
void	signal_handler(int signum, siginfo_t *act, void *next);
void	here_doc_signal_handler(int signum, siginfo_t *act, void *next);
int 	here_doc_readline_flagger(void);
void	set_handler_to_default(void);
void	set_handler_to_ignore(void);

# include <signal.h>
# include <sys/types.h>

extern volatile sig_atomic_t	g_handler_flag;

#endif
