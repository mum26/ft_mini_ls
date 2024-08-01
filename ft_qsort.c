#include "ft_mini_ls.h"

static void	do_qsort(unsigned char *base, size_t left, size_t right, size_t width, int (*compar)(const void *, const void *))
{
	if (left >= right)
		return ;
	size_t 
}

void	ft_qsort(void *base, size_t nel, size_t width, int (*compar)(const *void)(const *void))
{
	if (nel <= 1)
		return ;
	do_qsort((unsigned char *)base, 0, nel - 1, width, compar);
}
