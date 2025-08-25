#include "minishell.h"

static bool	invalid_err_msg(char *var);
static bool	is_valid_export(char *joint);
static void	print_exported_vars(t_local_vars *vars);

void	export(t_cmd *cmd)
{
	t_local_vars	*vars;
	char			*arg;
	int				i;

	i = -1;
	vars = get_local_vars();
	while (++i < cmd->args->size)
	{
		arg = cmd->args->get(cmd->args, i);
		if (!is_valid_export(arg))
		{
			vars->status = 1;
			continue ;
		}
		vars->set(arg);
		vars->status = 0;
	}
	if (cmd->args->size == 0)
		print_exported_vars(vars);
}

static bool	is_valid_export(char *joint)
{
	int	i;

	i = -1;
	if (!joint || *joint == '=' || ft_isdigit(*joint))
		return (invalid_err_msg(joint));
	while (joint[++i] && joint[i] != '=')
	{
		if (!is_legal_expansion_char(joint[i]))
			return (invalid_err_msg(joint));
	}
	return (true);
}

static bool	invalid_err_msg(char *var)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
	return (false);
}

static void	print_exported_vars(t_local_vars *vars)
{
	const t_vector	*sorted = sorted_envp_vars(vars);
	t_env_var		*var;
	char			*tmp;
	int				i;

	i = -1;
	while (++i < sorted->size)
	{
		var = sorted->get((t_vector *)sorted, i);
		if (*var->variable == '_')
			continue ;
		tmp = ft_strrchr(var->joint, '=');
		if (var->value && tmp && *(tmp + 1))
			ft_printf("declare -x %s=\"%s\"\n", var->variable, var->value);
		else if (tmp && !*(tmp + 1))
			ft_printf("declare -x %s=\"\"\n", var->variable);
		else
			ft_printf("declare -x %s\n", var->variable);
	}
	vars->status = 0;
}
