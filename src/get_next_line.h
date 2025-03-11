/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:45:34 by apalaz            #+#    #+#             */
/*   Updated: 2024/01/12 19:27:08 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef unsigned int	t_ui;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

char	*get_next_line(int fd);
char	*get_line_wout(char *lwol);
char	*get_line_wol(int fd, char *lwol);
char	*get_buff(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	ctrl_nl(char *str);
t_ui	ft_strlen_gnl(char *str);

#endif
