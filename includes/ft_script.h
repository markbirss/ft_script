/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:57:28 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/22 15:16:15 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include <stdlib.h>
# include <termios.h>
# include "../libft/includes/libft.h"

# define OPEN_FLAGS O_CREAT | O_WRONLY
# define OPEN_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

typedef struct		s_env {
	struct termios	saved_term;
	char			*filename;
	char			**command;
	int				cmd_size;
	int				opt_a;
	int				opt_d;
	int				opt_f;
	int				opt_p;
	int				opt_q;
	int				opt_r;
	int				opt_k;
	int				opt_t;
}					t_env;

void				ft_script(int fd_file, t_env *env);
int					open_file(t_env *env);
int					get_params(int ac, char **av, t_env *env);
void				*ft_mmap(int size);
char				*ft_mmap_strdup(const char *s1);
int					create_pty(int *fd_master, int *fd_slave);
void				get_shell(t_env *env, char **envp);
int					ft_posix_openpt(int flags);
char				*ft_ptsname(int fd);
int					ft_grantpt(int fd);
int					ft_unlockpt(int fd);
void				set_raw_mode(t_env *env);
int					ft_tcsetattr(int fd, struct termios *t);
int					ft_tcgetattr(int fd, struct termios *t);

#endif
