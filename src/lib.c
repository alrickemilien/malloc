#include "malloc.h"

struct s__malloc_instance__			g__malloc_instance__;
struct s__malloc_thread_safe__		g__malloc_thread_safe__;
/*
 *								G_MALLOC
 */


/*
   int		getrlimit(int resource, struct rlimit *rlp);

   struct	rlimit {
   rlim_t  rlim_cur;        current (soft) limit 
   rlim_t  rlim_max;        hard limit 
   };

   The getrlimit() and setrlimit() system calls will fail if:

   [EFAULT]           The address specified for rlp is invalid.

   [EINVAL]           resource is invalid.

   The setrlimit() call will fail if:

   [EINVAL]           The specified limit is invalid (e.g., RLIM_INFINITY or lower than rlim_cur).

   [EPERM]            The limit specified would have raised the maximum limit value and the caller is not
   the super-user.

*/

void	*new_zone(size_t size)
{
	t__malloc_block__	*ptr;

	ptr = mmap(0,
			size + sizeof(t__malloc_block__),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE,
			-1, 0);
	ptr->size = size;
	ptr->is_free = 1;
	return ((void*)ptr);	
}

void	init()
{
	int		page_size;

	page_size = getpagesize();
	ft_bzero(&g__malloc_instance__, sizeof(g__malloc_instance__));
	g__malloc_instance__.options.absolute_max_size = SIZE_MAX - (2 * page_size);
	g__malloc_instance__.options.tiny_zone_size = page_size;
	g__malloc_instance__.options.small_zone_size = page_size;
	while (g__malloc_instance__.options.tiny_zone_size < __MALLOC_TINY_ZONE_SIZE__)
		g__malloc_instance__.options.tiny_zone_size += page_size;
	while (g__malloc_instance__.options.small_zone_size < __MALLOC_SMALL_ZONE_SIZE__)
		g__malloc_instance__.options.small_zone_size += page_size;
}
