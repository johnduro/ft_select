/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_delelem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 19:11:52 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/11 17:09:38 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_select.h"

static void		se_freenode(t_arg *node)
{
	free(node->name);
	free(node);
}


static void		se_delnode(t_select *arg, t_arg *node)
{
	if (node == arg->first)
	{
		if (node->next != NULL)
		{
			arg->first = node->next;
			node->next->prev = NULL;
		}
		else
		{
			arg->first = NULL;
			return ;
		}
	}
	else if (node != arg->last)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else
	{
		arg->last = node->prev;
		node->prev->next = NULL;
		arg->current = arg->current - 1;
	}
}

void			se_checkdel(char *buf, t_select *arg)
{
	t_arg	*tmp;
	t_arg	*save;
	int		check;

	check = 0;
	save = NULL;
	tmp = arg->first;
	if ((buf[0] == 126 || buf[0] == 127) && buf[1] == 0 && buf[2] == 0)
	{
		while (tmp != NULL)
		{
			if (tmp->nb == arg->current)
			{
				se_delnode(arg, tmp);
				arg->size = arg->size - 1;
				save = tmp;
				check = 1;
			}
			if (check == 1)
				tmp->nb = (tmp->nb) - 1;
			tmp = tmp->next;
		}
		if (save)
			se_freenode(save);
	}
}
