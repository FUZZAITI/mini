/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:15:14 by pepinhei          #+#    #+#             */
/*   Updated: 2025/08/11 15:44:01 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char		*ptr;
	size_t				i;

	ptr = (unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		ptr[i] = '\0';
		i++;
		n--;
	}
}
