/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:04 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/15 14:32:44 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_exc_path(char *paths, char *cmd, t_arena *arena);
static char *get_env_variable(char **envp, char *variable);
static char *command_exist(char *path);

void *set_errno(int err_code)
{
	errno = err_code;
	return (NULL);
}

char *format_path(char *command, char **envp, t_arena *arena)
{
	char *path;
	char *exc_path;

	if (command != NULL && ft_strchr(command, '/'))
	{
		exc_path = command_exist(command);
		if (!exc_path)
			return NULL;
		return (exc_path);
	}
	path = get_env_variable(envp, "PATH=");
	if (!path)
	{
		ft_printf("Pipex: command not found: %s\n", command);
		return NULL;
	}
	exc_path = get_exc_path(path, command, arena);
	if (!exc_path)
		ft_printf("Pipex: command not found: %s\n", command);
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
		exc_path = arena->alloc(arena, i + len + 2, NULL);
		if (!exc_path)
			return (set_errno(ENOMEM));
		exc_path[i + len + 1] = '\0';
		exc_path[i] = '/';
		ft_memcpy(exc_path, path, i);
		ft_memcpy(exc_path + i + 1, cmd, len);
		if (access(exc_path, X_OK) == 0)
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

char *command_exist(char *path)
{
	char *dup_path;

	if (access(path, X_OK) < 0)
	{
		ft_printf("Pipex: %s: %s\n", strerror(errno), path);
		return (set_errno(errno));
	}
	dup_path = ft_strdup(path);
	if (!dup_path)
		return (set_errno(5));
	return (dup_path);
}