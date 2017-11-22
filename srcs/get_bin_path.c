/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:45:26 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/22 16:46:31 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"

static int			count_path(char *ret)
{
	int				i;
	int				count;

	i = 0;
	if (!ret)
		return (0);
	count = 1;
	while (ret[i])
	{
		if (ret[i] == ':')
			count++;
		i++;
	}
	return (count);
}

static int			ret_copy(char *ret, int c, t_env *env)
{
	int i;
	int y;
	int e;

	i = 0;
	y = 0;
	while (ret[i])
	{
		if (ret[i] == ':')
			break ;
		env->path[c][i] = ret[i];
		i++;
	}
	env->path[c][i] = '/';
	e = i + 1;
	i++;
	while (env->command[0][y])
	{
		env->path[c][e] = env->command[0][y];
		y++;
		e++;
	}
	return (i);
}

static void			add_path(t_env *env, char *ret, int count)
{
	int i;
	int c;

	c = 0;
	i = 0;
	while (ret[i] && count >= c)
	{
		env->path[c] = ft_mmap(1024);
		i += ret_copy(ret + i, c, env);
		c++;
	}
}

void				get_bin_path(t_env *env, char **envp)
{
	int				i;
	int				count;
	char			*ret;

	i = 0;
	ret = NULL;
	while (envp[i])
	{
		if ((ret = ft_strstr(envp[i], "PATH")) != NULL)
		{
			while (*ret != '=')
				ret++;
			ret++;
			count = count_path(ret);
			env->path = ft_mmap(sizeof(char*) * count + 1);
			add_path(env, ret, count);
			env->command[count + 1] = NULL;
			break ;
		}
		i++;
	}
}
