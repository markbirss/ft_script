#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include <stdlib.h>
# include "../libft/includes/libft.h"

typedef struct      s_env {
    char            *bash;
    char            *filename;
    char            *command;
    //options
    int             opt_a;
    int             opt_d;
    int             opt_f;
    int             opt_p;
    int             opt_q;
    int             opt_r;
    //bonus
    int             opt_k;
    int             opt_t;
}                   t_env;

void                ft_script(t_env *env);
int                 get_params(int ac, char **av, t_env **env);
void		        *ft_mmap(int size);
char	            *ft_mmap_strdup(const char *s1);
int                 create_pty(int *fd_master, int *fd_slave);
void                get_shell(t_env *env, char **envp);
int                 ft_posix_openpt(int flags);
#endif