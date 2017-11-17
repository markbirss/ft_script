#include "../includes/ft_script.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * TODO
 * re-code :
 * - openpt OK
 * - granpt TODO
 * - unlockpt TODO
 * - ptsname NOT WORKING
**/

int        create_pty(int *fd_master, int *fd_slave)
{
    *fd_master =  ft_posix_openpt(O_RDWR);
    if (*fd_master < 0)
        return (-1);
    if ((ft_grantpt(*fd_master)) != 0)
        return (-1);
    if ((ft_unlockpt(*fd_master)) != 0)
        return (-1);
    if ((*fd_slave = open(ft_ptsname(*fd_master), O_RDWR)) == -1)
        return (-1);
    return (0);
}