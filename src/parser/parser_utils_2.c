/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:45:31 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/15 18:45:32 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*first_line_check(char ***file_cont, int fd)
{
	char	*line;

	*file_cont = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		print_error("File is empty!");
		return (NULL);
	}
	return (line);
}
