/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:26:44 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 16:04:03 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <sys/types.h>
# include <sys/uio.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define RED_CROSS 33
# define PI 3.14159265359
# define DR 0.0174533
# define BUFFER_SIZE 100
# define R_LEFT	65361
# define R_RIGHT 65363

typedef struct s_play {
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	pa;
}				t_play;

typedef struct s_map
{
	int		no;
	int		so;
	int		ea;
	int		we;
	int		f;
	int		c;
	int		c_color;
	int		f_color;
	int		wrong_char;
	int		line_len;
	int		nb_lines;
	int		max;
	char	**map;
	int		start;
}				t_map;

typedef struct s_data
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct s_vars {
	int		error;
	void	*mlx;
	void	*win;
	char	**map2;
	char	*text_no;
	char	*text_so;
	char	*text_ea;
	char	*text_we;
	t_data	t_no;
	t_data	t_so;
	t_data	t_ea;
	t_data	t_we;
	t_data	td;
	t_play	p;
	t_map	map;
}				t_vars;

typedef struct s_ray {
	int		r;
	int		mx;
	int		my;
	int		dof;
	double	ra;
	double	rx;
	double	ry;
	double	xo;
	double	yo;
	double	distt;
	int		indv;
	int		indh;
	int		indt;
	double	ntan;
	double	atan;
	double	disth;
	double	hx;
	double	hy;
	double	distv;
	double	vx;
	double	vy;
	double	lineh;
	double	lineo;
	double	ca;
	float	ty;
	float	ty_off;
	float	step;
	float	tx;
}				t_ray;

void	errorpars(int i, t_vars *s);
void	checkpos(t_ray *r, t_vars *s);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		closew(t_vars *vars);
double	dist(double ax, double ay, double bx, double by);
void	raycast(t_vars *s);
int		key_hook(int keycode, t_vars *vars);
void	settex(t_vars *vars);
int		ft_render(t_vars *vars);
char	**ft_split(const char *s, char c);
void	surrounded_by_walls(t_vars *s);
void	error(t_vars *s, char *str);
void	check_file(t_vars *s, char *str);
int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	malloc_struct(t_vars *s);
void	map_verification(t_vars *s, char *line);
void	map_error(t_vars *s);
void	parsing_map(t_vars *s, char *map);
void	free_struct(t_vars *s);
void	finish_map(t_vars *s);
void	put_path(t_vars *s, char **str);
int		ft_atoi(const char *nptr);
void	put_colors(t_vars *s, char **str);
int		map_validity(t_vars *s, char *line);
void	map_verification(t_vars *s, char *line);
int		max(int a, int b);
void	free_split(char **str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	initray(t_ray *r);
void	ft_init(t_vars *s);
double	corrangle(double a);
double	dist(double ax, double ay, double bx, double by);
void	rayv(t_ray *r, t_vars *s);
void	rayh(t_ray *r, t_vars *s);
void	puttex(t_ray *r, t_vars *s, int i);
void	putfc(t_ray *r, t_vars *s, int i);
void	checkerreur(t_vars *s);
int		is_digit(char *s);
int		convert_rgb(int r, int g, int b);

#endif
