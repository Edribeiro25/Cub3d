/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:22:11 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 13:17:39 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	keycode3(int keycode, t_vars *vars, int opx, int opy)
{
	if (keycode == KEY_S)
	{
		opx = (int)(vars->p.px - vars->p.pdx * 10) >> 6;
		if (vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px -= vars->p.pdx * 2;
		opy = (int)(vars->p.py - vars->p.pdy * 10) >> 6;
		if (vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py -= vars->p.pdy * 2;
	}
	if (keycode == KEY_W)
	{
		opx = (int)(vars->p.px + vars->p.pdx * 10) >> 6;
		if (vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px += vars->p.pdx * 2;
		opy = (int)(vars->p.py + vars->p.pdy * 10) >> 6;
		if (vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py += vars->p.pdy * 2;
	}
	return (0);
}

int	keycode4(int keycode, t_vars *vars)
{
	double	angle;
	int		opx;
	int		opy;

	if (keycode == KEY_A)
	{
		angle = corrangle(vars->p.pa - (PI / 2));
		opx = (int)(vars->p.px + cos(angle) * 10) >> 6;
		if (vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px += cos(angle) * 2;
		opy = (int)(vars->p.py + sin(angle) * 10) >> 6;
		if (vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py += sin(angle) * 2;
	}
	return (0);
}

int	keycode2(int keycode, t_vars *vars)
{
	double	angle;
	int		opx;
	int		opy;

	if (keycode == KEY_D)
	{
		angle = corrangle(vars->p.pa + (PI / 2));
		opx = (int)(vars->p.px + cos(angle) * 10) >> 6;
		if (vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px += cos(angle) * 2;
		opy = (int)(vars->p.py + sin(angle) * 10) >> 6;
		if (vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py += sin(angle) * 2;
	}
	keycode4(keycode, vars);
	keycode3(keycode, vars, opx, opy);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		closew(vars);
	if (keycode == R_LEFT)
	{
		vars->p.pa -= 0.02;
		if (vars->p.pa < 0)
			vars->p.pa += 2 * PI;
		if (vars->p.pa > 2 * PI)
			vars->p.pa -= 2 * PI;
		vars->p.pdx = cos(vars->p.pa);
		vars->p.pdy = sin(vars->p.pa);
	}
	if (keycode == R_RIGHT)
	{
		vars->p.pa += 0.02;
		if (vars->p.pa < 0)
			vars->p.pa += 2 * PI;
		if (vars->p.pa > 2 * PI)
			vars->p.pa -= 2 * PI;
		vars->p.pdx = cos(vars->p.pa);
		vars->p.pdy = sin(vars->p.pa);
	}
	keycode2(keycode, vars);
	return (1);
}
