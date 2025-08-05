#include "vector.h"

t_vector *init_vector(int capacity, size_t elem_size, void *content)
{
    t_vector *vector;

    vector = malloc(sizeof(t_vector));
    if (!vector)
        return (NULL);
    vector->size = 0;
    vector->elem_size = elem_size;
    vector->capacity = capacity;
    vector->push = append;
    vector->pop = pop;
    vector->get = get_vector_elem;
    vector->free = free_vector;
    vector->clear = clear_vector;
    vector->data = malloc(elem_size * capacity);
    if (!vector->data)
    {
        free(vector);
        return (NULL);
    }
    if (!content)
        return (vector);
    ft_memcpy(vector->data, content, vector->elem_size);
    vector->size++;
    return (vector);
}
