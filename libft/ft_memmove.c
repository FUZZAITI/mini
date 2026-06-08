/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:16:42 by pepinhei          #+#    #+#             */
/*   Updated: 2025/08/11 13:27:10 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*dst2;
	unsigned const char		*src2;
	size_t					i;

	if (dst == src || len == 0)
		return (dst);
	dst2 = (unsigned char *)dst;
	src2 = (unsigned const char *)src;
	i = 0;
	if (dst2 < src2)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len > 0)
		{
			len--;
			dst2[len] = src2[len];
		}
	}
	return (dst);
}
