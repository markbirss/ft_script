/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:56:12 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/22 14:56:42 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"
#include <fcntl.h>

int		open_file(t_env *env)
{
	if (env->opt_a == 1)
		return (open(env->filename, OPEN_FLAGS | O_APPEND, OPEN_MODE));
	else
		return (open(env->filename, OPEN_FLAGS | O_TRUNC, OPEN_MODE));
}
