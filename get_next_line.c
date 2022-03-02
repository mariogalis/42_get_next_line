/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:12:22 by magonzal          #+#    #+#             */
/*   Updated: 2022/03/02 15:31:14 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read(int fd, char *todo)
{
	char	*line;
	int		n;
	
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while(!ft_strchr(todo, '\n'))
	{
		n = read(fd, line, BUFFER_SIZE);	//TODO: si hay error read devuelve -1
		// if (n == 0 || n == -1)
		// {
		// 	free(line);
		// 	return (todo);
		// }
		line[BUFFER_SIZE] = 0;
		if(!todo)
			todo = ft_strdup(line);
		else
			todo = ft_strjoin(todo, line);
	}
	free(line);
	return(todo);
}

char	*ft_goodline(char *todo)
{
	char	*auxline;
	int		i;

	i = 0;
	while(todo[i] != '\n')
	{
		auxline[i] = todo[i];
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
	//printf("line = %s",line);
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
	static char	*todo = NULL;
	char		*goodline;
	
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1000)
		return(NULL);
	//check
	todo = ft_read(fd, todo);
	//printf("TODO == %s \n",todo);
	goodline = ft_goodline(todo);
	//printf("GOODLINE ==  = %s\n", goodline);
	//todo = ft_restline(todo);
	//printf("EL RESTO = %s",todo);
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
