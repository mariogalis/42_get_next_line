/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:12:22 by magonzal          #+#    #+#             */
/*   Updated: 2022/02/28 19:43:59 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read(int fd, char *casitodo)
{
	char	*line;

	casitodo = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while(!ft_strchr(casitodo,'\n'))
	{
		read(fd, casitodo, BUFFER_SIZE);
		if(!line)
			line = ft_strdup(casitodo);
		else
			line = ft_strjoin(line,casitodo);
	}
	return(line);
}

char	*ft_goodline(char *goodline)
{
	char *auxline;
	int i;

	i = 0;
	//saber la long de line para malloc
	//quitar mierda despues del \n y copiar hasta /n
	
	while(goodline[i] != '\n')
	{
		auxline[i] = goodline[i];
		i++;
	}
	return (auxline);
}

char	*ft_restline(char *line)
{
	int		i;
	int		j;
	char	*lineaux;

	i = 0;
	j = 0;
	while(line[i] != '\n')
		i++;
	i++;
	while(line[i] != '\0')
	{
		lineaux[j] = line[i];
		j++;
		i++;
	}
	return(lineaux);
}

char	*get_next_line(int fd)
{
	static char	*todo;
	char		*goodline;
	
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1000)
		return(NULL);
	todo = ft_read(fd, todo);
	goodline = ft_goodline(todo);
	//todo = ft_restline(todo);
	return(goodline);
}

int main()
{
	int		fd;
	char	*str;
	
	fd = open("fichero", O_RDONLY);
	//printf("File Descriptor = %d\n",fd);
	str = get_next_line(fd);
	printf("%s\n", str);
	
	close(fd);
	return (0);
}
