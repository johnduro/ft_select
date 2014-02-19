/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 20:45:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/12 19:29:25 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include <termcap.h>

# define SE_USAGE "Usage : ./ft_select stuff_1 etc..."
# define PROG "ft_select"

typedef struct			s_arg
{
	char				*name;
	char				select;
	int					nb;
	struct s_arg		*prev;
	struct s_arg		*next;
}						t_arg;

typedef struct 			s_select
{
	t_arg			*first;
	t_arg			*last;
	int				size;
	int				len;
	int				current;
	int				win_l;
	int				win_c;
	struct termios	old_t;
	struct termios	new_t;
	char			*cl_str;
	char			*us_str;
	char			*so_str;
	char			*ue_str;
	char			*se_str;
	char			*cm_str;
	char			*vb_str;
}						t_select;

void			se_set_arg(t_select *arg);
void			ft_error(const char *name, int code);
int				se_select(t_select *arg);
void			se_get_tcaps(t_select *arg);
int				sing_tty(void);
t_select		*sing_select(t_select *new);
struct termios	*sing_oldterm(struct termios *term);
struct termios	*sing_newterm(struct termios *term);
void			se_printhead(t_select *arg);
int				se_print_list(t_select *arg);
void			move_right(t_select *arg);
void			move_left(t_select *arg);
void			move_up(t_select *arg);
void			move_down(t_select *arg);
void			se_checkdel(char *buf, t_select *arg);
void			se_print_ret(t_select *arg);
int				se_cursinwin(t_select *arg, t_arg *current);
int				se_checkforprint(t_select *arg);
int				tputs_putchar(int c);
void			se_do_print(t_arg *tmp, t_select *arg);
void			se_checksignal(void);
void			treat_signal(int sig);
void			se_close(struct termios *term, struct termios *old);
void			se_sigkill(void);
void			se_selectall(char *buf, t_select *arg);
void			se_un_selectall(char *buf, t_select *arg);
void			se_inverse(char *buf, t_select *arg);

#endif /* !FT_SELECT_H */
