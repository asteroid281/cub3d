/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:26:58 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:26:58 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_error(const char *error)
{
	ft_putstr_fd("Error : ", 2);
	if (!error)
		return ;
	ft_putendl_fd((char *) error, 2);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = &(t_cube){0};
	if (argc != 2)
	{
		print_error("Argument Number");
		return (EXIT_FAILURE);
	}
	if (parser(argv, cube))
	{
		free_cube(cube);
		return (EXIT_FAILURE);
	}
	if (executer(cube))
	{
		free_cube(cube);
		return (EXIT_FAILURE);
	}
	free_cube(cube);
	return (EXIT_SUCCESS);
}
