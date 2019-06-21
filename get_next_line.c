/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znazam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:01:26 by znazam            #+#    #+#             */
/*   Updated: 2019/06/21 16:22:44 by znazam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	checker(const int fd, char **fd_arr)
{
	char buff[BUFF_SIZE + 1];//buff size is the amount of bytes it counts at a time
	char *tmp;
	int ret;

	while(ft_strchr(fd_arr[fd], '\n') == NULL)//checks for the /n and if it doesn't fnd it it must return 0
	{
		if((ret = read(fd, buff, BUFF_SIZE)) == 0)//reads the folder and adds buffer size to it
			break;// if it reaches 0 which is the end of the file it breaks
		buff[ret] = '\0';// read returns the str alone without a '\0' so i add the '\0'
		tmp = ft_strjoin(fd_arr[fd], buff);//im joining the current buffer with the new one
		ft_strdel(&fd_arr[fd]);//deleting the old buffer because tmp has the new one
		fd_arr[fd] = tmp;//fd_arr becomes the new tmp file
	}
	shift_over;
//	if ((ft_strchr(fd_arr[fd], '\n') != NULL))//strchr searchers for the '\n' and does not find '\0' it executes the bellow
//			{
//				ft_repstr(&fd_arr[fd], '\n', '\0');//replace the '\n' with a '\0'
//				//return a 1
//			}
//	else if (ft_strlen(fd_arr[fd]) != 0)
//		fd_arr[fd] = ft_strdup(fd_arr[fd]);//if the string doesn't have a '\n' it must return the current string
}

void shift_over(char **line)
{
	char *ptr = ft_strchr(str, '\n');//gives a pointer to the '\n'
	int len = ptr - str;//dlts the '\n'
	*line = ft_strsub(str, 0, len);//creates a fresh string with everything before '\n'
	char * tmp = ft_strsub(str, len + 1, /*rest of the string*/);//stores the rest of the str
	free(fd_arr[fd]);//removes the str
	fd_arr[fd] = tmp;//becomes the str of the rest
}

int		get_next_line(const int fd, char **line)
{
	char buff[BUFF_SIZE + 1];// plus 1 is for that null terminator
	char *tmp;
	static char* fd_arr[1024];// the number is the maximum amount of files that can be opened at a time for the bonus section

	if (fd < 0 || read(fd, buff, 0) < 0 || !line)
		return (-1);// error detected
	if(fd_arr[fd] == NULL)
		fd_arr[fd] = ft_strnew(0);// if the string is empty a newstring with zero bytes is Created
	read(fd, buff, 0);// will read the file from 0

	checker(fd, fd_arr);// calls my funtion and looks for the ')\n' to replace with a '\0'
	*line = fd_arr[fd];// to make the new file with the '\0' = to *line that was a '\n'
	if (**line != '\0')
		return(1);// i have read a line
	else
		return (0);// i have over reached the EOF

	//after the checker do a bunch of checks

	//remember that GNL returns an int! -1 for error, 1 for I have read a line, and 0 once you have reached the end of the file.

}

int		main(void)
{
	char *line;
	while (get_next_line(0, &line) > 0)
	{
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
	}
	return (0);
}
