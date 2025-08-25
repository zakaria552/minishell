#include "minishell.h"

static char	*read_prompt(char *prompt_msg, bool update_history);
static void	display_working_dir(void);
static char	*get_pwd(void);

char	*int_tty_prompt(char *prompt_msg, bool update_history, bool interactive)
{
	t_allocators	*allocs;
	char			*prompt;
	char			*arena_prompt;
	char			*line;

	allocs = get_allocators();
	if (interactive)
		return (read_prompt(prompt_msg, update_history));
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	prompt = ft_strtrim(line, "\n");
	if (!prompt)
	{
		free(line);
		return (NULL);
	}
	free(line);
	arena_prompt = arena_strdup(allocs->prompt, prompt);
	free(prompt);
	return (arena_prompt);
}

static char	*read_prompt(char *prompt_msg, bool update_history)
{
	t_allocators	*allocs;
	char			*prompt;
	char			*arena_prompt;

	allocs = get_allocators();
	if (update_history)
		display_working_dir();
	prompt = readline(prompt_msg);
	if (!prompt)
	{
		if (errno > 0)
			runtime_err(errno, NULL);
		return (NULL);
	}
	arena_prompt = arena_alloc(allocs->prompt, ft_strlen(prompt) + 1, prompt);
	free(prompt);
	if (update_history)
		add_history(arena_prompt);
	return (arena_prompt);
}

static char	*get_pwd(void)
{
	const t_local_vars	*vars = get_local_vars();
	const t_env_var		*home = vars->get("HOME");
	int					len;
	int					i;

	if (!home)
		return (vars->pwd);
	len = ft_strlen(home->value);
	i = -1;
	while (++i < len)
	{
		if (vars->pwd[i] != home->value[i])
			return (vars->pwd);
	}
	return (arena_strjoin(get_allocators()->prompt, "~", vars->pwd + i));
}

static void	display_working_dir(void)
{
	char	*pwd;
	char	*working_dir;
	char	*tmp;

	pwd = get_pwd();
	working_dir = ft_strrchr(pwd, '/');
	if (!working_dir)
	{
		ft_printf("\x1B[38;5;93m%s\e[0m\n", pwd);
		return ;
	}
	tmp = working_dir;
	working_dir++;
	*tmp = '\0';
	ft_printf("\x1B[38;5;135m%s/\e[0m\x1B[38;5;93m%s\e[0m\n", pwd, working_dir);
}
