/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:23:33 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 11:23:34 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	raychoose(t_ray *r)
{
	if (r->disth < r->distv)
	{
		r->rx = r->hx;
		r->ry = r->hy;
		r->distt = r->disth;
		r->indt = r->indh;
	}
	if (r->distv < r->disth)
	{
		r->rx = r->vx;
		r->ry = r->vy;
		r->distt = r->distv;
		r->indt = r->indv;
	}
}

void	rayset(t_ray *r, t_vars *s)
{
	r->ca = corrangle(s->p.pa - r->ra);
	r->distt = r->distt * cos(r->ca);
	if (r->distt == 0)
		r->lineh = 0;
	else
		r->lineh = (64 * 768) / r->distt;
	r->step = 64.0 / r->lineh;
	r->ty_off = 0;
	if (r->lineh > 768)
	{
		r->ty_off = (r->lineh - 768) / 2.0;
		r->lineh = 768;
	}
	if (r->lineo < 0)
		r->lineo = 0;
	r->lineo = (768 / 2) - ((int)r->lineh >> 1);
	if (r->indt == 0 || r->indt == 1)
		r->tx = (int)r->rx % 64;
	else
		r->tx = (int)r->ry % 64;
	r->ty = r->ty_off * r->step;
}

void	raycast(t_vars *s)
{
	int		r;
	t_ray	ray;

	r = 0;
	initray(&ray);
	ray.ra = corrangle(s->p.pa - 30 * DR);
	while (r < 1280)
	{
		rayh(&ray, s);
		rayv(&ray, s);
		raychoose(&ray);
		rayset(&ray, s);
		puttex(&ray, s, r);
		putfc(&ray, s, r);
		r++;
		ray.ra = corrangle(ray.ra + DR / 20);
	}
}
