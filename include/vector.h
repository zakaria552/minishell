#ifndef VECTOR_H
# define VECTOR_H

# include "minishell.h"

# define INIT_VECTOR_SIZE 10

typedef struct s_vector	t_vector;

typedef struct s_vector
{
	int		size;
	int		capacity;
	size_t	elem_size;
	void	**data;
	t_arena	*arena;
	void	*(*pop)(t_vector *vector);
	void	*(*push)(t_vector *vector, void *content);
	void	*(*get)(t_vector *vector, int index);
	void	(*remove)(t_vector *vector, int index);
	void	(*free)(t_vector *vector);
	void	(*clear)(t_vector *vector);
}	t_vector;

// Vector initialization
t_vector	*init_vector(int capacity, void *content, t_arena *arena);

// Vector operation methods
void		*append(t_vector *vector, void *content);
void		*get_vector_elem(t_vector *vector, int index);
void		*pop(t_vector *vector);
void		free_vector(t_vector *vector);
void		clear_vector(t_vector *vector);
void		remove_element(t_vector *vector, int index);

#endif
