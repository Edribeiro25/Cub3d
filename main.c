/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:48:18 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 13:34:51 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	closew(t_vars *vars)
{
	if (vars->t_ea.img)
		mlx_destroy_image(vars->mlx, vars->t_ea.img);
	if (vars->t_so.img)
		mlx_destroy_image(vars->mlx, vars->t_so.img);
	if (vars->t_no.img)
		mlx_destroy_image(vars->mlx, vars->t_no.img);
	if (vars->t_we.img)
		mlx_destroy_image(vars->mlx, vars->t_we.img);
	if (vars->td.img)
		mlx_destroy_image(vars->mlx, vars->td.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->mlx)
		free(vars->mlx);
	free_struct(vars);
	exit(0);
	return (1);
}

void	putfc(t_ray *r, t_vars *s, int i)
{
	int	j;

	j = 0;
	while (j < 768)
	{
		if (j < r->lineo)
		{
			s->td.addr[j * s->td.line_length / 4 + i] = s->map.f_color;
		}
		else if (j >= r->lineh + r->lineo)
		{
			s->td.addr[j * s->td.line_length / 4 + i] = s->map.c_color;
		}
		j++;
	}
}

int	ft_render(t_vars *vars)
{
	raycast(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->td.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	s;

	ft_init(&s);
	if (ac != 2)
		error(&s, "Error : not 2 args\n");
	else
		check_file(&s, av[1]);
	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, 1280, 768, "Cub3d");
	s.td.img = mlx_new_image(s.mlx, 1280, 768);
	s.td.addr = (int *)mlx_get_data_addr(s.td.img, &s.td.bits_per_pixel, \
	&s.td.line_length, &s.td.endian);
	settex(&s);
	mlx_key_hook(s.win, key_hook, &s);
	mlx_hook(s.win, ClientMessage, StructureNotifyMask, closew, &s);
	mlx_hook(s.win, KeyPress, KeyPressMask, key_hook, &s);
	mlx_loop_hook(s.mlx, ft_render, &s);
	mlx_loop(s.mlx);
}
