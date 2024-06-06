/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:48:18 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/27 22:47:59 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"


int	closew(t_vars *vars)
{
	mlx_destroy_image(vars->mlx,vars->t_ea.img);
	mlx_destroy_image(vars->mlx,vars->t_so.img);
	mlx_destroy_image(vars->mlx,vars->t_no.img);
	mlx_destroy_image(vars->mlx,vars->t_we.img);
	mlx_destroy_image(vars->mlx,vars->td.img);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	exit(0);
	return (1);
}

double dist(double ax ,double ay ,double bx , double by )
{
	return (sqrt((bx-ax)*(bx-ax) + (by- ay) * (by - ay)));
}

void raycast(t_vars *s)
{
	int r = 0,mx = 0,my = 0,dof = 0,i = 0,j = 0;
	double rx = 0,ry = 0,ra = 0,xo = 0,yo = 0,distT = 0;
	int indV = 0, indH = 0 ,indT = 0;

	double nTan = 0;
	double aTan = 0;

	ra=s->p.pa - 30 * DR;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 *PI)
		ra -= 2*PI;
	r = 0;
	while(r < 1280)
	{
		dof = 0;
		double DistH = 1000000000000;
		double hx = s->p.px;
		double hy = s->p.py;
		aTan = -1/tan(ra);
		//up
		if(ra > PI)
		{
			ry = (((int)s->p.py >> 6)<< 6) - 0.0000000001;
			rx = (s->p.py - ry) * aTan + s->p.px;
			yo = - 64;
			xo = -yo * aTan;
			indH = 0;
		}
		//down
		else if(ra < PI)
		{
			ry = (((int)s->p.py >> 6)<< 6) + 64;
			rx = (s->p.py - ry) * aTan + s->p.px;
			yo = 64;
			xo = -yo * aTan;
			indH = 1;
		}
		else
		{
			rx = s->p.px;
			ry = s->p.py;
			dof = s->map.max; 
		}
		while (dof < s->map.max)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			if (mx > s->map.line_len)
				mx = s->map.line_len;
			if (mx < 1)
				mx = 1;
			if (my > s->map.nb_lines)
				my = s->map.nb_lines;
			if (my < 1)
				my = 1;
			if (s->map.map[my][mx] == '1')
			{
				hx = rx;
				hy = ry;
				DistH = dist(s->p.px,s->p.py,hx,hy);
				dof = s->map.max;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		dof = 0;
		double Distv = 100000000000;
		double vx = s->p.px;
		double vy = s->p.py;
		nTan = -tan(ra);
		// left
		if(ra > (PI / 2) && ra < (3 * PI / 2))
		{
			rx = (((int)s->p.px >> 6)<< 6) - 0.000000001;
			ry = (s->p.px - rx) * nTan + s->p.py;
			xo = - 64;
			yo = -xo * nTan;
			indV = 2;
		}
		// right
		else if (ra < (PI / 2) || ra > (3 * PI / 2))
		{
			rx = (((int)s->p.px >> 6)<< 6) + 64;
			ry = (s->p.px - rx) * nTan + s->p.py;
			xo = 64;
			yo = -xo * nTan;
			indV = 3;
		}
		else
		{
			rx = s->p.px;
			ry = s->p.py;
			dof = s->map.max; 
		}
		while (dof < s->map.max)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			if (mx > s->map.line_len)
				mx = s->map.line_len;
			if (mx < 1)
				mx = 1;
			if (my > s->map.nb_lines)
				my = s->map.nb_lines;
			if (my < 1)
				my = 1;
			if (s->map.map[my][mx] == '1')
			{
				vx = rx;
				vy = ry;
				Distv = dist(s->p.px,s->p.py,vx,vy);
				dof = s->map.max;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (DistH < Distv)
		{
			rx = hx;
			ry = hy;
			distT = DistH;
			indT = indH;
		}
		if (Distv < DistH)
		{
			rx = vx;
			ry = vy;
			distT = Distv;
			indT = indV;
		}
		double lineH = 0;
		double lineO = 0;
		double ca = 0;

		ca = s->p.pa - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 *PI)
			ca -= 2*PI;
		distT = distT * cos(ca);
		if(distT == 0)
			lineH = 0;
		else
			lineH = (64 * 768) / distT;
		lineO = 0;
		float ty = 0;
		float ty_off = 0;
		float step;
		step = 64.0 / lineH;
		if (lineH > 768)
		{
			ty_off = (lineH - 768) / 2.0;
			lineH = 768;
		}
		if (lineO < 0)
			lineO = 0;
		lineO = (768 / 2) - ((int)lineH >> 1);
		i = r;
		ty = ty_off * step;
		float tx;
		if(indT == 0 || indT == 1)
			tx = (int)rx % 64;
		else
			tx = (int)ry % 64;
		j = 0;
		while (j < 768)
		{
			if (j < lineO)
			{
				s->td.addr[j * s->td.line_length/4 +i] = s->map.f_color;
			}
			else if (j >= lineH + lineO)	
			{
				s->td.addr[j * s->td.line_length/4 +i] = s->map.c_color;
			}
			j++;
		}
		j = 0;
		while (j < lineH)
		{
				if (indT == 0)
					s->td.addr[(int)(j + lineO) * s->td.line_length / 4 + i] = s->t_no.addr[(int)ty * s->t_no.line_length/4 + (int)tx];
				else if (indT == 1)
				{
					s->td.addr[(int)(j + lineO) * s->td.line_length / 4 + i] = s->t_so.addr[(int)ty * s->t_so.line_length/4 + (int)tx];
				}
				else if (indT == 3)
				{
					s->td.addr[(int)(j + lineO) * s->td.line_length / 4 + i] = s->t_ea.addr[(int)ty * s->t_ea.line_length/4 + (int)tx];
				}
				else
				{
					s->td.addr[(int)(j + lineO) * s->td.line_length / 4 + i] =s->t_we.addr[(int)ty * s->t_we.line_length/4 + (int)tx];
				}
				ty += step;
				j++;
		}
		r++;
		ra += DR/20;
		if(ra < 0)
			ra += 2 * PI;
		if (ra > 2 *PI)
			ra -= 2*PI;
	}
}
int keycode2(int keycode, t_vars *vars)
{
	double angle;
	int		opx = 0;
	int		opy = 0;

	angle = vars->p.pa;
	if (keycode == KEY_D)
	{
		angle = vars->p.pa + (PI / 2);
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 *PI)
			angle -= 2*PI;
		opx = (int)(vars->p.px + cos(angle) * 5) >> 6;
		if(vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px += cos(angle) * 2;
		opy = (int)(vars->p.py + sin(angle) * 5) >> 6;
		if(vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py += sin(angle) * 2;
	}
	if (keycode == KEY_A)
	{
		angle = vars->p.pa - (PI / 2);
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 *PI)
			angle -= 2*PI;
		opx = (int)(vars->p.px + cos(angle) * 5) >> 6;
		if(vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px += cos(angle) * 2; 
		opy = (int)(vars->p.py + sin(angle) * 5) >> 6;
		if(vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py += sin(angle) * 2;
	}
	if (keycode == KEY_S)
	{
		opx = (int)(vars->p.px - vars->p.pdx * 5) >> 6;
		if(vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px -= vars->p.pdx * 2;
		opy = (int)(vars->p.py - vars->p.pdy * 5) >> 6;
		if(vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py -= vars->p.pdy * 2;
	}
	if (keycode == KEY_W)
	{
		opx = (int)(vars->p.px + vars->p.pdx * 5) >> 6;
		if(vars->map.map[(int)vars->p.py >> 6][opx] != '1')
			vars->p.px += vars->p.pdx * 2;
		opy = (int)(vars->p.py + vars->p.pdy * 5) >> 6;
		if(vars->map.map[opy][(int)vars->p.px >> 6] != '1')
			vars->p.py += vars->p.pdy * 2;
	}
	return(0);
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
		if (vars->p.pa > 2 *PI)
			vars->p.pa -= 2*PI;
		vars->p.pdx = cos(vars->p.pa) * 2;
		vars->p.pdy = sin(vars->p.pa) * 2;
	}
	if (keycode == R_RIGHT)
	{
			vars->p.pa += 0.02;
		if (vars->p.pa < 0)
			vars->p.pa += 2 * PI;
		if (vars->p.pa > 2 *PI)
			vars->p.pa -= 2*PI;
		vars->p.pdx = cos(vars->p.pa) * 2;
		vars->p.pdy = sin(vars->p.pa) * 2;
	}
	keycode2(keycode,vars);
	return (1);
}


void settex(t_vars *s)
{
	s->t_no.img= mlx_xpm_file_to_image(s->mlx,s->text_no,&s->t_no.width,&s->t_no.height);
	s->t_so.img= mlx_xpm_file_to_image(s->mlx,s->text_so,&s->t_so.width,&s->t_so.height);
	s->t_ea.img= mlx_xpm_file_to_image(s->mlx,s->text_ea,&s->t_ea.width,&s->t_ea.height);
	s->t_we.img= mlx_xpm_file_to_image(s->mlx,s->text_we,&s->t_we.width,&s->t_we.height);
	s->t_no.addr = (int *)mlx_get_data_addr(s->t_no.img, &s->t_no.bits_per_pixel, &s->t_no.line_length,&s->t_no.endian);	
	s->t_so.addr = (int *)mlx_get_data_addr(s->t_so.img, &s->t_so.bits_per_pixel, &s->t_so.line_length,&s->t_so.endian);
	s->t_ea.addr = (int *)mlx_get_data_addr(s->t_ea.img, &s->t_ea.bits_per_pixel, &s->t_ea.line_length,
								&s->t_ea.endian);
	s->t_we.addr = (int *)mlx_get_data_addr(s->t_we.img, &s->t_we.bits_per_pixel, &s->t_we.line_length,
								&s->t_we.endian);
}

int ft_render(t_vars *vars)
{
	raycast(vars);
	mlx_put_image_to_window(vars->mlx,vars->win,vars->td.img,0,0);
	return(0);
}

void ft_init(t_vars *s)
{
	s->text_no = NULL;
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
}

int	main(int ac ,char **av)
{
	t_vars	s;

	ft_init(&s);
	if (ac != 2)
		error(&s, "Error : not 2 args\n");
	else
		check_file(&s, av[1]);
	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, 1280, 768, "Cub3d");
	settex(&s);
	s.td.img = mlx_new_image(s.mlx,1280,768);
	s.td.addr = (int *)mlx_get_data_addr(s.td.img, &s.td.bits_per_pixel, &s.td.line_length,
								&s.td.endian);
	mlx_key_hook(s.win, key_hook, &s);
	mlx_hook(s.win, ClientMessage,StructureNotifyMask, closew, &s);
	mlx_hook(s.win, KeyPress, KeyPressMask, key_hook, &s);
	mlx_loop_hook(s.mlx,ft_render,&s);
	mlx_loop(s.mlx);
}

