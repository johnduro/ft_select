/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 18:27:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 19:07:01 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <termcap.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_select.h"

static t_arg		*se_setnode(char *name, int nb)
{
	t_arg		*new;

	if ((new = (t_arg *)malloc(sizeof(*new))) == NULL)
		ft_error(PROG, 1);
	new->name = ft_strdup(name);
	new->select = 0;
	new->nb = nb;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

static void			se_add_tolist(t_select *arg, char *name, int nb)
{
	t_select	*tmp;
	t_arg		*new;

	tmp = arg;
	new = se_setnode(name, nb);
	if (tmp->first == NULL)
	{
		tmp->first = new;
		tmp->last = new;
		tmp->size = nb;
		tmp->len = ft_strlen(name);
	}
	else
	{
		new->prev = tmp->last;
		tmp->last->next = new;
		tmp->last = new;
		new->next = NULL;
		tmp->size = nb;
		tmp->len = ft_isgreater(tmp->len, ft_strlen(name));
	}
}

static t_select		*se_init_arg(char **argv)
{
	int			i;
	t_select	*arg;

	i = 0;
	if ((arg = (t_select *)malloc(sizeof(*arg))) == NULL)
		ft_error(PROG, 1);
	se_set_arg(arg);
	se_get_tcaps(arg);
	argv++;
	while (*argv)
	{
		se_add_tolist(arg, *argv, i);
		i++;
		argv++;
	}
	sing_select(arg);
	return (arg);
}

static void			se_init_term(struct termios *term, struct termios *oldterm)
{
	char	*tname;

	if ((tname = getenv("TERM")) == NULL)
		ft_error(PROG, 2);
	tgetent(NULL, tname);
	tcgetattr(0, oldterm);
	sing_oldterm(oldterm);
	tcgetattr(0, term);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	sing_newterm(term);
	tcsetattr(0, 0, term);
	tputs(tgetstr("vi", NULL), 1, tputs_putchar);
}

int					main(int argc, char **argv)
{
	struct termios		term;
	struct termios		oldterm;
	t_select			*arg;
	int					ret;

	ret = 0;
	if (argc < 2)
		ft_error(SE_USAGE, 0);
	se_init_term(&term, &oldterm);
	arg = se_init_arg(argv);
	tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	ret = se_select(arg);
	tputs(tgetstr("te", NULL), 1, tputs_putchar);
	if (ret)
		se_print_ret(arg);
	se_close(&term, &oldterm);
	return (0);
}
