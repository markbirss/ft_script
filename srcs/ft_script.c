#include "../includes/ft_script.h"
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//select
#include <sys/select.h>
#include <unistd.h>
#include <sys/ioctl.h>
//tcsetattr
#include <termios.h>

static int read_master(int fd_master, int fd_file, fd_set fd_in)
{
    int rc;
    char input[150];
    
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

static int  read_user(int fd_master, int fd_file, fd_set fd_in)
{
    int rc;
    char input[150];
    
    (void)fd_file;    
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

static void fork_parent(int fd_master, int fd_slave, int fd_file)
{
    int rc;
    fd_set fd_in;

    close(fd_slave);
    while (42)
    {
        FD_ZERO(&fd_in);
        FD_SET(0, &fd_in);
        FD_SET(fd_master, &fd_in);
        rc = select(fd_master + 1, &fd_in, NULL, NULL, NULL); //select surveille les fd, attend quils soient dispo
        if (rc == -1)
            return;
        else if (rc > 0)
        {
            if (read_user(fd_master, fd_file, fd_in) == -1)
                return ;
            if (read_master(fd_master, fd_file, fd_in) == -1)
                return ;
        }
    }
}

static void fork_child(int fd_master, int fd_slave, t_env *env)
{
    int rc;
    char *args[2];
    struct termios slave_orig_term_settings; // Saved terminal settings
    struct termios new_term_settings;        // Current terminal settings

    close(fd_master);
    rc = tcgetattr(fd_slave, &slave_orig_term_settings);
    // Sauvegarde des parametre par defaut du PTY esclave
    // Positionnement du PTY esclave en mode RAW
    new_term_settings = slave_orig_term_settings;
    cfmakeraw(&new_term_settings);
    tcsetattr(fd_slave, TCSANOW, &new_term_settings);
    // Le cote esclave du PTY devient l'entree et les sorties standards du fils
    close(0);// Fermeture de l'entrée standard (terminal courant)
    close(1);// Fermeture de la sortie standard (terminal courant)
    close(2);// Fermeture de la sortie erreur standard (terminal courant)
    dup(fd_slave);// Le PTY devient l'entree standard (0)
    dup(fd_slave);// Le PTY devient la sortie standard (1)
    dup(fd_slave);// Le PTY devient la sortie erreur standard (2)
    close(fd_slave);// Maintenant le descripteur de fichier original n'est plus utile
    setsid();// Le process courant devient un leader de session
    // Comme le process courant est un leader de session, La partie esclave du PTY devient son terminal de contrôle
    // (Obligatoire pour les programmes comme le shell pour faire en sorte qu'ils gerent correctement leurs sorties)
    ioctl(0, TIOCSCTTY, 1);
    args[0] = "zsh";
    args[1] = NULL;
    rc = execvp(env->bash, args);
}

void ft_script(t_env *env)
{
    int fd_master;
    int fd_slave;
    int fd_file;

    fd_file = open("./typescript", O_CREAT | O_WRONLY | O_TRUNC);
    if (create_pty(&fd_master, &fd_slave) == -1)
        return;
    if (!fd_file || !fd_master || !fd_slave)
        return;
    if (fork())
        fork_parent(fd_master, fd_slave, fd_file);
    else
        fork_child(fd_master, fd_slave, env);
    close(fd_file);
}