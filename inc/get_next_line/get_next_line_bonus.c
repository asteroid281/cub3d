/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:58:05 by apalaz            #+#    #+#             */
/*   Updated: 2024/01/16 15:57:11 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "stdlib.h"
#include "unistd.h"

char	*get_buff(char *str)
{
	char	*rtrn;
	t_ui	i;
	t_ui	j;

	if (!ctrl_nl(str))
		return (free(str), NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	rtrn = (char *) malloc(ft_strlen(str) - i);
	if (!rtrn)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i + j])
	{
		rtrn[j] = str[i + j];
		j++;
	}
	rtrn[j] = 0;
	free(str);
	return (rtrn);
}

char	*get_line_wol(int fd, char *lwol)
{
	char	*buff;
	int		state;

	buff = (char *) malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(lwol), NULL);
	state = 1;
	while (state && !ctrl_nl(lwol))
	{
		state = read(fd, buff, BUFFER_SIZE);
		if (state == -1)
			return (free(buff), free(lwol), NULL);
		if (!state)
			break ;
		buff[state] = 0;
		lwol = ft_strjoin(lwol, buff);
		if (!lwol)
			return (free(buff), free(lwol), NULL);
	}
	free(buff);
	return (lwol);
}

char	*get_line_wout(char *lwol)
{
	char	*rtrn;
	t_ui	i;

	if (!*lwol)
		return (0);
	i = 0;
	while (lwol[i] && lwol[i] != '\n')
		i++;
	rtrn = (char *) malloc(i + 1 + (lwol[i] == '\n'));
	if (!rtrn)
		return (0);
	i = 0;
	while (lwol[i] && lwol[i] != '\n')
	{
		rtrn[i] = lwol[i];
		i++;
	}
	if (lwol[i] == '\n')
	{
		rtrn[i] = '\n';
		i++;
	}
	rtrn[i] = 0;
	return (rtrn);
}

char	*get_next_line(int fd)
{
	static char		*line_with_ol[10000];
	char			*line_wout_ol;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line_with_ol[fd] = get_line_wol(fd, line_with_ol[fd]);
	if (!line_with_ol[fd])
		return (0);
	line_wout_ol = get_line_wout(line_with_ol[fd]);
	line_with_ol[fd] = get_buff(line_with_ol[fd]);
	return (line_wout_ol);
}
