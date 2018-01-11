#ifndef MALLOC_H
# define MALLOC_H

# include "../../libft/libft.h"
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>

# define G_MALLOC						g__malloc_instance__

/*
	- CHAQUE ZONE DOIT CONTENIR AU MOINS 100 ALLOCATIONS
	- En cas d’erreur, les fonctions malloc() et realloc() retournent un pointeur NULL
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

# define __MALLOC_TINY__			0
# define __MALLOC_SMALL__			1
# define __MALLOC_LARGE__			2

/*
 * * If set, malloc remembers the function call stack at the time of each allocation.
 */
# define MallocStackLogging 0

/*
 * * This option is similar to MallocStackLogging
 * * but makes sure that all allocations are logged,
 * * no matter how small or how short lived the buffer may be.
 */
# define MallocStackLoggingNoCompact 1

/*
 * * If set, free sets each byte of every released block to the value 0x55.
 */
# define MallocScribble 2

/*
 * * If set, malloc sets each byte of a newly allocated block to the value 0xAA.
 * * This increases the likelihood that a program making assumptions about freshly allocated memory fails.
 */
# define MallocPreScribble 3

/*
 * * If set, malloc adds guard pages before and after large allocations.
 */
# define MallocGuardEdges 4

/*
 * * Fine-grain control over the behavior of MallocGuardEdges:
 * * If set, malloc does not place a guard page at the head of each large block allocation.
 */
# define MallocDoNotProtectPrelude 5

/*
 * * Fine-grain control over the behavior of MallocGuardEdges:
 * * If set, malloc does not place a guard page at the tail of each large block allocation.
 */
# define MallocDoNotProtectPostlude 6

/*
 * * Set this variable to the number of allocations before malloc will begin validating the heap.
 * * If not set, malloc does not validate the heap.
 */
# define MallocCheckHeapStart 7

/*
 * * Set this variable to the number of allocations before malloc should validate the heap.
 * * If not set, malloc does not validate the heap.
 */
# define MallocCheckHeapEach 8

/*
 *		|				|											|
 *		|	T_MALLOC	|					DATA					|
 *		|	BLOCK		|											|
 *		|				|											|
 */

# define LOCK(mutex) pthread_mutex_lock( mutex )

# define UNLOCK(mutex) pthread_mutex_unlock( mutex )

typedef struct					s__malloc_block__
{
	size_t						size;
	struct s__malloc_block__	*next;
	int							is_free;
}								t__malloc_block__;

typedef struct					s__malloc_options__
{
	int							zone_size[2];
	int							malloc_env_vars[9];
	int							absolute_max_size;
}								t__malloc_options__;

struct							s__malloc_instance__
{
		int						is_init;
		t__malloc_options__		options;
		t__malloc_block__		*zone[3];
		void					*zone_addr[3];
};

struct							s__malloc_thread_safe__
{
	pthread_mutex_t 			global;
	pthread_mutex_t 			zone[3];
};

void							init(void);
int								init_zone(int zone);
void							put_addr(void *param);
void							print_memory(void *ptr, size_t size);
void							*new_zone(size_t size);
void							show_alloc_mem(void);
void							show_alloc_mem_ex(void);
void							show_last_alloc_mem(void);
void							show_alloc_mem_zone(int zon);

#endif
