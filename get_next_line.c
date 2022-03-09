/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:12:22 by magonzal          #+#    #+#             */
/*   Updated: 2022/03/08 18:31:07 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char *ft_read(int fd, char *casitodo)
// {
// 	char	*line;

// 	casitodo = malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	while(!ft_strchr(casitodo,'\n'))
// 	{
// 		read(fd, casitodo, BUFFER_SIZE);
// 		if(!line)
// 			line = ft_strdup(casitodo);
// 		else
// 			line = ft_strjoin(line,casitodo);
// 	}
// 	return(line);
// }

char	*ft_goodline(char *goodline)
{
	char *auxline;
	int i;

	i = 0;
	auxline = malloc(sizeof(char) * ft_strlen(goodline));
	while(goodline[i] != '\n')
	{
		auxline[i] = goodline[i];
		i++;
	}
	auxline[i] = '\n';
	auxline[i+1]= '\0';
	return (auxline);
}

char	*ft_restline(char *line)
{
	int		i;
	int		j;
	char	*lineaux;

	i = 0;
	j = 0;

	lineaux = malloc(sizeof(char) * ft_strlen(line));
	while(line[i] != '\n')
		i++;
	i++;
	while(line[i] != '\0')
	{
		lineaux[j] = line[i];
		j++;
		i++;
	}
	lineaux[i] = '\0';
	//free(lineaux);
	return(lineaux);
}

char	*get_next_line(int fd)
{
	static char	*todo = NULL;
	char		*goodline;
	int r;
	
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1000)
		return(NULL);

	goodline = malloc(sizeof(char) * BUFFER_SIZE + 1);
	r = 1;
	while(!ft_strchr(goodline,'\n') && r >= 0)
	{
		r = read(fd, goodline, BUFFER_SIZE);
		if(r == -1)
		{
			free(goodline);
			return(NULL);
		}
		goodline[r] = '\0';
		if(!todo)
			todo = ft_strdup(goodline);
		else	
			todo = ft_strjoin(todo,goodline);

		//printf("Goodline = %s Todo = %s\n\n",goodline,todo);
	}
	goodline = ft_goodline(todo);
	todo = ft_restline(todo);
	//printf("%s",todo);
	return(goodline);
}

int main()
{
	int		fd;
	char	*str;
	
	fd = open("ejemplo", O_RDONLY);
	//printf("File Descriptor = %d\n",fd);
	str = get_next_line(fd);
	printf("%s",str);
	str = get_next_line(fd);
	printf("%s",str);
	str = get_next_line(fd);
	printf("%s",str);
	close(fd);
	return (0);
}
