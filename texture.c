/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:21:56 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 11:22:52 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	settex(t_vars *s)
{
	s->t_no.img = mlx_xpm_file_to_image(s->mlx, \
	s->text_no, &s->t_no.width, &s->t_no.height);
	if (!s->t_no.img)
		error(s, "Error\nProblem with xpm_file_to_image\n");
	s->t_so.img = mlx_xpm_file_to_image(s->mlx, \
	s->text_so, &s->t_so.width, &s->t_so.height);
	if (!s->t_so.img)
		error(s, "Error\nProblem with xpm_file_to_image\n");
	s->t_ea.img = mlx_xpm_file_to_image(s->mlx, \
	s->text_ea, &s->t_ea.width, &s->t_ea.height);
	if (!s->t_ea.img)
		error(s, "Error\nProblem with xpm_file_to_image\n");
	s->t_we.img = mlx_xpm_file_to_image(s->mlx, \
	s->text_we, &s->t_we.width, &s->t_we.height);
	if (!s->t_we.img)
		error(s, "Error\nProblem with xpm_file_to_image\n");
	s->t_no.addr = (int *)mlx_get_data_addr(s->t_no.img, \
	&s->t_no.bits_per_pixel, &s->t_no.line_length, &s->t_no.endian);
	s->t_so.addr = (int *)mlx_get_data_addr(s->t_so.img, \
	&s->t_so.bits_per_pixel, &s->t_so.line_length, &s->t_so.endian);
	s->t_ea.addr = (int *)mlx_get_data_addr(s->t_ea.img, \
	&s->t_ea.bits_per_pixel, &s->t_ea.line_length, &s->t_ea.endian);
	s->t_we.addr = (int *)mlx_get_data_addr(s->t_we.img, \
	&s->t_we.bits_per_pixel, &s->t_we.line_length, &s->t_we.endian);
}

void	puttex(t_ray *r, t_vars *s, int i)
{
	int	j;

	j = 0;
	while (j < r->lineh)
	{
		if (r->indt == 0)
			s->td.addr[(int)(j + r->lineo) * s->td.line_length / 4 + i] = \
			s->t_no.addr[(int)r->ty * s->t_no.line_length / 4 + (int)r->tx];
		else if (r->indt == 1)
			s->td.addr[(int)(j + r->lineo) * s->td.line_length / 4 + i] = \
			s->t_so.addr[(int)r->ty * s->t_so.line_length / 4 + (int)r->tx];
		else if (r->indt == 3)
			s->td.addr[(int)(j + r->lineo) * s->td.line_length / 4 + i] = \
			s->t_ea.addr[(int)r->ty * s->t_ea.line_length / 4 + (int)r->tx];
		else
			s->td.addr[(int)(j + r->lineo) * s->td.line_length / 4 + i] = \
			s->t_we.addr[(int)r->ty * s->t_we.line_length / 4 + (int)r->tx];
		r->ty += r->step;
		j++;
	}
}
