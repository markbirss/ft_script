/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:50:26 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/17 13:50:49 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"

void		get_shell(t_env *env, char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (envp[i])
	{
		if ((ret = ft_strstr(envp[i], "SHELL")) != NULL)
		{
			while (*ret != '=')
				ret++;
			ret++;
			env->bash = ft_strdup(ret);
		}
		i++;
	}
}
