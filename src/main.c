/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 22:40:26 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/27 19:30:09 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_sh2.h"

int		eb_wait_for_it(t_data *d)
{
	ft_bzero(d->read_char, 5);
	while (!is_enter(d->read_char))
	{
		if (ft_isprint(d->read_char[0]))
			eb_new_elt(d, d->list, d->read_char[0]);
		if (is_del(d->read_char))
			eb_del_elt(d);
		eb_move_cursor(d);
		/*else
			printf("read_char[%d][%d][%d][%d][%d]\n", d->read_char[0],
				d->read_char[1], d->read_char[2], d->read_char[3], d->read_char[4]);
		*/
		eb_print_list(d, d->list, 1);
		ft_bzero(d->read_char, 5);
		read(0, d->read_char, 5);
	}
	eb_print_list(d, d->list, 0);
	tputs(tgetstr("sc", NULL), 1, eb_putchar);
	eb_press_enter(d);
	return (-1);
}

int		ft_get_cmd(t_data *data)
{
	/*get_next_line(0, &data->prompt);*/
	free(data->prompt);
	data->prompt = eb_list_to_string(data->list);

	data->av = ft_strsplit(data->prompt, ' ');
	if (data->av[0])
	{
		data->name_cmd = data->av[0];
		data->ac = eb_sizeenv(data->av);
		return (0);
	}
	return (-1);
}

int		main(int ac, char **av, char **env)
{
	t_data			*d;
	struct termios	*old;

	(void)ac;
	(void)av;
	eb_getsig();
	d = eb_get_data();
	old = eb_get_init_conf();
	d->env = eb_envcpy(env);
	if (d->env[0] == NULL)
		p_err("Pas d'environement", "", 0);
	if (tgetent(d->bp, getenv("TERM")) < 1)
		p_err("pas de terminal defini", "", 0);
	d->prompt = ft_strnew(1);
	eb_close();
	tputs(tgetstr("sc", NULL), 1, eb_putchar);
	eb_init();
	ft_putstr("$> Welcome ");
	ft_putstr(eb_getenv(d->env, "USER"));
	ft_putchar('\n');
	tputs(tgetstr("sc", NULL), 1, eb_putchar);
	while (ft_strcmp(d->prompt, "exit") != 0)
	{
		ft_putstr("t");
		if (eb_wait_for_it(d) == 0)
		{
			ft_exec_cmd(d);
			free(d->name_cmd);
		}
	}
	eb_envfree(d->env);
	return (0);
}
