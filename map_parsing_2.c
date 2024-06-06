/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:42:34 by aazra             #+#    #+#             */
/*   Updated: 2022/07/28 16:15:53 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	surrounded_by_walls(t_vars *s)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	while (i < s->map.nb_lines + 1)
	{
		j = 1;
		while (j < s->map.line_len + 1)
		{
			if (s->map.map[i][j] == '0')
			{
				if (s->map.map[i - 1][j] != '0' && s->map.map[i - 1][j] != '1')
					error(s, "Error\nMap is not surrounded by walls\n");
				if (s->map.map[i + 1][j] != '0' && s->map.map[i + 1][j] != '1')
					error(s, "Error\nMap is not surrounded by walls\n");
				if (s->map.map[i][j + 1] != '0' && s->map.map[i][j + 1] != '1')
					error(s, "Error\nMap is not surrounded by walls\n");
				if (s->map.map[i][j - 1] != '0' && s->map.map[i][j - 1] != '1')
					error(s, "Error\nMap is not surrounded by walls\n");
			}
			j++;
		}
		i++;
	}
}

void	malloc_struct(t_vars *s)
{
	s->map.map = malloc(sizeof(char *) * (s->map.nb_lines + 2));
	if (!(s->map.map))
		error(s, "Error : problem with malloc\n");
}

int	convert_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}
