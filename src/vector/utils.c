#include "minishell.h"

void	*pop(t_vector *vector)
{
	if (vector->size == 0)
		return (NULL);
	vector->size--;
	return (vector->get(vector, vector->size));
}

void	remove_element(t_vector *vector, int index)
{
	if (index >= vector->size)
		return ;
	ft_memcpy(vector->data + index, vector->data + index + 1, (vector->size
			- index - 1) * sizeof(void *));
	vector->size--;
}

void	*get_vector_elem(t_vector *vector, int index)
{
	if (index >= vector->size)
		return (NULL);
	return (*(vector->data + index));
}

void	free_vector(t_vector *vector)
{
	free(vector->data);
	free(vector);
}

void	clear_vector(t_vector *vector)
{
	ft_memset(vector->data, 0, vector->size);
	vector->size = 0;
}
