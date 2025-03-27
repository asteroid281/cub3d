/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:30:26 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:30:47 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "fcntl.h"
#include "stdbool.h"

char	is_dir(char *argv)
{
	int	fd;

	fd = open(argv, __O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (true);
	}
	return (false);
}

static char	is_cub(char *argv)
{
	int	len1;
	int	len2;

	len1 = ft_strlen2(argv);
	len2 = ft_strlen(argv);
	if (len1 > 4 && argv[len2 - 4] == '.' && argv[len2 - 3] == 'c' \
	&& argv[len2 - 2] == 'u' && argv[len2 - 1] == 'b')
		return (true);
	return (false);
}

int	file_check(char *argv)
{
	int	fd;

	if (is_dir(argv))
		return (print_error("Not directory"), -1);
	if (!is_cub(argv))
		return (print_error("File is not cub file."), -1);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (print_error("File could not be opened."), -1);
	return (fd);
}
