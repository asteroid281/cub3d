/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:28:01 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/09 15:29:17 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	ft_strlen2(char *s)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i])
	{
		len++;
		if (s[i] == '/')
			len = 0;
		i++;
	}
	return (len);
}

int	str_arr_len(char **str_arr)
{
	int	i;

	if (!str_arr)
		return (0);
	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

static char	**str_arr_r_negative(char *element)
{
	char	**rtrn;

	rtrn = ft_calloc(sizeof(char *), 2);
	if (!rtrn)
		return (NULL);
	rtrn[0] = ft_strdup(element);
	return (rtrn);
}

char	**str_arr_realloc(char **str_arr, char *element)
{
	char	**rtrn;
	int		i;

	if (!str_arr)
		return (str_arr_r_negative(element));
	rtrn = ft_calloc(sizeof(char *), str_arr_len(str_arr) + 2);
	if (!rtrn)
		return (NULL);
	i = -1;
	while (str_arr[++i])
	{
		rtrn[i] = ft_strdup(str_arr[i]);
		if (!rtrn[i])
		{
			free_str_arr(rtrn);
			return (NULL);
		}
	}
	rtrn[i] = ft_strdup(element);
	free_str_arr(str_arr);
	return (rtrn);
}
