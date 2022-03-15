/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:12:22 by magonzal          #+#    #+#             */
/*   Updated: 2022/03/14 12:21:03 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_goodline(char *gline)
{
	char	*aux;
	int		i;

	i = 0;
	if (!gline)
		return (NULL);
	aux = malloc(sizeof(char) * ft_strlen(gline)+1);
	if (!aux)
		return (NULL);
	while (gline[i] != '\n' && gline[i])
	{
		aux[i] = gline[i];
		i++;
	}
	if (gline[i] == '\n')
		aux[i++] = '\n';
	aux[i] = '\0';
	return (aux);
}

int	aux(char *line, char *lineaux, int i)
{
	int	j;

	j = 0;
	while (line[i] != '\0')
	{
		lineaux[j] = line[i];
		j++;
		i++;
	}
	return (j);
}

char	*ft_restline(char *line)
{
	int		i;
	int		j;
	char	*lineaux;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	if (!line[ft_strline(line)])
	{
		free(line);
		return (NULL);
	}
	lineaux = malloc(sizeof(char) * (ft_strlen(line) - ft_strline(line)) + 1);
	if (!lineaux)
		return (NULL);
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	lineaux[aux(line, lineaux, i)] = '\0';
	free(line);
	return (lineaux);
}

char	*ft_read(int fd, char *goodline, char *todo)
{
	int	r;

	while (!ft_strchr(todo, '\n'))
	{
		r = read(fd, goodline, BUFFER_SIZE);
		goodline[r] = '\0';
		if (r == -1)
		{
			free(goodline);
			return (NULL);
		}
		else if (r == 0)
		{
			free(goodline);
			return (todo);
		}
		if (!todo)
			todo = ft_strdup(goodline);
		else
			todo = ft_strjoin(todo, goodline);
	}
	free(goodline);
	return (todo);
}

char	*get_next_line(int fd)
{
	static char	*todo = NULL;
	char		*goodline;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1000)
		return (NULL);
	goodline = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!goodline)
		return (NULL);
	todo = ft_read(fd, goodline, todo);
	goodline = ft_goodline(todo);
	todo = ft_restline(todo);
	return (goodline);
}
