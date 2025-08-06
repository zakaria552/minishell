#include "minishell.h"

void    *append(t_vector *vector, void *content)
{
    void *tmp_data;

    if (vector->size <= vector->capacity)
    {
        ft_memcpy(vector->data + (vector->elem_size * vector->size),
                content, vector->elem_size);
        vector->size++;
        return (vector->data + vector->elem_size * vector->size);
    }
    tmp_data = vector->data;
    vector->capacity = vector->capacity * 2;
    vector->data = malloc(vector->elem_size * (vector->capacity / 2));
    if (!vector->data)
        return (NULL);
    ft_memcpy(vector->data, tmp_data, vector->capacity / 2);
    ft_memcpy(vector->data + (vector->elem_size * vector->size),
                content, vector->elem_size);
    vector->size++;
    free(tmp_data);
    return (vector->data + vector->elem_size * vector->size);
}

void    pop(t_vector *vector)
{
    vector->size--;
    ft_memset(vector->data + vector->elem_size * vector->size, 0, vector->elem_size);
}

void    *get_vector_elem(t_vector *vector, int index)
{
	void	*temp;

    if (index > vector->size)
		return (NULL);
	temp = vector->data + vector->elem_size * index;
    return (vector->data + vector->elem_size * index);
}

void    free_vector(t_vector *vector)
{
    free(vector->data);
    free(vector);
}

void    clear_vector(t_vector *vector)
{
    ft_memset(vector->data, 0, vector->size);
    vector->size = 0;
}
