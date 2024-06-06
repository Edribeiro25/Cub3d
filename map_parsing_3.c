/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:22:02 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 16:04:19 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_verification_4(t_vars *s, char *line, int i)
{
	if (map_validity(s, line) == 1)
	{
		i = ft_strlen(line);
		if (i > s->map.line_len)
			s->map.line_len = i;
		s->map.nb_lines++;
	}	
}

void	map_verification_3(t_vars *s, char **str)
{
	if (ft_strlen(str[0]) > 0 && str[0][0] == 'F')
	{
		s->map.f++;
		put_colors(s, str);
	}
	else if (ft_strlen(str[0]) > 0 && str[0][0] == 'C')
	{
		s->map.c++;
		put_colors(s, str);
	}
	else if (ft_strlen(str[0]) > 0 && str[0][0] == '1')
		return ;
	else if (!((ft_strlen(str[0]) > 1 && str[0][0] == 'N' && str[0][1] == 'O') \
			|| (ft_strlen(str[0]) > 1 && str[0][0] == 'S' && str[0][1] == 'O') \
			|| (ft_strlen(str[0]) > 1 && str[0][0] == 'E' && str[0][1] == 'A') \
			|| (ft_strlen(str[0]) > 1 && str[0][0] == 'W' && str[0][1] == 'E') \
			|| (ft_strlen(str[0]) > 0 && str[0][0] == 'F') \
			|| (ft_strlen(str[0]) > 0 && str[0][0] == 'C') \
			|| (ft_strlen(str[0]) > 0 && str[0][0] == '1')
			|| (str[0] == NULL)))
		errorpars(-4, s);
}

void	map_verification_2(t_vars *s, char **str)
{
	if (str[0] == NULL)
		return ;
	else if (ft_strlen(str[0]) > 1 && str[0][0] == 'N' && str[0][1] == 'O')
	{
		s->map.no++;
		put_path(s, str);
	}
	else if (ft_strlen(str[0]) > 1 && str[0][0] == 'S' && str[0][1] == 'O')
	{
		s->map.so++;
		put_path(s, str);
	}
	else if (ft_strlen(str[0]) > 1 && str[0][0] == 'E' && str[0][1] == 'A')
	{
		s->map.ea++;
		put_path(s, str);
	}
	else if (ft_strlen(str[0]) > 1 && str[0][0] == 'W' && str[0][1] == 'E')
	{
		s->map.we++;
		put_path(s, str);
	}
}

void	map_verification(t_vars *s, char *line)
{
	int			i;
	char		**str;

	i = 0;
	str = ft_split(line, ' ');
	if (!str)
		error(s, "Error\nProblem with malloc\n");
	map_verification_2(s, str);
	map_verification_3(s, str);
	if (s->map.no > 1 || s->map.so > 1 || s->map.ea > 1 || \
		s->map.we > 1 || s->map.c > 1 || s->map.f > 1)
		errorpars(-1, s);
	if (str[0] && str[0][0] == '1' && (s->map.no < 1 || s->map.so < 1 \
		|| s->map.ea < 1 || s->map.we < 1 || s->map.c < 1 || s->map.f < 1))
		errorpars(-1, s);
	if (str[0] && str[0][0] == '1' && s->map.no == 1 && s->map.so == 1 \
	&& s->map.ea == 1 && s->map.we == 1 && s->map.c == 1 && s->map.f == 1)
		map_verification_4(s, line, i);
	free_split(str);
}
