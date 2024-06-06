/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:10:22 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 17:10:25 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_colors2(t_vars *s, char **rgb, char **str)
{
	if (is_digit(rgb[0]) == -1 || is_digit(rgb[1]) == -1 \
		|| is_digit(rgb[2]) == -1)
	{
		free_split(rgb);
		errorpars(-5, s);
		return ;
	}
	if (str[0][0] == 'C')
		s->map.c_color = convert_rgb(ft_atoi(rgb[0]), \
		ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (str[0][0] == 'F')
		s->map.f_color = convert_rgb(ft_atoi(rgb[0]), \
		ft_atoi(rgb[1]), ft_atoi(rgb[2]));
}

void	put_colors(t_vars *s, char **str)
{
	char	**rgb;

	if (str[1] == NULL || (str[1] && str[2] != NULL))
	{
		errorpars(-5, s);
		return ;
	}
	rgb = ft_split(str[1], ',');
	if (!rgb)
	{
		free_split(str);
		free_split(rgb);
		error(s, "Error\nProblem with malloc\n");
	}
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		free_split(rgb);
		errorpars(-5, s);
		return ;
	}
	put_colors2(s, rgb, str);
	free_split(rgb);
}
