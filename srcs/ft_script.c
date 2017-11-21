/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:51:09 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/17 13:56:52 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_script.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <utmp.h>

static void test(int fdm, int fds, int fdf, t_env *env)
{
	int pid;
	int i;
	fd_set set;
	char buf[64];

	if ((pid = fork()) < 0)
		exit(2);
	if (!pid)
	{
		// child
		close(fdm);
		dup2(fds, 0);
		dup2(fds, 1);
		dup2(fds, 2);
		execl(env->command[0], env->command[0]);
		exit(3);
	}
	/* father: copy stdin/out to/from master */
	close(fds);
	system("stty raw -echo");
	FD_ZERO(&set);
	while (waitpid(pid, &i, WNOHANG) != pid)
	{
		FD_SET(0, &set);
		FD_SET(fdm, &set);
		select(fdm + 1, &set, NULL, NULL, NULL);
		if (FD_ISSET(0, &set))
		{
			i = read(0, buf, 64);
			if (i > 0)
				write(fdm, buf, i);
		}
		if (FD_ISSET(fdm, &set))
		{
			i = read(fdm, buf, 64);
			if (i > 0)
			{
				write(1, buf, i);
				write(fdf, buf, i);
			}
		}
	}
	system("stty sane");
	exit(0);
}

void ft_script(t_env *env)
{
	int fd_master;
	int fd_slave;
	int fd_file;

	if (env->opt_a == 1)
		fd_file = open(env->filename, OPEN_FLAGS | O_APPEND, OPEN_MODE);
	else
		fd_file = open(env->filename, OPEN_FLAGS | O_TRUNC, OPEN_MODE);
	if (create_pty(&fd_master, &fd_slave) == -1)
		return;
	if (!fd_file || !fd_master || !fd_slave)
		return;
	test(fd_master, fd_slave, fd_file, env);
	close(fd_file);
}