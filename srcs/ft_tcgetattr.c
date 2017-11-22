/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcgetattr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:54:14 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/22 14:55:28 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"
#include <sys/ioctl.h>
#include <sys/types.h>

/*
** tcgetattr() récupère les paramètres associés à l'objet référencé par fd
** et les stocke dans la structure termios pointée par termios_p.
** Cette fonction peut être appelée par un processus en arrière-plan ;
** néanmoins, les attributs de terminal peuvent être modifiés
** par la suite par le processus en avant-plan.
*/

int			ft_tcgetattr(int fd, struct termios *t)
{
	return (ioctl(fd, TIOCGETA, t));
}
