/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:21:52 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 11:52:47 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// left
// right

#include "cub.h"

void	initrayv(t_ray *r, t_vars *s)
{
	r->dof = 0;
	r->distv = 64 * s->map.max;
	r->vx = s->p.px;
	r->vy = s->p.py;
	r->ntan = -tan(r->ra);
}

void	rayv2(t_ray *r, t_vars *s)
{
	while (r->dof < s->map.max)
	{
		r->mx = (int)(r->rx) >> 6;
		r->my = (int)(r->ry) >> 6;
		checkpos(r, s);
		if (s->map.map[r->my][r->mx] == '1')
		{
			r->vx = r->rx;
			r->vy = r->ry;
			r->distv = dist(s->p.px, s->p.py, r->vx, r->vy);
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

void	rayv(t_ray *r, t_vars *s)
{
	initrayv(r, s);
	if (r->ra > (PI / 2) && r->ra < (3 * PI / 2))
	{
		r->rx = (((int)s->p.px >> 6) << 6) - 0.000000001;
		r->ry = (s->p.px - r->rx) * r->ntan + s->p.py;
		r->xo = -64;
		r->yo = -r->xo * r->ntan;
		r->indv = 2;
	}
	else if (r->ra < (PI / 2) || r->ra > (3 * PI / 2))
	{
		r->rx = (((int)s->p.px >> 6) << 6) + 64;
		r->ry = (s->p.px - r->rx) * r->ntan + s->p.py;
		r->xo = 64;
		r->yo = -r->xo * r->ntan;
		r->indv = 3;
	}
	else
	{
		r->rx = s->p.px;
		r->ry = s->p.py;
		r->dof = s->map.max;
	}
	rayv2(r, s);
}
