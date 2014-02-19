/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_set_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 15:45:52 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/11 17:16:43 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "ft_select.h"
#include "libft.h"

void		se_get_tcaps(t_select *arg)
{
	arg->cl_str = tgetstr("cl", NULL);
	arg->us_str = tgetstr("us", NULL);
	arg->so_str = tgetstr("so", NULL);
	arg->ue_str = tgetstr("ue", NULL);
	arg->se_str = tgetstr("se", NULL);
	arg->cm_str = tgetstr("cm", NULL);
	arg->vb_str = tgetstr("vb", NULL);
}

void		se_set_arg(t_select *arg)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	arg->first = NULL;
	arg->last = NULL;
	arg->size = 0;
	arg->len = 0;
	arg->current = 0;
	arg->win_l = (int)win.ws_row;
	arg->win_c = (int)win.ws_col;
}
