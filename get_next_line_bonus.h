/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:26:26 by muhademi          #+#    #+#             */
/*   Updated: 2023/12/07 15:11:02 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strchr(char *str, int c);
int		ft_strlen(char *s);
void	str_part_cpy(char *s1, char *s2, int srci, int len);
char	*join(char *s1, char *s2);
char	*get_line_from_buffer(char *buffer);
char	*get_next_line(int fd);
char	*clean_buffer(char *buffer);

#endif
