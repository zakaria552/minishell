#ifndef ARENA_H
# define ARENA_H
# include "libft.h"

typedef struct s_arena	t_arena;
typedef struct s_arena
{
	void	*buffer;
	size_t	size;
	size_t	offset;
	t_arena	*next;
	void	*(*alloc)(t_arena *arena, size_t size, void *content);
	void	(*destroy)(t_arena *arena);
}	t_arena;

t_arena	*init_arena(size_t size);
void	*arena_alloc(t_arena *arena, size_t size, void *content);
t_arena	*tail_arena(t_arena *arena);
size_t	allign_p(t_arena *arena, size_t size);
void	destroy_arena(t_arena *arena);

# define ALIGNMENT (sizeof(void *)
# define ARENA_SIZE (32 * 1024)
#endif
