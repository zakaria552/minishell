/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:28:37 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/08 10:48:34 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// does a system call to find current directory, or uses local variable
void	pwd(void)
{
	char			pwd[1024];
	const char		*msg = "Couldn't access parent directory on path: ";
	t_local_vars	*vars;

	ft_memset(pwd, 0, 1024);
	getcwd(pwd, 1024);
	if (ft_strlen(pwd) > 0)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		set_status(0);
	}
	else
	{
		vars = get_local_vars();
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd(vars->pwd, 2);
		ft_putstr_fd("\n", 2);
		set_status(1);
	}
}

// creates a string of current working directory
char	*pwd_to_string(t_arena *arena)
{
	size_t	length;
	char	*pwd;
	char	*temp;

	length = 128;
	pwd = arena_alloc(arena, length, NULL);
	temp = getcwd(pwd, length);
	while (!temp && errno == ERANGE && length <= 1024)
	{
		length *= 2;
		pwd = arena_alloc(arena, length, NULL);
		temp = getcwd(pwd, length);
	}
	if (!temp)
		return (arena_strdup(arena, get_local_vars()->pwd));
	return (pwd);
}
