#ifndef MALLOC_H
# define MALLOC_H

# include "../../libft/libft.h"
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdio.h>
# include <pthread.h>
# include <stdint.h>
# define G_MALLOC						g__malloc_instance__
/*
		CHQUE ZONE DOIT CONTENIR AU MOINS 100 ALLOCATIONS
*/
# define __MALLOC_TINY_LIMIT__		993
# define __MALLOC_SMALL_LIMIT__		127000
# define __MALLOC_LARGE_LIMIT__		10000000000

# define __MALLOC_TINY_QUANTUM__	16
# define __MALLOC_SMALL_QUANTUM__	512
# define __MALLOC_LARGE_QUANTUM__	4000
/*
 *		Gonna * getpagesize()
 */
# define __MALLOC_TINY_ZONE_SIZE__	2000000
# define __MALLOC_SMALL_ZONE_SIZE__	16000000
/*
 *
 *		|				|											|
 *		|	T_MALLOC	|					DATA					|
 *		|	BLOCK		|											|
 *		|				|											|
 */
# define LOCK(mutex) pthread_mutex_lock( mutex )
# define UNLOCK(mutex) pthread_mutex_unlock( mutex )

typedef struct	s__malloc_block__
{
	size_t						size;
	struct s__malloc_block__	*next;
	int							is_free;
}				t__malloc_block__;

typedef struct	s__malloc_options__
{
	int				tiny_zone_size;
	int				small_zone_size;
	int				absolute_max_size;
}				t__malloc_options__;

struct	s__malloc_instance__
{
		int						is_init;
		t__malloc_options__		options;
		t__malloc_block__		*tiny_zone;
		t__malloc_block__		*small_zone;
		t__malloc_block__		*large_zone;
		void					*tiny_zone_addr;
		void					*small_zone_addr;
		void					*large_zone_addr;
};

struct	s__malloc_thread_safe__
{
	pthread_mutex_t 		global;
	pthread_mutex_t 		tiny;
	pthread_mutex_t 		small;
	pthread_mutex_t 		large;
};

void						init(void);
void						init_tiny_zone(void);
void						print_memory(void *ptr, size_t size);
void						*new_zone(size_t size);
void						show_alloc_mem(void);

#endif
