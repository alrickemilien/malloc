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

void	init()
{
	int		page_size;

	page_size = getpagesize();
	g__malloc_instance__.options.tiny_zone_size = page_size;
	g__malloc_instance__.options.small_zone_size = page_size;
	while (g__malloc_instance__.options.tiny_zone_size < __MALLOC_TINY_ZONE_SIZE__)
		g__malloc_instance__.options.tiny_zone_size += page_size;
	while (g__malloc_instance__.options.small_zone_size < __MALLOC_SMALL_ZONE_SIZE__)
		g__malloc_instance__.options.small_zone_size += page_size;
		
}
