/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:17:33 by pepinhei          #+#    #+#             */
/*   Updated: 2025/07/30 12:32:39 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t					i;
	unsigned char			x;

	x = (unsigned char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == x)
			return ((char *)(s + i));
		i--;
	}
	if (s[i] == x)
		return ((char *)(s + i));
	return (0);
}
