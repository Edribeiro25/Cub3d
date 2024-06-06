/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:41:35 by aazra             #+#    #+#             */
/*   Updated: 2022/07/28 16:21:13 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_error(t_vars *s)
{
	if (s->map.line_len == -1)
		error(s, "Error : invalid map\n");
	if (s->map.nb_lines == 0)
		error(s, "Error : invalid map\n");
	if (s->map.wrong_char == -1)
		error(s, "Error : wrong character in map\n");
}

void	error(t_vars *s, char *str)
{
	write(1, str, ft_strlen(str));
	closew(s);
	exit(0);
}

void	errorpars(int i, t_vars *s)
{
	if (s->error < 0)
		return ;
	else
		s->error = i;
}

void	checkerreur(t_vars *s)
{
	if (s->error == 0)
		return ;
	if (s->error == -1)
		error(s, "Error\nMissing or duplicate elements\n");
	if (s->error == -2)
		error(s, "Error\nToo much or not enough strs for element\n");
	if (s->error == -3)
		error(s, "Error\nBad path elements\n");
	if (s->error == -4)
		error(s, "Error\nBad map\n");
	if (s->error == -5)
		error(s, "Error\nRGB colors are not good\n");
}
