/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 19:07:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 19:07:11 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <termcap.h>
#include "libft.h"
#include "ft_select.h"

void	se_print_ret(t_select *arg)
{
	t_arg	*tmp;
	int		check;

	check = 0;
	tmp = arg->first;
	while (tmp != NULL)
	{
		if (tmp->select == 1)
		{
			if (check > 0)
				write(1, " ", 1);
			write(1, tmp->name, ft_strlen(tmp->name));
			check++;
		}
		tmp = tmp->next;
	}
	if (check)
		write(1, "\n", 1);
}


int		tputs_putchar(int c)
{
	write(sing_tty(), &c, 1);
	return (1);
}

void	se_close(struct termios *term, struct termios *old)
{
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	tcsetattr(0, 0, old);
	exit(0);
}
