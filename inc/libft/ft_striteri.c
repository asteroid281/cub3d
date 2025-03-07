/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:37:47 by apalaz            #+#    #+#             */
/*   Updated: 2025/01/13 16:06:49 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(t_ui, char *))
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		f((t_ui) i, &s[i]);
		i++;
	}
}
