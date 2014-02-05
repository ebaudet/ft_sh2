/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 00:32:40 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/05 00:32:40 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ft_sh2.h"

int		eb_putchar(int c)
{
	write(isatty(FD_STD_OUT), &c, 1);
	return (1);
}

int		eb_putchar_output(int c)
{
	write(1, &c, 1);
	return (1);
}

/*void	eb_clear_screen(t_data *d)
{
	int		i;

	i = -1;
	tputs(tgetstr("dm", NULL), 1, eb_putchar);
	while (++i < d->row)
		tputs(tgetstr("dl", NULL), 1, eb_putchar);
	tputs(tgetstr("ed", NULL), 1, eb_putchar);
	tputs(tgetstr("cl", NULL), 1, eb_putchar);
}*/

/*void	*eb_get_data(void)
{
	static t_data		*d = NULL;

	if (d == NULL)
		d = (t_data *)malloc(sizeof(t_data));
	return (d);
}*/

/*void	eb_get_winsize(t_data *d)
{
	struct winsize		w;

	ioctl(isatty(FD_STD_OUT), TIOCGWINSZ, &w);
	d->row = w.ws_row;
	d->col = w.ws_col;
}*/
