#include "../includes/ft_script.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * TODO
 * re-code :
 * - openpt
 * - granpt
 * - unlockpt
 * - ptsname
**/

int        create_pty(int *fd_master, int *fd_slave)
{
    //ouvre un pty et return le fd
    *fd_master =  ft_posix_openpt(O_RDWR);
    if (*fd_master < 0)
        return (-1);
    //change les droits du pty
    if ((grantpt(*fd_master)) != 0)
        return (-1);
    //deverouille pty
    if ((unlockpt(*fd_master)) != 0)
        return (-1);
    //ouverture tu pty esclave
    *fd_slave = open(ptsname(*fd_master), O_RDWR);
    return (0);
}