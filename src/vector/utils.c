/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:31:21 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:31:22 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
