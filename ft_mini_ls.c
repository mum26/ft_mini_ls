/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:45:21 by sishige           #+#    #+#             */
/*   Updated: 2024/08/05 00:00:57 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

#include <stdio.h>
#include <libc.h>

__attribute__((destructor)) static void destructor(void)
{
	system("leaks -q ft_mini_ls");
}

void reverse_array(void *array, size_t element_count, size_t element_size) {
    // バッファ用に一時的なメモリを確保
    void *temp = malloc(element_size);
    if (temp == NULL) {
        perror("malloc");
        return;
    }

    // 配列の反転
    for (size_t i = 0; i < element_count / 2; ++i) {
        void *start = (char *)array + i * element_size;
        void *end = (char *)array + (element_count - i - 1) * element_size;

        // startとendの内容を交換
        memcpy(temp, start, element_size);
        memcpy(start, end, element_size);
        memcpy(end, temp, element_size);
    }

    // 一時メモリを解放
    free(temp);
}

// Always in descending order.
int	compare_dir_update_time_with_name(const void *a, const void *b)
{
	time_t	a_update_time;
	time_t	b_update_time;
	char	*a_d_name;
	char	*b_d_name;

	a_update_time = ((t_ent_stat *)a)->stat.st_mtimespec.tv_sec;
	b_update_time = ((t_ent_stat *)b)->stat.st_mtimespec.tv_sec;
	if (a_update_time < b_update_time)
		return (1);
	if (b_update_time < a_update_time)
		return (-1);
	a_d_name = ((t_ent_stat *)a)->ent->d_name;
	b_d_name = ((t_ent_stat *)b)->ent->d_name;
	return (strcmp(a_d_name, b_d_name));
}

int	compare_d_name(const void *a, const void *b)
{
	char	*a_d_name;
	char	*b_d_name;

	a_d_name = ((t_ent_stat *)a)->ent->d_name;
	b_d_name = ((t_ent_stat *)b)->ent->d_name;
	return (strcmp(a_d_name, b_d_name));
}

static int	get_dirent_stat(t_ent_stat *ent_stat_p, int ent_stat_count) 
{
	int	i;

	if (!ent_stat_p || ent_stat_count < 1)
		return (perror("get_dirent_stat()"), -1);
	i = 0;
	while (i < ent_stat_count)
	{
		if (ent_stat_p[i].ent->d_type != DT_LNK)
		{
			if (lstat(ent_stat_p[i].ent->d_name, &ent_stat_p[i].stat) == -1)
				return (perror("get_dirent() -> lstat()"), -1);
		}
		else
		{
			if (stat(ent_stat_p[i].ent->d_name, &ent_stat_p[i].stat) == -1)
				return (perror("get_dirent() -> stat()"), -1);
		}
		i++;
	}
	return (i);
}

static int	get_dirent(t_ent_stat **ent_stat_p, DIR *dp)
{
	int	ent_stat_size;
	int	i;

	if (!ent_stat_p)
		return (perror("get_dirent()"),-1);
	ent_stat_size = 16;
	*ent_stat_p = (t_ent_stat *)ft_calloc(ent_stat_size, sizeof(t_ent_stat));
	if (!*ent_stat_p)
		return (perror("get_dirend -> ft_calloc()"), -1);
	i = 0;
	while (true)
	{
		if (ent_stat_size <= i)
		{
			*ent_stat_p = (t_ent_stat *)ft_realloc(ent_stat_p, sizeof(t_ent_stat) * ent_stat_size * 2 ,
					sizeof(t_ent_stat) * ent_stat_size);
			if (!ent_stat_p)
				return (free(*ent_stat_p), perror("get_dirent() -> ft_realloc()"), -1);
			ent_stat_size *= 2;
		}
		(*ent_stat_p)[i].ent = readdir(dp);
		if (!(*ent_stat_p)[i].ent)
			break ;
		i++;
	}
	return (i);
}

int	main(int argc, char *argv[])
{
	DIR			*dp;
	t_ent_stat	*ent_stat_p;
	int			ent_stat_count;
	int			i;

	if (1 < argc)
		return (fprintf(stderr, "%s: 引数は受けつけてません。\n", argv[0]), -1);
	dp = opendir(".");
	ent_stat_count = get_dirent(&ent_stat_p, dp);
	if (ent_stat_count < 0)
		return (perror("main -> get_dirent()"), -1);
	ft_qsort(ent_stat_p, ent_stat_count, sizeof(t_ent_stat), &compare_d_name);
	if (get_dirent_stat(ent_stat_p, ent_stat_count) < 0)
		return (perror("main -> get_dirent_stat()"), -1);
	reverse_array(ent_stat_p, ent_stat_count, sizeof(t_ent_stat));
	i = 0;
	while (i < ent_stat_count)
	{
		if (ent_stat_p[i].ent->d_name[0] != '.')
			printf("%s\n", ent_stat_p[i].ent->d_name);
		i++;
	}
	free(ent_stat_p);
	if (closedir(dp))
		return (perror("main() -> closedir()"), -1);
	return (0);
}
