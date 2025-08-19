#include "minishell.h"

//does a system call to find current directory
//TODO:use local variable to store it and update it?
void	pwd(void)
{
	char	*temp;

	temp = getcwd(temp, NULL);
	if (temp)
		ft_printf("%s\n", temp);
	free(temp);
}
