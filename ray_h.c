/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_h.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:21:45 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 11:53:48 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//down
//up

void	checkpos(t_ray *r, t_vars *s)
{
	if (r->mx > s->map.line_len)
		r->mx = s->map.line_len;
	if (r->mx < 1)
		r->mx = 1;
	if (r->my > s->map.nb_lines)
		r->my = s->map.nb_lines;
	if (r->my < 1)
		r->my = 1;
}

void	rayh2(t_ray *r, t_vars *s)
{
	while (r->dof < s->map.max)
	{
		r->mx = (int)(r->rx) >> 6;
		r->my = (int)(r->ry) >> 6;
		checkpos(r, s);
		if (s->map.map[r->my][r->mx] == '1')
		{
			r->hx = r->rx;
			r->hy = r->ry;
			r->disth = dist(s->p.px, s->p.py, r->hx, r->hy);
			r->dof = s->map.max;
		}
		else
		{
			r->rx += r->xo;
			r->ry += r->yo;
			r->dof += 1;
		}
	}
}

void	initrayh(t_ray *r, t_vars *s)
{
	r->dof = 0;
	r->disth = 64 * s->map.max;
	r->hx = s->p.px;
	r->hy = s->p.py;
	r->atan = -1 / tan(r->ra);
}

void	rayh(t_ray *r, t_vars *s)
{
	initrayh(r, s);
	if (r->ra > PI)
	{
		r->ry = (((int)s->p.py >> 6) << 6) - 0.0000000001;
		r->rx = (s->p.py - r->ry) * r->atan + s->p.px;
		r->yo = -64;
		r->xo = -r->yo * r->atan;
		r->indh = 0;
	}
	else if (r->ra < PI)
	{
		r->ry = (((int)s->p.py >> 6) << 6) + 64;
		r->rx = (s->p.py - r->ry) * r->atan + s->p.px;
		r->yo = 64;
		r->xo = -r->yo * r->atan;
		r->indh = 1;
	}
	else
	{
		r->rx = s->p.px;
		r->ry = s->p.py;
		r->dof = s->map.max;
	}
	rayh2(r, s);
}
