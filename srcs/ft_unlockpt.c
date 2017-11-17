#include "../includes/ft_script.h"
#include <sys/ioctl.h>

int ft_unlockpt(int fd)
{
    return ioctl(fd, TIOCPTYUNLK);    
}