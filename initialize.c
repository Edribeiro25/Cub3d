/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:22:14 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 15:46:38 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_init_2(t_vars *s)
{
	s->map.f = 0;
	s->map.c = 0;
	s->map.c_color = -1;
	s->map.f_color = -1;
	s->map.map = NULL;
	s->map.start = 0;
	s->td.addr = 0;
	s->td.bits_per_pixel = 0;
	s->td.height = 0;
	s->td.endian = 0;
	s->td.width = 0;
	s->mlx = NULL;
	s->win = NULL;
	s->td.img = NULL;
	s->error = 0;
}

void	ft_init(t_vars *s)
{
	s->text_no = NULL;
	s->t_ea.img = NULL;
	s->t_no.img = NULL;
	s->t_so.img = NULL;
	s->t_we.img = NULL;
	s->text_so = NULL;
	s->text_ea = NULL;
	s->text_we = NULL;
	s->p.px = -1;
	s->p.py = -1;
	s->p.pa = -1;
	s->p.pdx = cos(s->p.pa);
	s->p.pdy = sin(s->p.pa);
	s->map.line_len = -1;
	s->map.wrong_char = 0;
	s->map.nb_lines = 0;
	s->map.no = 0;
	s->map.so = 0;
	s->map.ea = 0;
	s->map.we = 0;
	ft_init_2(s);
}

void	initray_2(t_ray *r)
{
	r->atan = 0;
	r->disth = 0;
	r->hx = 0;
	r->hy = 0;
	r->distv = 0;
	r->vx = 0;
	r->vy = 0;
	r->lineh = 0;
	r->lineo = 0;
	r->ca = 0;
	r->ty = 0;
	r->ty_off = 0;
	r->step = 0;
	r->tx = 0;
}

void	initray(t_ray *r)
{
	r->r = 0;
	r->mx = 0;
	r->my = 0;
	r->dof = 0;
	r->ra = 0;
	r->rx = 0;
	r->ry = 0;
	r->ra = 0;
	r->xo = 0;
	r->yo = 0;
	r->distt = 0;
	r->indv = 0;
	r->indh = 0;
	r->indt = 0;
	r->ntan = 0;
	initray_2(r);
}
