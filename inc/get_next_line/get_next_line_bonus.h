/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:58:03 by apalaz            #+#    #+#             */
/*   Updated: 2024/01/15 17:03:17 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

typedef unsigned int	t_ui;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

char	*get_next_line(int fd);
char	*get_line_wout(char *lwol);
char	*get_line_wol(int fd, char *lwol);
char	*get_buff(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	ctrl_nl(char *str);
t_ui	ft_strlen(char *str);

#endif
