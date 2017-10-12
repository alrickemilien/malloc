/*
 *		ATTENTION!
 *		Les variables globales depndent d'un processus.
 *		Lors d'un fork, celle ci est duplique et n'est plus partagee
 *		meme si c'est un pinteur
 */

#include "malloc.h"

void	*malloc(size_t size)
{
	extern char **environ;
	extern struct s__malloc_instance__ g__malloc_instance__;
	int		i;
	(void)size;

	init();
	i = 0;
	while (environ[i])
	{
		write(1, environ[i], ft_strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	ft_putnbr(g__malloc_instance__.options.tiny_zone_size);
	return (NULL);
}
