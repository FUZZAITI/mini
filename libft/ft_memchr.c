/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:16:02 by pepinhei          #+#    #+#             */
/*   Updated: 2025/07/30 09:54:59 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char		*str;
	unsigned char			val;
	size_t					i;

	str = (unsigned const char *)s;
	val = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == val)
			return ((void *)&str[i]);
		i++;
	}
	return (0);
}
