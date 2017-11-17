#include "../includes/ft_script.h"
#include <sys/ioctl.h>

int     ft_grantpt(int fd)
{
    return ioctl(fd, TIOCPTYGRANT);
}