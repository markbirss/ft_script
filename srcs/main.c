/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:48:34 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/22 17:17:07 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"
#include <sys/mman.h>
#include <time.h>

static void		init_env(t_env **env)
{
	(*env)->cmd_size = 0;
	(*env)->path_size = 0;
	(*env)->opt_a = 0;
	(*env)->opt_d = 0;
	(*env)->opt_f = 0;
	(*env)->opt_p = 0;
	(*env)->opt_q = 0;
	(*env)->opt_r = 0;
	(*env)->opt_k = 0;
	(*env)->opt_t = 0;
	(*env)->path = NULL;
	(*env)->filename = NULL;
	(*env)->command = NULL;
}

static void		free_stuff(t_env *env)
{
	int			i;

	i = 0;
	if (env->filename)
		munmap(env->filename, ft_strlen(env->filename) + 1);
	while (env->command && env->command[i])
	{
		munmap(env->command[i], ft_strlen(env->command[i] + 1));
		i++;
	}
	i = 0;
	while (env->path && env->path[i])
	{
		munmap(env->path[i], ft_strlen(env->path[i]));
		i++;
	}
	if (env->path)
		munmap(env->path, env->path_size);
	if (env->command)
		munmap(env->command, env->cmd_size);
	if (env)
		munmap(env, sizeof(env + 1));
}

static void		msg_start(t_env *env, int fd_file)
{
	time_t curtime;

	time(&curtime);
	ft_putstr("Script started, output file is ");
	ft_putstr_fd("Script started on ", fd_file);
	ft_putstr_fd(ctime(&curtime), fd_file);
	if (env->filename != NULL)
		ft_putendl(env->filename);
	else
		ft_putendl("typescript");
}

static void		msg_end(t_env *env, int fd_file)
{
	time_t curtime;

	time(&curtime);
	ft_putstr("\nScript done, output file is ");
	ft_putstr_fd("\nScript done on ", fd_file);
	ft_putstr_fd(ctime(&curtime), fd_file);
	if (env->filename != NULL)
		ft_putendl(env->filename);
	else
		ft_putendl("typescript");
}

int				main(int ac, char **av, char **envp)
{
	t_env		*env;
	int			ret;
	int			fd_file;

	ret = 0;
	env = ft_mmap(sizeof(t_env) + 1);
	init_env(&env);
	ret = get_params(ac, av, env);
	if (env->command == NULL)
		get_shell(env, envp);
	else
		get_bin_path(env, envp);
	if (ret == -1)
		return (ret);
	if (ret == ac)
		ret = 0;
	fd_file = open_file(env);
	if (env->opt_q == 0)
		msg_start(env, fd_file);
	ft_script(fd_file, envp, env);
	if (env->opt_q == 0)
		msg_end(env, fd_file);
	free_stuff(env);
	close(fd_file);
	return (0);
}
