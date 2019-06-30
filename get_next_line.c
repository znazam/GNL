/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znazam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:01:26 by znazam            #+#    #+#             */
/*   Updated: 2019/06/30 09:26:30 by znazam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	checker(const int fd, char **fd_arr)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	while (ft_strchr(fd_arr[fd], '\n') == NULL)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) == 0)
			break ;
		buff[ret] = '\0';
		if (!(tmp = ft_strjoin(fd_arr[fd], buff)))
			return (ret);
		free(fd_arr[fd]);
		fd_arr[fd] = tmp;
	}
	return (ret);
}

static void	shift_over(char **fd_arr, char **line)
{
	int		after;
	char	*ptr;
	int		len;
	char	*tmp;

	if (!(ptr = ft_strchr(*fd_arr, '\n')))
		ptr = ft_strchr(*fd_arr, '\0');
	len = ptr - *fd_arr;
	*line = ft_strsub(*fd_arr, 0, len);
	after = ft_strlen(*(fd_arr) + len + 1);
	if (!(*ptr))
		tmp = ft_strnew(0);
	else
		tmp = ft_strsub(*(fd_arr) + len + 1, 0, after);
	free(*fd_arr);
	*fd_arr = tmp;
}

int			get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static char		*fd_arr[1024];
	int				ret;

	if (fd < 0 || read(fd, buff, 0) < 0 || !line)
		return (-1);
	if (fd_arr[fd] == NULL && !(fd_arr[fd] = ft_strnew(0)))
		return (-1);
	ret = checker(fd, fd_arr);
	if (ret < BUFF_SIZE && !ft_strlen(fd_arr[fd]))
		return (0);
	if (fd_arr[fd])
	{
		shift_over(&fd_arr[fd], line);
		return (1);
	}
	else
		return (-1);
}
