#include "ft_mini_ls.h"

void	ft_swap(void *a, void *b, size_t width)
{
	void	*tmp;

	tmp = malloc(width);
	if (!tmp)
	{
		perror("swap() -> malloc");
		return ;
	}
	ft_memcpy(tmp, a, width);
	ft_memcpy(a, b, width);
	ft_memcpy(b, tmp, width);
	free(tmp);
}

static void	do_qsort(unsigned char *base, size_t left, size_t right, size_t width, int (*compar)(const void *, const void *))
{
	if (left >= right)
		return ;
	size_t p_index = left + (right - left) / 2;
	unsigned char *pivot = base + p_index * width;
	swap(base + p_index * width, base + right * width, width);

	size_t	i = left;
	size_t	j = left;
	while (j < right)
		if (compar(base + j * width, pivot) < 0)
			swap(base + i++ * width, base + j++ * width, width);
	swap(base + i + width, base + right * width, width);
	if (0 < i)
		do_qsort(base, left, i - 1, width, compar);
	do_qsort(base, i + 1, right, compar)
}

void	ft_qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
	if (nel <= 1)
		return ;
	do_qsort((unsigned char *)base, 0, nel - 1, width, compar);
}
