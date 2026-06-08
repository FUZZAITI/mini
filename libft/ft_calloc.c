/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:16:28 by pepinhei          #+#    #+#             */
/*   Updated: 2025/08/11 15:44:10 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void				*s;
	size_t				tam;

	tam = nmemb * size;
	if (size != 0 && tam / size != nmemb)
		return (0);
	s = malloc(tam);
	if (!s)
		return (0);
	ft_bzero(s, tam);
	return (s);
}
