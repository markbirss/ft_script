#include "../includes/ft_script.h"
#include <sys/ioctl.h>

/**
 * tcsetattr() fixe les paramètres du terminal
 * (à moins que le matériel sous-jacent ne le prenne pas en charge)
 * en lisant la structure termios pointée par termios_p.
 * optional_actions précise quand les changements auront lieu :
 **/

int			ft_tcsetattr(int fd, struct termios *t)
{
	return (ioctl(fd, TIOCSETA, t));
}