/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:31:26 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:31:27 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

int	main(int argc, char **args, char **envp)
{
	int	status;

	(void)argc;
	(void)args;
	init_local_vars(envp);
	launch_shell();
	status = get_local_vars()->status;
	clean_up(true, true);
	return (status);
}
