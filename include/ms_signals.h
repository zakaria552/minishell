/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:54:50 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/15 14:10:12 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# include <signal.h>
# include <sys/types.h>

extern volatile sig_atomic_t	g_handler_flag;

void	set_readline_handler(void);
void	set_here_doc_handler(void);
void	handler(int signum, siginfo_t *act, void *next);
void	here_doc_handler(int signum, siginfo_t *act, void *next);

#endif
