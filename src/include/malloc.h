#ifndef MALLOC_H
# define MALLOC_H

# include "../../libft/libft.h"
# define G_MALLOC					g__malloc_instance__

# define __MALLOC_TINY__			1
# define __MALLOC_SMALL__			100
# define __MALLOC_LARGE__			500

/*
 *		Gonna * getpagesize()
 */
# define __MALLOC_TINY_ZONE_SIZE__	5
# define __MALLOC_SMALL_ZONE_SIZE__	10

struct	s__malloc_instance__
{
	int		tiny_zone_size;
	int		small_zone_size;
	int		n;
	int		m;
};

#endif
