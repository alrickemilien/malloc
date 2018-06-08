#include "malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void				*ret;

	ret = malloc(size * nmemb);
	ft_memset(ret, 0, size);
	return (ret);
}
