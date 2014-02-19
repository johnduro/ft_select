/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 15:53:52 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/11 18:53:02 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_error(const char *name, int code)
{
	char	*error_tab[3];

	error_tab[1] = "Out of memory";
	error_tab[2] = "Couldn't acces environment";
	write(2, "[error]: ", 9);
	if (name != NULL)
	{
		write(2, name, ft_strlen(name));
	}
	if (code != 0)
	{
		write(2, ": ", 2);
		write(2, error_tab[code], ft_strlen(error_tab[code]));
	}
	write(2, ".\n", 2);
	exit(code);
}
