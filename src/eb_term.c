/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 22:43:47 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/04 22:43:47 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_sh2.h"

struct termios	*eb_get_init_conf(void)
{
	static struct termios	*old = NULL;

	if (old == NULL)
	{
		old = (struct termios *)malloc(sizeof(struct termios));
		if (tcgetattr(0, old) != 0)
			ft_error("bad tcgetattr");
	}
	return (old);
}

void			eb_init(void)
{
	struct termios		term;

	if (tcgetattr(0, &term) != 0)
		ft_error("bad tcgetattr");
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		ft_error("bad tcsetattr");
	tputs(tgetstr("ti", NULL), 1, eb_putchar);
	tputs(tgetstr("vi", NULL), 1, eb_putchar);
}

void			eb_close(void)
{
	struct termios			*old;

	old = eb_get_init_conf();
	tcsetattr(0, TCSANOW, old);
	/*tputs(tgetstr("cl", NULL), 1, eb_putchar);*/
	tputs(tgetstr("ve", NULL), 1, eb_putchar);
	tputs(tgetstr("te", NULL), 1, eb_putchar);
}

void			eb_putchar_term(char c)
{
	ft_putchar_fd(c, isatty(FD_STD_OUT));
}

void			eb_putstr_term(char *str)
{
	ft_putstr_fd(str, isatty(FD_STD_OUT));
}
