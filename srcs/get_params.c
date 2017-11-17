/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:47:27 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/17 13:48:31 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"

static void		invalid_param(char c)
{
	ft_putstr("script: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
	ft_putendl("usage: script [-adpqr] [file [command ...]]");
}

static int		parse_simple_param(char *s, t_env **env)
{
	int			i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == 'a')
			(*env)->opt_a = 1;
		else if (s[i] == 'd')
			(*env)->opt_d = 1;
		else if (s[i] == 'F')
			(*env)->opt_f = 1;
		else if (s[i] == 'p')
			(*env)->opt_p = 1;
		else if (s[i] == 'q')
			(*env)->opt_q = 1;
		else if (s[i] == 'r')
			(*env)->opt_r = 1;
		else
		{
			invalid_param(s[i]);
			return (-1);
		}
		i++;
	}
	return (1);
}

int				get_params(int ac, char **av, t_env **env)
{
	int			i;
	int			y;

	i = 1;
	y = 0;
	while (i < ac && av[i] && av[i][0] == '-')
	{
		if (parse_simple_param((av[i]) + 1, env) == -1)
			return (-1);
		i++;
	}
	if (av[i] && ft_strlen(av[i]) > 0 && av[i][0] != '-')
	{
		(*env)->filename = ft_mmap_strdup(av[i]);
		i++;
	}
	else if (ac == i)
		(*env)->filename = ft_mmap_strdup("typescript");
	if (i < ac)
	{
		(*env)->command = ft_mmap(sizeof(char*) * (ac - i + 1));
		(*env)->cmd_size = ac - i + 1;
		while (i < ac)
		{
			(*env)->command[y] = ft_mmap_strdup(av[i]);
			i++;
			y++;
		}
		(*env)->command[y] = NULL;
	}
	return (i);
}
