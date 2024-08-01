/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:45:21 by sishige           #+#    #+#             */
/*   Updated: 2024/08/02 00:48:25 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

#include <stdio.h>
#include <libc.h>

__attribute__((destructor)) static void destructor(void)
{
	system("leaks -q ft_mini_ls");
}

static int	do_ls(char *path)
{
	DIR *dp;
	t_finfo	finfo[10];
	size_t	i;
	int		is_error;

	dp = opendir(path);
	if (!dp)
		return (-1);
	i = 0;
	while (i < 10)
	{
		finfo[i].entry = readdir(dp);
		if (!finfo[i].entry)
			break ;
		if (finfo[i].entry->d_type == DT_LNK)
			is_error = lstat(finfo[i].entry->d_name, &finfo[i].status);
		else
			is_error = stat(finfo[i].entry->d_name, &finfo[i].status);
		if (is_error == -1)
			break ;
		i++;
//		if (*entry->d_name != '.')
//		printf("%s\n", entry->d_name);
	}
	return (closedir(dp));
}

int	main(int argc, char *argv[])
{
	int	i;
	struct stat statbuf;

	if (argc < 2)
		return (fprintf(stderr, "%s: no arguments\n", argv[0]), -1);
	i = 1;
	do_ls(argv[i]);
	stat("Go", &statbuf);
	printf("Go last update time:  %zd\n", statbuf.st_mtimespec.tv_sec);
	return (0);
}
