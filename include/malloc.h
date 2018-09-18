/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 11:40:22 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 14:58:58 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>

/*
** 	ATTENTION!
** 	Les variables globales depndent d'un processus.
** 	Lors d'un fork, celle ci est duplique et n'est plus partagee
** 	meme si c'est un pointeur
*/

# define G_MALLOC						g__malloc_instance__

/*
** CHAQUE ZONE DOIT CONTENIR AU MOINS 100 ALLOCATIONS
** En cas d’erreur, les fonctions malloc() et realloc()
** retournent un pointeur NULL
*/

# define __MALLOC_TINY_LIMIT__		992
# define __MALLOC_SMALL_LIMIT__		127000
# define __MALLOC_LARGE_LIMIT__		10000000000

# define __MALLOC_TINY_QUANTUM__	16
# define __MALLOC_SMALL_QUANTUM__	512
# define __MALLOC_LARGE_QUANTUM__	4000

/*
** Gonna getpagesize()
*/
# define __MALLOC_TINY_ZONE_SIZE__	2000000
# define __MALLOC_SMALL_ZONE_SIZE__	16000000

# define __MALLOC_TINY__			0
# define __MALLOC_SMALL__			1
# define __MALLOC_LARGE__			2

# define SIZE_MAX 1000000000000

/*
** If set, free sets each byte of every released block to the value 0x55.
*/
# define MALLOCSCRIBBLE 0

/*
** If set, malloc sets each byte of a newly allocated block to the value 0xAA.
** This increases the likelihood that a program making assumptions
** about freshly allocated memory fails.
*/
# define MALLOCPRESCRIBBLE 1

/*
** If set, malloc adds guard pages before and after large allocations.
*/
# define MALLOCGUARDEDGES 2

/*
** Fine-grain control over the behavior of MallocGuardEdges:
** If set, malloc does not place a guard
** page at the head of each large block allocation.
*/
# define MALLOCDONOTPROTECTPRELUDE 3

/*
** Fine-grain control over the behavior of MallocGuardEdges:
** If set, malloc does not place a guard page at the tail
** of each large block allocation.
*/
# define MALLOCDONOTPROTECTPOSTLUDE 4

# define LOCK(mutex) pthread_mutex_lock( mutex )

# define UNLOCK(mutex) pthread_mutex_unlock( mutex )

/*
**		|				    |								|
**		|	T_MALLOC		|					DATAS		|
**		|	BLOCK		  	|								|
**		|				    |								|
*/
typedef struct					s__malloc_block__
{
	size_t						size;
	struct s__malloc_block__	*next;
	int							is_free;
}								t__malloc_block__;

/*
** @params
** int* zone_size : an array including the size of each zone
** int* malloc_env_vars : an array including the env vars
*/
typedef struct					s__malloc_options__
{
	int							zone_size[2];
	size_t						zone_quantums[3];
	int							malloc_env_vars[6];
	int							absolute_max_size;
}								t__malloc_options__;

/*
** Defines an instance of memory allocation
** (used for malloc, calloc, etc)
** It is a static structure, declared once in the code
**  int 				is_init : Tells if the instance has been instancied once
**	t__malloc_options__	options;
**	t__malloc_block__	*zone[3];
**	void				*zone_addr[3];
*/
typedef struct					s__malloc_instance__
{
	int							is_init;
	t__malloc_options__			options;
	t__malloc_block__			*zone[3];
	void						*zone_addr[3];
}								t__malloc_instance__;

struct							s__malloc_thread_safe__
{
	pthread_mutex_t				global;
	pthread_mutex_t				zone[3];
};

void							init(void);
int								init_zone(int zone);
void							put_addr(void *param);
void							print_memory(void *ptr, size_t size);
void							*new_zone(size_t size);
void							show_alloc_mem(void);
void							show_alloc_mem_ex(void);
void							show_last_alloc_mem(void);
void							show_alloc_mem_zone(int zone);
size_t							get_size_according_to_quantum_zone(
													size_t size, int zone);
int								get_zone(size_t size);

#endif
