/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:43:22 by aazra             #+#    #+#             */
/*   Updated: 2022/07/28 15:50:42 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	finish_map_2(t_vars *s)
{
	s->map.map[0] = malloc(sizeof(char) * (s->map.line_len + 3));
	if (!s->map.map[0])
		error(s, "Error\nProblem with malloc\n");
	s->map.map[s->map.nb_lines + 1] = malloc(sizeof(char) * \
		(s->map.line_len + 3));
	if (!s->map.map[s->map.nb_lines + 1])
		error(s, "Error\nProblem with malloc\n");
	s->map.max = max(s->map.nb_lines, s->map.line_len);
}

void	finish_map(t_vars *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	finish_map_2(s);
	while (j < (s->map.line_len + 2))
	{
		s->map.map[0][j] = ' ';
		j++;
	}
	s->map.map[0][j] = '\0';
	while (i < (s->map.nb_lines + 2))
	{
		s->map.map[i][0] = ' ';
		i++;
	}
	j = 0;
	while (j < (s->map.line_len + 2))
	{
		s->map.map[s->map.nb_lines + 1][j] = ' ';
		j++;
	}
	s->map.map[s->map.nb_lines + 1][j] = '\0';
}

int	map_fd(t_vars *s, char *map)
{
	int	fd;

	fd = open(map, O_DIRECTORY);
	if (fd != -1)
		error(s, "Error : argument is a directory\n");
	fd = open(map, O_RDONLY);
	if (fd == -1)
		error(s, "Error : file did not open\n");
	return (fd);
}

void	parsing(t_vars *s, char *map)
{
	int		fd;
	int		gnl;
	char	*line;

	line = NULL;
	gnl = 1;
	fd = map_fd(s, map);
	while (gnl != 0)
	{
		gnl = get_next_line(fd, &line);
		if (gnl == -1)
			error(s, "Error : problem with gnl\n");
		if (gnl == 1)
			map_verification(s, line);
		free(line);
	}
	close(fd);
	checkerreur(s);
	map_error(s);
	parsing_map(s, map);
	surrounded_by_walls(s);
	if (s->map.start > 1)
		error(s, "Error\nToo many starting position\n");
	if (s->map.start == 0)
		error(s, "Error\nNo starting position\n");
}

void	check_file(t_vars *s, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '\0')
		error(s, "Error : wrong file\n");
	else
	{
		if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b' \
		&& str[i + 4] == '\0')
			parsing(s, str);
		else
			error(s, "Error : wrong file extension\n");
	}
}
