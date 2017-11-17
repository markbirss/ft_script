/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptsname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:45:38 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/17 13:46:04 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/param.h>

char				*ft_ptsname(int fd)
{
	static char		ptsnamebuf[MAXPATHLEN];
	char			*retval;
	struct stat		sbuf;

	retval = NULL;
	if (ioctl(fd, TIOCPTYGNAME, ptsnamebuf) == -1)
		return (NULL);
	if (stat(ptsnamebuf, &sbuf) == 0)
		retval = ptsnamebuf;
	return (retval);
}
