/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:16:22 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/15 11:05:17 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

void	reset_readline(char *msg, int status);
void	set_readline_handler(void);
void	set_here_doc_handler(void);
void	signal_handler(int signum, siginfo_t *act, void *next);
void	here_doc_signal_handler(int signum, siginfo_t *act, void *next);
int		here_doc_readline_flagger(void);
void	set_handler_to_default(void);
void	set_handler_to_ignore(void);
void	handle_child_signal(bool *signalled, int status);

#endif
