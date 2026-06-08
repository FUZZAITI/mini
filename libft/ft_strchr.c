/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:17:07 by pepinhei          #+#    #+#             */
/*   Updated: 2025/07/30 12:31:44 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned const char				*str;
	unsigned char					x;

	str = (unsigned const char *)s;
	x = (unsigned char)c;
	while (*str)
	{
		if (*str == x)
			return ((char *)str);
		str++;
	}
	if (*str == x)
		return ((char *)str);
	return (0);
}
