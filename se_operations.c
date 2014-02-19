/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 18:36:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 19:31:49 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <termcap.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "ft_select.h"
#include "libft.h"

static int		se_get_pos(char *buf, t_select *arg)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		move_right(arg);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		move_left(arg);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		move_up(arg);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		move_down(arg);
	return (0);
}

static void		se_checkmod(char *buf, t_select *arg)
{
	t_arg	*tmp;

	tmp = arg->first;
	if (buf[0] == 32 && buf[1] == 0 && buf[2] == 0)
	{
		while (tmp != NULL)
		{
			if (arg->current == tmp->nb)
			{
				if (tmp->select == 1)
					tmp->select = 0;
				else
				{
					tmp->select = 1;
					if (arg->current != arg->last->nb)
						arg->current = arg->current + 1;
				}
				return ;
			}
			tmp = tmp->next;
		}
	}
}


static void		se_mod_list(char *buf, t_select *arg)
{
	se_get_pos(buf, arg);
	se_checkmod(buf, arg);
	se_checkdel(buf, arg);
	se_selectall(buf, arg);
	se_un_selectall(buf, arg);
	se_inverse(buf, arg);
}

int				se_print_list(t_select *arg)
{
	t_arg		*tmp;

	tmp = arg->first;
	se_printhead(arg);
	if (tmp == NULL)
		return (1);
	if (se_checkforprint(arg))
		return (0);
	se_do_print(tmp, arg);
	return (0);
}

int				se_select(t_select *arg)
{
	char	buf[4] = {0};

	se_checksignal();
	while (42)
	{
		tputs(arg->cl_str, 1, tputs_putchar);
		if (se_print_list(arg))
			return (0);
		buf[1] = 0;
		buf[2] = 0;
		read(0, buf, 3);
		if (buf[0] == 27 && buf[1] == 0 && buf[2] == 0)
			return (0);
		if (buf[0] == 10 && buf[1] == 0 && buf[2] == 0)
			return (1);
		se_mod_list(buf, arg);
	}
	return (0);
}
