/*
 *		ATTENTION!
 *		Les variables globales depndent d'un processus.
 *		Lors d'un fork, celle ci est duplique et n'est plus partagee
 *		meme si c'est un pinteur
 */

#include "malloc.h"

void	*malloc(size_t size)
{
	(void)size;
	return (NULL);
}
