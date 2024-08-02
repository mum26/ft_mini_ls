/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:02:54 by sishige           #+#    #+#             */
/*   Updated: 2024/08/02 18:09:22 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include "libft.h"
# include <time.h>
# include <dirent.h>
# include <sys/stat.h>

# define ASC  1
# define DESC 2

typedef struct s_file_info
{
	struct dirent	*entry;
	struct stat		status;
}				t_file_info;

void	ft_qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *, int));
void	ft_swap(void *a, void *b, size_t width);

#endif
