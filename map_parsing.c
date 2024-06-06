/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:42:49 by aazra             #+#    #+#             */
/*   Updated: 2022/07/27 12:08:55 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	start_position(t_vars *s, char c, int i, int j)
{
	if (c == 'N')
		s->p.pa = 3 * PI / 2;
	if (c == 'S')
		s->p.pa = PI / 2;
	if (c == 'E')
		s->p.pa = 0;
	if (c == 'W')
		s->p.pa = PI;
	s->p.pdx = cos(s->p.pa);
	s->p.pdy = sin(s->p.pa);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		s->map.start++;
		s->p.px = (j + 1) * 64 + 32;
		s->p.py = (i + 1) * 64 - 32;
		return (1);
	}
	return (0);
}

void	get_map_2(t_vars *s, int i, int j)
{
	j++;
	while (j < s->map.line_len + 2)
	{
		s->map.map[i][j] = ' ';
		j++;
	}
	s->map.map[i][j] = '\0';
}

void	get_map(t_vars *s, char *line)
{
	static int	i = 1;
	int			j;
	char		**str;

	j = 0;
	str = ft_split(line, ' ');
	if (!str)
		error(s, "Error\nProblem with malloc\n");
	if (str[0] != NULL && str[0][0] == '1')
	{
		s->map.map[i] = malloc(sizeof(char) * (s->map.line_len + 3));
		if (!(s->map.map[i]))
			error(s, "Error : problem with malloc\n");
		while (line[j] != '\0')
		{
			if (start_position(s, line[j], i, j) == 1)
				s->map.map[i][j + 1] = '0';
			else
				s->map.map[i][j + 1] = line[j];
			j++;
		}
		get_map_2(s, i, j);
		i++;
	}
	free_split(str);
}

void	parsing_map(t_vars *s, char *map)
{
	char	*line;
	int		fd;
	int		gnl;

	line = NULL;
	gnl = 1;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		error(s, "Error : map did not open\n");
	malloc_struct(s);
	while (gnl != 0)
	{
		gnl = get_next_line(fd, &line);
		if (gnl == -1)
			error(s, "Error : problem with gnl\n");
		if (gnl == 1)
			get_map(s, line);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	finish_map(s);
	close(fd);
}

int	map_validity(t_vars *s, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[i] != '\0')
	{
		while (line[i] != '\0')
		{
			if (line[i] != '0' && line[i] != '1' && line[i] != 'N' \
			&& line[i] != 'S' && line[i] != 'E' \
			&& line[i] != 'W' && line[i] != ' ')
				s->map.wrong_char = -1;
			i++;
		}
		return (1);
	}
	return (0);
}
