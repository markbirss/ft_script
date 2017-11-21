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

// static void test(int fdm, int fds, int fdf, t_env *env)
// {
// 	int pid;
// 	int i;
// 	fd_set set;
// 	char buf[64];

// 	if ((pid = fork()) < 0)
// 		exit(2);
// 	if (!pid)
// 	{
// 		close(fdm);
// 		dup2(fds, 0);
// 		dup2(fds, 1);
// 		dup2(fds, 2);
// 		execl(env->command[0], env->command[0]);
// 		exit(3);
// 	}
// 	/* father: copy stdin/out to/from master */
// 	close(fds);
// 	system("stty raw -echo");//avoid echo command
// 	FD_ZERO(&set);
// 	while (waitpid(pid, &i, WNOHANG) != pid)
// 	{
// 		FD_SET(0, &set);
// 		FD_SET(fdm, &set);
// 		select(fdm + 1, &set, NULL, NULL, NULL);
// 		if (FD_ISSET(0, &set))
// 		{
// 			i = read(0, buf, 64);
// 			if (i > 0)
// 				write(fdm, buf, i);
// 		}
// 		if (FD_ISSET(fdm, &set))
// 		{
// 			i = read(fdm, buf, 64);
// 			if (i > 0)
// 			{
// 				write(1, buf, i);
// 				write(fdf, buf, i);
// 			}
// 		}
// 	}
// 	system("stty sane");
// 	exit(0);
// }

static int			read_master(int fd_master, int fd_file, fd_set fd_in)
{
	int				rc;
	char			input[150];

	if (FD_ISSET(fd_master, &fd_in))
	{
		rc = read(fd_master, input, sizeof(input));
		if (rc > 0)
		{
			write(fd_file, input, rc);
			write(1, input, rc);
		}
		else if (rc <= 0)
			return (-1);
	}
	return (0);
}

static int			read_user(int fd_master, fd_set fd_in)
{
	int				rc;
	char			input[150];

	if (FD_ISSET(0, &fd_in))
	{
		rc = read(0, input, sizeof(input));
		if (rc > 0)
		{
			if (write(fd_master, input, rc) <= 0)
				return (-1);
		}
		else if (rc < 0)
			return (-1);
	}
	return (0);
}

static void			fork_parent(int fd_master, int fd_slave, int fd_file)
{
	int				rc;
	fd_set			fd_in;

	system("stty raw -echo");//avoid echo command
	close(fd_slave);
	while (42)
	{
		FD_ZERO(&fd_in);
		FD_SET(0, &fd_in);
		FD_SET(fd_master, &fd_in);
		rc = select(fd_master + 1, &fd_in, NULL, NULL, NULL);
		if (rc == -1)
			return ;
		else if (rc > 0)
		{
			if (read_user(fd_master, fd_in) == -1)
				return ;
			if (read_master(fd_master, fd_file, fd_in) == -1)
				return ;
		}
	}
	system("stty sane");
}

static void			fork_child(int fd_master, int fd_slave, t_env *env)
{
	close(fd_master);
	dup2(fd_slave, 0);
	dup2(fd_slave, 1);
	dup2(fd_slave, 2);
	close(fd_slave);
	setsid();
	ioctl(0, TIOCSCTTY, 1);
	if (env->command != NULL)
		execvp(env->command[0], env->command);
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
	if (fork())
		fork_parent(fd_master, fd_slave, fd_file);
	else
		fork_child(fd_master, fd_slave, env);
	// test(fd_master, fd_slave, fd_file, env);
	close(fd_file);
}