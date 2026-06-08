/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:16:45 by pepinhei          #+#    #+#             */
/*   Updated: 2025/07/30 10:01:48 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*ptr;
	unsigned char		val;
	size_t				i;

	ptr = (unsigned char *)b;
	val = (unsigned char)c;
	i = 0;
	while (len > 0)
	{
		ptr[i] = val;
		len--;
		i++;
	}
	return (b);
}
