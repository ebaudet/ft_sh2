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

#include <stdlib.h>
#include "ft_sh2.h"

int		ft_get_cmd(t_data *data)
{
	char	**tab;

	get_next_line(0, &data->prompt);
	tab = ft_strsplit(data->prompt, ' ');
	if (tab[0])
	{
		data->name_cmd = tab[0];
		data->argv = tab;
		return (0);
	}
	return (-1);
}

char	*ft_get_user(char **tab)
{
	char	*tmp;

	tmp = tab[4] + 5;
	return (tmp);
}

int		main(int ac, char **av, char **env)
{
	t_data		data;

	(void)ac;
	(void)av;
	data.env = env;
	if (data.env[0] == NULL)
		p_err("Pas d'environement", "", 0);
	data.prompt = ft_strnew(1);
	ft_putstr("$> Welcome ");
	ft_putstr(eb_getenv(data.env, "USER"));
	ft_putchar('\n');
	while (ft_strcmp(data.prompt, "exit") != 0)
	{
		ft_putstr("$> ");
		if (ft_get_cmd(&data) == 0)
		{
			ft_exec_cmd(&data);
			free(data.name_cmd);
		}
	}
	return (0);
}
