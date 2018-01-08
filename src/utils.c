#include "malloc.h"

struct s__malloc_instance__			g__malloc_instance__ = {0, { { 0, 0 }, {0,0,0,0,0,0,0,0,0}, 0 }, { 0, 0, 0 }, { 0, 0, 0 }};
struct s__malloc_thread_safe__		g__malloc_thread_safe__ = {
	PTHREAD_MUTEX_INITIALIZER,
	{
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER
	}
};


/*
 *						G_MALLOC
 */

/*							THRED SAFE FUNCTIONS
 *							http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
 *
 *					pthread_self()
 *
 *
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

   [EINVAL] The spec limit is invalid
   (e.g., RLIM_INFINITY or lower than rlim_cur).

   [EPERM] The limit spec would have raised the maximum limit value
   and the caller is not
   the super-user.
   */

void	*new_zone(size_t size)
{
	t__malloc_block__	*ptr;

	if ((ptr = mmap(0,
			size + sizeof(t__malloc_block__),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE,
			-1, 0)) == MAP_FAILED)
		return (NULL);
	ptr->size = size;
	ptr->is_free = 1;
	return ((void*)ptr);
}

void				init_malloc_env()
{
		extern char		**environ;
		char			*malloc_env_vars[9];
		int				i;
		int				j;

		malloc_env_vars[MallocStackLogging] = "MallocStackLogging";
		malloc_env_vars[MallocStackLoggingNoCompact] = "MallocStackLoggingNoCompact";
		malloc_env_vars[MallocScribble] = "MallocScribble";
		malloc_env_vars[MallocPreScribble] = "MallocPreScribble";
		malloc_env_vars[MallocGuardEdges] = "MallocGuardEdges";
		malloc_env_vars[MallocDoNotProtectPrelude] = "MallocDoNotProtectPrelude";
		malloc_env_vars[MallocDoNotProtectPostlude] = "MallocDoNotProtectPostlude";
		malloc_env_vars[MallocCheckHeapStart] = "MallocCheckHeapStart";
		malloc_env_vars[MallocCheckHeapEach] = "MallocCheckHeapEach";
		j = 0;
		while (environ[j])
		{
			i = 0;
			while (malloc_env_vars[i])
			{
				if (ft_strstr(environ[j], malloc_env_vars[i]) == environ[j])
					g__malloc_instance__.options.malloc_env_vars[i] = 1;
				i++;
			}
			j++;
		}
}

void				init(void)
{
	int		page_size;

	LOCK( &g__malloc_thread_safe__.global );

	init_malloc_env();
	page_size = getpagesize();
	g__malloc_instance__.options.absolute_max_size = SIZE_MAX - (2 * page_size);
	g__malloc_instance__.options.zone_size[__MALLOC_TINY__] = page_size;
	g__malloc_instance__.options.zone_size[__MALLOC_SMALL__] = page_size;
	while (g__malloc_instance__.options.zone_size[__MALLOC_TINY__]
			< __MALLOC_TINY_ZONE_SIZE__)
		g__malloc_instance__.options.zone_size[__MALLOC_TINY__] += page_size;
	while (g__malloc_instance__.options.zone_size[__MALLOC_SMALL__]
			< __MALLOC_SMALL_ZONE_SIZE__)
		g__malloc_instance__.options.zone_size[__MALLOC_SMALL__] += page_size;
	g__malloc_instance__.is_init = 1;

	UNLOCK( &g__malloc_thread_safe__.global );
}

int		init_zone(int macro)
{
	if (macro == __MALLOC_LARGE__)
		return (1);
	LOCK( &g__malloc_thread_safe__.zone[macro] );

	if (!(g__malloc_instance__.zone[macro] = new_zone(g__malloc_instance__.options.zone_size[macro])))
	{
		UNLOCK( &g__malloc_thread_safe__.zone[macro] );
		return (0);
	}
	g__malloc_instance__.zone[macro]->is_free = 1;
	g__malloc_instance__.zone[macro]->size = g__malloc_instance__.options.zone_size[macro];
	g__malloc_instance__.zone_addr[macro] = g__malloc_instance__.zone[macro];

	UNLOCK( &g__malloc_thread_safe__.zone[macro] );
	return (1);
}