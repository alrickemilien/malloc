#ifndef MALLOC_H
# define MALLOC_H

# include "../../libft/libft.h"
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdio.h>
# define G_MALLOC					g__malloc_instance__

/*
		CHQUE ZONE DOIT CONTENIR AU MOINS 100 ALLOCATIONS
*/

# define __MALLOC_TINY_LIMIT__		992
# define __MALLOC_SMALL_LIMIT__		127000
# define __MALLOC_LARGE_LIMIT__		10000000000

# define __MALLOC_TINY_QUANTUM__	16
# define __MALLOC_SMALL_QUANTUM__	512
# define __MALLOC_LARGE_QUANTUM__	4000

/*
 *		Gonna * getpagesize()
 */

# define __MALLOC_TINY_ZONE_SIZE__	1000000
# define __MALLOC_SMALL_ZONE_SIZE__	16000000

typedef struct	s__malloc_options__
{
	int			tiny_zone_size;
	int			small_zone_size;
}				t__malloc_options__;

struct	s__malloc_instance__
{
		t__malloc_options__		options;
};

struct	s__malloc_thread_safe__
{
	int		o;
};

void	init(void);

#endif
