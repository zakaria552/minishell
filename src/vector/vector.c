/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:31:24 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/15 13:42:03 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void	set_properties(t_vector *vector, int capacity, t_arena *arena);

t_vector	*init_vector(int capacity, void *content, t_arena *arena)
{
	t_vector	*vector;

	if (!arena)
		vector = malloc(sizeof(t_vector));
	else
		vector = arena->alloc(arena, sizeof(t_vector), NULL);
	if (!vector)
		return (NULL);
	set_properties(vector, capacity, arena);
	if (!arena)
		vector->data = malloc(capacity * sizeof(void *));
	else
		vector->data = arena->alloc(arena, capacity * sizeof(void *), NULL);
	if (!vector->data)
	{
		if (!arena)
			free(vector);
		return (NULL);
	}
	if (!content)
		return (vector);
	*vector->data = content;
	vector->size++;
	return (vector);
}

static void	set_properties(t_vector *vector, int capacity, t_arena *arena)
{
	vector->size = 0;
	vector->capacity = capacity;
	vector->arena = arena;
	vector->push = append;
	vector->pop = pop;
	vector->get = get_vector_elem;
	vector->free = free_vector;
	vector->clear = clear_vector;
	vector->remove = remove_element;
}

void	*append(t_vector *vector, void *content)
{
	void	**tmp_data;

	if (vector->size < vector->capacity)
	{
		*(vector->data + vector->size) = content;
		vector->size++;
		return (*(vector->data + (vector->size - 1)));
	}
	tmp_data = vector->data;
	vector->capacity = vector->capacity * 2;
	if (!vector->arena)
		vector->data = malloc(sizeof(void *) * vector->capacity);
	else
		vector->data = vector->arena->alloc(vector->arena, sizeof(void *)
				* vector->capacity, NULL);
	if (!vector->data)
		return (NULL);
	ft_memcpy(vector->data, tmp_data, (vector->capacity / 2) * sizeof(void *));
	*(vector->data + vector->size) = content;
	vector->size++;
	if (!vector->arena)
		free(tmp_data);
	return (vector->data + vector->size);
}
