/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_kill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 16:45:08 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 19:06:31 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <termcap.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_select.h"

void		se_sigkill(void)
{
	struct termios		*old;
	struct termios		*term;

	term = sing_newterm(NULL);
	old = sing_oldterm(NULL);
	tputs(tgetstr("te", NULL), 1, tputs_putchar);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	tcsetattr(0, 0, old);
	write(2, "Goodbye !!\n", 11);
	exit(0);
}
