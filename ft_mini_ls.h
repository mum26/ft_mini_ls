/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:02:54 by sishige           #+#    #+#             */
/*   Updated: 2024/08/02 00:38:38 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include "libft.h"
# include <time.h>
# include <dirent.h>
# include <sys/stat.h>

typedef struct s_file_info
{
	struct dirent	*entry;
	struct stat		status;
}				t_file_info;

#endif
