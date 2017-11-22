#include "../includes/ft_script.h"
#include <termios.h>
#include <sys/ioctl.h>

/**
 * lflags local mode
 * ICANON Active le mode canonique (erase & kill & NL for read) 
 * ECHO Effectuer un écho des caractères saisis.
 * ISIG Lorsqu'un caractère INTR, QUIT, SUSP ou DSUSP arrive, engendrer le signal correspondant.
 * \(0_0)/
 * iflags : entry mode
 * IXON Valider le contrôle de flux XON/XOFF en sortie.
 * IGNCR Ignorer CR en entrée.
 * ICRNL Convertir CR en NL en entrée, sauf si IGNCR est indiqué.
 * INLCR Convertir NL en CR en entrée.
 **/

void        set_raw_mode(t_env *env)
{
	struct termios	term;
    
    ft_tcgetattr(0, &term);
    env->saved_term = term;
    term.c_lflag &= ~(ICANON | ECHO | ISIG);
    term.c_iflag &= ~(IXON | INLCR | IGNCR | ICRNL);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    ft_tcsetattr(0, &term);
}