/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:41:45 by aazra             #+#    #+#             */
/*   Updated: 2022/07/25 14:08:40 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_struct(t_vars *s)
{
	int	i;

	i = 0;
	if (s->map.map)
	{
		while (i < s->map.nb_lines + 2)
		{
			free(s->map.map[i]);
			i++;
		}
		free(s->map.map);
	}
	if (s->text_ea)
		free(s->text_ea);
	if (s->text_we)
		free(s->text_we);
	if (s->text_no)
		free(s->text_no);
	if (s->text_so)
		free(s->text_so);
}
