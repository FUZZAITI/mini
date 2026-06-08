/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:17:11 by pepinhei          #+#    #+#             */
/*   Updated: 2025/07/30 09:43:38 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*dup;
	size_t		i;

	i = ft_strlen(s) + 1;
	dup = malloc(i);
	if (!dup)
		return (0);
	ft_memcpy(dup, s, i);
	return (dup);
}
