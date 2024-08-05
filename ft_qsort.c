/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:34:19 by sishige           #+#    #+#             */
/*   Updated: 2024/08/05 19:59:30 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

////#include "ft_mini_ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_swap(void *a, void *b, size_t width)
{
	void	*tmp;

	tmp = malloc(width);
	if (!tmp)
	{
		perror("swap() -> malloc");
		return ;
	}
	memcpy(tmp, a, width);
	memcpy(a, b, width);
	memcpy(b, tmp, width);
	free(tmp);
}

static void	do_qsort(unsigned char *base, size_t left, size_t right,
		size_t width, int (*compar)(const void *, const void *))
{
	size_t			p_index;
	unsigned char	*pivot;
	size_t			i;
	size_t			j;

	if (left >= right)
		return ;
	p_index = left + (right - left) / 2;
	ft_swap(base + p_index * width, base + right * width, width);
	pivot = base + right * width;
	i = left;
	j = left;
	while (j < right)
	{
		if (compar(base + j * width, pivot) < 0)
			ft_swap(base + i++ * width, base + j * width, width);
		j++;
	}
	ft_swap(base + i * width, base + right * width, width);
	if (i > 0)
		do_qsort(base, left, i - 1, width, compar);
	do_qsort(base, i + 1, right, width, compar);
}

void	ft_qsort(void *base, size_t nel, size_t width,
		int (*compar)(const void *, const void *))
{
	if (nel <= 1)
		return ;
	do_qsort((unsigned char *)base, 0, nel - 1, width, compar);
}
