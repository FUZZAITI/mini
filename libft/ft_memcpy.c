/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:16:38 by pepinhei          #+#    #+#             */
/*   Updated: 2025/08/15 12:10:41 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char						*ptr;
	const unsigned char					*ptrsrc;
	size_t								i;

	if (!dst && !src)
		return (0);
	ptr = (unsigned char *)dst;
	ptrsrc = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr[i] = ptrsrc[i];
		i++;
	}
	return (dst);
}
