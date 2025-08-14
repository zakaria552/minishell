/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:04 by zfarah            #+#    #+#             */
/*   Updated: 2025/08/14 18:04:19 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_exc_path(char *paths, char *cmd, t_arena *arena);
static char *get_env_variable(char **envp, char *variable);
bool is_executable(char *path);

void *set_errno(int err_code)
{
	errno = err_code;
	return (NULL);
}

char *get_binary_path(char *command, char **envp, t_arena *arena)
{
	char *path;
	char *exc_path;

	if (command != NULL && ft_strchr(command, '/'))
	{
		if (!is_executable(command))
			cmd_not_found_err(errno, command, false);
		return command;
	}
	path = get_env_variable(envp, "PATH=");
	if (!path)
		cmd_not_found_err(127, command, false);
	exc_path = get_exc_path(path, command, arena);
	if (!exc_path)
		cmd_not_found_err(errno, command, true);
	return (exc_path);
}

char *get_exc_path(char *path, char *cmd, t_arena *arena)
{
	const int len = strlen(cmd);
	char *exc_path;
	int i;

	while (*path)
	{
		i = 0;
		while (path[i] && path[i] != ':')
			i++;
		exc_path = arena_alloc(arena, i + len + 2, NULL);
		exc_path[i + len + 1] = '\0';
		exc_path[i] = '/';
		ft_memcpy(exc_path, path, i);
		ft_memcpy(exc_path + i + 1, cmd, len);
		if (is_executable(exc_path))
			return (exc_path);
		if (!path[i])
			break;
		path = path + i + 1;
	}
	errno = 127;
	return (NULL);
}

char *get_env_variable(char **envp, char *variable)
{
	size_t len;
	int i;

	len = ft_strlen(variable);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], variable, len) == 0)
			return (envp[i] + len);
	}
	return (NULL);
}

bool is_executable(char *path)
{
	return (access(path, X_OK) == 0);
}