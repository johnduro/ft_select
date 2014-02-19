/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 18:10:55 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 16:44:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "libft.h"
#include "ft_select.h"

#include <stdio.h> /**/

void	se_do_print(t_arg *tmp, t_select *arg)
{
	int		y;
	int		c;

	c = 0;
	while (tmp != NULL)
	{
		y = 1;
		while (y < arg->win_l && tmp != NULL)
		{
			tputs(tgoto(arg->cm_str, (arg->len + 2) * c, y), 1, tputs_putchar);
			if (tmp->nb == arg->current)
				tputs(arg->us_str, 1, tputs_putchar);
			if (tmp->select == 1)
				tputs(arg->so_str, 1, tputs_putchar);
			ft_putstr_fd(tmp->name, sing_tty());
			tputs(arg->ue_str, 1, tputs_putchar);
			tputs(arg->se_str, 1, tputs_putchar);
			tmp = tmp->next;
			y++;
		}
		c++;
	}
}

void	se_printhead(t_select *arg)
{
	int		i;

	i = 0;
	if (arg->win_c > 18)
	{
		tputs(tgoto(arg->cm_str, 0, 0), 1, tputs_putchar);
		tputs(arg->so_str, 1, tputs_putchar);
		write(sing_tty(), "ft_select", 9);
		while (i < (arg->win_c - 16))
		{
			write(sing_tty(), " ", 1);
			i++;
		}
		write(sing_tty(), "mle-roy", 7);
		tputs(arg->se_str, 1, tputs_putchar);
	}
}

int		se_checkforprint(t_select *arg)
{
	int		last_x;

	last_x = 0;
	last_x = ((arg->len) + 2) * ((arg->last->nb) / (arg->win_l));
	if ((last_x + arg->len) > arg->win_c)
	{
		tputs(arg->vb_str, 1, tputs_putchar);
		tputs(tgoto(arg->cm_str, 0, 1), 1, tputs_putchar);
		write(sing_tty(), "window too small !!", 19);
		return (1);
	}
	return (0);
}
