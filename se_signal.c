/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 18:23:40 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 19:06:21 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "ft_select.h"

static void		se_sigcont(void)
{
	t_select		*tmp;
	struct termios	*new;

	tmp = sing_select(NULL);
	new = sing_newterm(NULL);
	tcsetattr(0, 0, new);
	tputs(tgetstr("vi", NULL), 1, tputs_putchar);
	tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	se_print_list(tmp);
	signal(SIGTSTP, treat_signal);
}


static void		se_sigstp(void)
{
	char			sim[2];
	struct termios	*old;
	struct termios	*new;

	old = sing_oldterm(NULL);
	new = sing_newterm(NULL);
	sim[0] = new->c_cc[VSUSP];
	sim[1] = 0;
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	tputs(tgetstr("te", NULL), 1, tputs_putchar);
	tcsetattr(0, 0, old);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, sim);
}

static void		se_sigredim(void)
{
	struct winsize		win;
	t_select			*tmp;

	ioctl(0, TIOCGWINSZ, &win);
	tmp = sing_select(NULL);
	tmp->win_l = (int)win.ws_row;
	tmp->win_c = (int)win.ws_col;
	tputs(tmp->cl_str, 1, tputs_putchar);
	se_print_list(tmp);
}

void			treat_signal(int sig)
{
	if (sig == SIGWINCH)
		se_sigredim();
	if (sig == SIGTSTP)
		se_sigstp();
	if (sig == SIGCONT)
		se_sigcont();
	if (sig == SIGINT || sig == SIGTERM || sig == SIGTTIN)
		se_sigkill();
}

void			se_checksignal(void)
{
	signal(SIGWINCH, &treat_signal);
	signal(SIGTSTP, &treat_signal);
	signal(SIGCONT, &treat_signal);
	signal(SIGINT, &treat_signal);
	signal(SIGTERM, &treat_signal);
	signal(SIGTTIN, &treat_signal);
}
