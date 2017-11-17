/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:44:49 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/17 13:44:54 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"
#include <unistd.h>

static char		*copy(char *dst, const char *src)
{
	size_t i;

	i = 0;
	while (*src)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (dst);
}

char			*ft_mmap_strdup(const char *s1)
{
	char	*new;
	size_t	i;

	i = 0;
	i = ft_strlen(s1);
	new = ft_mmap(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	new = copy(new, s1);
	return (new);
}
