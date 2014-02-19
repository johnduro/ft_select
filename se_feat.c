/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_feat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 19:11:20 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 19:34:34 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		se_selectall(char *buf, t_select *arg)
{
	t_arg		*tmp;

	if (buf[0] == 97 && buf[1] == 0 && buf[2] == 0)
	{
		tmp = arg->first;
		while (tmp)
		{
			if (tmp->select == 0)
				tmp->select = 1;
			tmp = tmp->next;
		}
	}
}

void		se_un_selectall(char *buf, t_select *arg)
{
	t_arg		*tmp;

	if (buf[0] == 115 && buf[1] == 0 && buf[2] == 0)
	{
		tmp = arg->first;
		while (tmp)
		{
			if (tmp->select == 1)
				tmp->select = 0;
			tmp = tmp->next;
		}
	}
}

void		se_inverse(char *buf, t_select *arg)
{
	t_arg		*tmp;

	if (buf[0] == 105 && buf[1] == 0 && buf[2] == 0)
	{
		tmp = arg->first;
		while (tmp)
		{
			if (tmp->select == 0)
				tmp->select = 1;
			else if (tmp->select == 1)
				tmp->select = 0;
			tmp = tmp->next;
		}
	}
}
