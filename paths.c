/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:23:06 by eribeiro          #+#    #+#             */
/*   Updated: 2022/07/28 16:08:24 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_path_5(t_vars *s, char **str, int i)
{
	if (str[0][0] == 'N' && str[0][1] == 'O')
	{
		s->text_no = malloc(sizeof(char) * (i + 1));
		if (!s->text_no)
			error(s, "Error\nProblem with malloc\n");
		i = 0;
		while (str[1][i])
		{
			s->text_no[i] = str[1][i];
			i++;
		}
		s->text_no[i] = '\0';
	}
}

void	put_path_4(t_vars *s, char **str, int i)
{
	if (str[0][0] == 'E' && str[0][1] == 'A')
	{
		s->text_ea = malloc(sizeof(char) * (i + 1));
		if (!s->text_ea)
			error(s, "Error\nProblem with malloc\n");
		i = 0;
		while (str[1][i])
		{
			s->text_ea[i] = str[1][i];
			i++;
		}
		s->text_ea[i] = '\0';
	}
}

void	put_path_3(t_vars *s, char **str, int i)
{
	if (str[0][0] == 'W' && str[0][1] == 'E')
	{
		s->text_we = malloc(sizeof(char) * (i + 1));
		if (!s->text_we)
			error(s, "Error\nProblem with malloc\n");
		i = 0;
		while (str[1][i])
		{
			s->text_we[i] = str[1][i];
			i++;
		}
		s->text_we[i] = '\0';
	}
}

void	put_path_2(t_vars *s, char **str, int i)
{
	if (str[0][0] == 'S' && str[0][1] == 'O')
	{
		s->text_so = malloc(sizeof(char) * (i + 1));
		if (!s->text_so)
			error(s, "Error\nProblem with malloc\n");
		i = 0;
		while (str[1][i])
		{
			s->text_so[i] = str[1][i];
			i++;
		}
		s->text_so[i] = '\0';
	}
}

void	put_path(t_vars *s, char **str)
{
	int	i;

	i = 0;
	if (str[1] == NULL || (str[1] && str[2] != NULL))
	{
		errorpars(-2, s);
		return ;
	}
	i = open(str[1], O_RDONLY);
	if (i == -1)
		errorpars(-3, s);
	close (i);
	i = 0;
	while (str[1][i])
		i++;
	put_path_5(s, str, i);
	put_path_2(s, str, i);
	put_path_3(s, str, i);
	put_path_4(s, str, i);
}
