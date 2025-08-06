#include "minishell.h"

void    *append(t_vector *vector, void *content)
{
    void **tmp_data;

    if (vector->size <= vector->capacity)
    {
        *(vector->data + vector->size) = content;
        vector->size++;
        return (*(vector->data + vector->size));
    }
    tmp_data = vector->data;
    vector->capacity = vector->capacity * 2;
    if (!vector->arena)
        vector->data = malloc(sizeof(void *) * vector->capacity);
    else
        vector->data = vector->arena->alloc(vector->arena, sizeof(void *) * vector->capacity, NULL);
    if (!vector->data)
        return (NULL);
    ft_memcpy(vector->data, tmp_data, vector->capacity / 2);
    *(vector->data + vector->size) = content;
    vector->size++;
    if (!vector->arena)
        free(tmp_data);
    return (vector->data + vector->size);
}

void    *pop(t_vector *vector)
{
    if (vector->size == 0)
        return NULL;
    vector->size--;
    return (vector->get(vector, vector->size));
}

void    *get_vector_elem(t_vector *vector, int index)
{
	void	*temp;

    if (index > vector->size)
        return (NULL);
    return *(vector->data + index);
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
