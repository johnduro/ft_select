/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 16:49:29 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/11 17:49:56 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

void		move_right(t_select *arg)
{
	if ((arg->current + (arg->win_l)) <= arg->size)
		arg->current = arg->current + (arg->win_l - 1);
}

void		move_left(t_select *arg)
{
	if ((arg->current - (arg->win_l)) >= 0)
		arg->current = (arg->current - arg->win_l) + 1;
}

void		move_up(t_select *arg)
{
	if (arg->current == 0)
		arg->current = arg->last->nb;
	else
		arg->current = arg->current - 1;
}

void		move_down(t_select *arg)
{
	if (arg->current == arg->last->nb)
		arg->current = 0;
	else
		arg->current = arg->current + 1;
}
