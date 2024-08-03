/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:45:21 by sishige           #+#    #+#             */
/*   Updated: 2024/08/02 18:09:45 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

#include <stdio.h>
#include <libc.h>

__attribute__((destructor)) static void destructor(void)
{
	system("leaks -q ft_mini_ls");
}

//int	compare_dir_update_time(const void *a, const void *b, int order)
//{
//	long a_time;
//	long b_time;
//
//	a_time = ((t_file_info *)a)->status.st_mtimespec.tv_sec;
//	b_time = ((t_file_info *)b)->status.st_mtimespec.tv_sec;
//	if (order == ASC)
//	{
//		if (a_time < b_time)
//			return (-1);
//		if (b_time < a_time)
//			return (1);
//		return (0);
//	}
//	if (order == DESC)
//	{
//		if (a_time < b_time)
//			return (1);
//		if (b_time < a_time)
//			return (-1);
//		return (0);
//	}
//	perror("compare_dir_update_time() -> Invalid order.");
//	return(0);
//}
//
//static int	do_ls(char *path)
//{
//	DIR			*dp;
//	t_file_info	*fip;
//	size_t		fip_size;
//	int			is_error;
//
//	dp = opendir(path);
//	if (!dp)
//		return (-1);
//	fip_size = 16;
//	fip = (t_file_info *)ft_calloc(fip_size, sizeof(t_file_info));
//	size_t	i = 0;
//	while (i < fip_size)
//	{
//		fip[i].entry = readdir(dp);
//		if (!fip[i].entry)
//			break ;
//		if (fip[i].entry->d_type == DT_LNK)
//			is_error = lstat(fip[i].entry->d_name, &fip[i].status);
//		else
//			is_error = stat(fip[i].entry->d_name, &fip[i].status);
//		if (is_error == -1)
//			break ;
//		i++;
//	}
//	if (is_error == -1)
//		return(free(fip), closedir(dp));
//	ft_qsort(fip, fip_size, sizeof(t_file_info), &compare_dir_update_time);
//	i = 0;
//	while(i < fip_size)
//	{
//		if (!fip[i].entry)
//			break ;
//		printf("%15s\t%zd\n", fip[i].entry->d_name, fip[i].status.st_mtimespec.tv_sec);
//		i++;
//	}
//	return (free(fip), closedir(dp));
//}
//
//int	main(int argc, char *argv[])
//{
//	int	i;
//
//	if (argc < 2)
//		return (fprintf(stderr, "%s: no arguments\n", argv[0]), -1);
//	i = 1;
//	do_ls(argv[i]);
//	return (0);
//}

int	compare_dir_update_time(const void *a, const void *b, int order)
{
	time_t a_update_time;
	time_t b_update_time;

	a_update_time = ((t_file_info *)a)->status.st_mtimespec.tv_sec;
	b_update_time = ((t_file_info *)b)->status.st_mtimespec.tv_sec;
	if (order == ASC)
	{
		if (a_update_time < b_update_time)
			return (-1);
		if (b_update_time < a_update_time)
			return (1);
		return (0);
	}
	if (order == DESC)
	{
		if (a_update_time < b_update_time)
			return (1);
		if (b_update_time < a_update_time)
			return (-1);
		return (0);
	}
	perror("compare_dir_update_time() -> Invalid order.");
	return(0);
}

static int	do_ls(char *path)
{
	DIR			*dir_p;
	t_file_info	*file_info_p;
	size_t		file_info_array_size;
	int			is_error;

	dp = opendir(path);
	if (!dp)
		return (-1);
	fip_size = 16;
	fip = (t_file_info *)calloc(fip_size, sizeof(t_file_info));
	if (!fip)
		return (closedir(dp), -1);
	size_t	i = 0;
	while (1)
	{
		if (i >= fip_size)
		{
			fip_size *= 2;
			t_file_info *tmp = realloc(fip, fip_size * sizeof(t_file_info));
			if (!tmp)
				return (free(fip), closedir(dp), -1);
			fip = tmp;
		}
		fip[i].entry = readdir(dp);
		if (!fip[i].entry)
			break ;
		if (fip[i].entry->d_type == DT_LNK)
			is_error = lstat(fip[i].entry->d_name, &fip[i].status);
		else
			is_error = stat(fip[i].entry->d_name, &fip[i].status);
		if (is_error == -1)
			return (free(fip), closedir(dp), -1);
		i++;
	}
	size_t num_files = i;
	ft_qsort(fip, num_files, sizeof(t_file_info), &compare_dir_update_time);
	for (i = 0; i < num_files; i++)
	{
		if (fip[i].entry->d_name[0] != '.')
			printf("%s\n", fip[i].entry->d_name);
	}
	return (free(fip), closedir(dp), 0);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (fprintf(stderr, "%s: no arguments\n", argv[0]), -1);
	do_ls(argv[1]);
	return (0);
}
