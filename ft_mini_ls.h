/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:02:54 by sishige           #+#    #+#             */
/*   Updated: 2024/08/04 21:21:28 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include "libft.h"
# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdio.h>

typedef struct s_ent_stat
{
	struct dirent	*ent;
	struct stat		stat;
}				t_ent_stat;

void	ft_qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
void	ft_swap(void *a, void *b, size_t width);

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);

#endif
