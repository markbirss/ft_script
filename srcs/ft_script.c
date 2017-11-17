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
}

static void			fork_child(int fd_master, int fd_slave, t_env *env)
{
	int				rc;
	char			*args[2];
	struct termios	slave_orig_term_settings;
	struct termios	new_term_settings;

	close(fd_master);
	rc = tcgetattr(fd_slave, &slave_orig_term_settings);
	new_term_settings = slave_orig_term_settings;
	cfmakeraw(&new_term_settings);
	tcsetattr(fd_slave, TCSANOW, &new_term_settings);
	close(0);
	close(1);
	close(2);
	dup(fd_slave);
	dup(fd_slave);
	dup(fd_slave);
	close(fd_slave);
	setsid();
	ioctl(0, TIOCSCTTY, 1);
	args[0] = "zsh";
	args[1] = NULL;
	rc = execvp(env->bash, args);
}

void				ft_script(t_env *env)
{
	int				fd_master;
	int				fd_slave;
	int				fd_file;

	if (env->opt_a == 1)
		fd_file = open(env->filename, O_CREAT | O_WRONLY | O_APPEND, OPEN_MODE);
	else
		fd_file = open(env->filename, O_CREAT | O_WRONLY | O_TRUNC, OPEN_MODE);
	if (create_pty(&fd_master, &fd_slave) == -1)
		return ;
	if (!fd_file || !fd_master || !fd_slave)
		return ;
	if (fork())
		fork_parent(fd_master, fd_slave, fd_file);
	else
		fork_child(fd_master, fd_slave, env);
	close(fd_file);
}