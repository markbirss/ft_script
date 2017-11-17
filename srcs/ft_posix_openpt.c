#include "../includes/ft_script.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int     ft_posix_openpt(int flags)
{
    return open("/dev/ptmx", flags);
}