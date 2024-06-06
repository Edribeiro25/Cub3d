/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:10:26 by aazra             #+#    #+#             */
/*   Updated: 2022/07/28 11:22:57 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	count;

	count = 0;
	if (!(src) || !(dst))
		return (0);
	if (size > 0)
	{
		while (--size && src[count])
		{
			dst[count] = src[count];
			count++;
		}
		dst[count] = '\0';
	}
	while (src[count])
		count++;
	return (count);
}
