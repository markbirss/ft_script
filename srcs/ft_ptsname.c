#include "../includes/ft_script.h"
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/param.h>//MAXPATHLEN

char                *ft_ptsname(int fd)
{
    static char     ptsnamebuf[MAXPATHLEN];
    char            *retval;
	struct stat     sbuf;
    
    retval = NULL;
    if (ioctl(fd, TIOCPTYGNAME, ptsnamebuf) == -1)
        return (NULL);
    if (stat(ptsnamebuf, &sbuf) == 0)
        retval = ptsnamebuf;
    return (retval);
}