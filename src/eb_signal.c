/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 22:38:59 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/04 22:38:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_sh2.h"

/*void	eb_sig_resize(void)
{
	t_data		*d;

	d = eb_get_data();
	eb_get_winsize(d);
	eb_clear_screen(d);
	eb_print(d);
}*/

/*void	eb_sig_clear(void)
{
	t_data		*d;

	d = eb_get_data();
	eb_clear_screen(d);
}*/

/*void	eb_sig_fg(void)
{
	t_data		*d;

	d = eb_get_data();
	eb_init();
	eb_print(d);
	signal(SIGTSTP, eb_sig_action);
}*/

void	eb_sig_action(int s)
{
	t_data		*d;

	d = eb_get_data();
	/*if (s == SIGWINCH)
		eb_sig_resize();
	else if (s == SIGCONT)
		eb_sig_fg();*/
	/*else
	{*/
		/*eb_sig_clear();*/
		if (s == SIGTSTP)
		{
			eb_close();
			signal(SIGTSTP, SIG_DFL);
			ioctl(isatty(FD_STD_OUT), TIOCSTI, "\032");
		}
		else
		{
			eb_close();
			exit (0);
		}
	/*}*/
}

void	eb_getsig(void)
{
	/*signal(SIGTSTP, &eb_sig_action);
	signal(SIGINT, &eb_sig_action);
	signal(SIGWINCH, &eb_sig_action);
	signal(SIGTERM, &eb_sig_action);
	signal(SIGCONT, &eb_sig_action);
	signal(SIGQUIT, &eb_sig_action);*/
}