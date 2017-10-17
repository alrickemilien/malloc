/*
 *		ATTENTION!
 *		Les variables globales depndent d'un processus.
 *		Lors d'un fork, celle ci est duplique et n'est plus partagee
 *		meme si c'est un pinteur
 */

#include "malloc.h"

void	new_block(size_t size)
{
	mmap(0, 
		size + sizeof(t__malloc_block__),
		PROT_RED | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE);
}

void	*malloc(size_t size)
{
	extern char **environ;
	extern struct s__malloc_instance__ g__malloc_instance__;
	(void)size;

	init();
	ft_putnbr(g__malloc_instance__.options.tiny_zone_size );
	write(1, "\n", 1);
	ft_putnbr(g__malloc_instance__.options.tiny_zone_size - sizeof(t__malloc_block__));

	return (NULL);
}
