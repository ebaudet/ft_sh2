/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_key_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 15:30:38 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/07 15:30:38 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh2.h"

int		eb_press_enter(t_data *d)
{
	int		result;

	result = -1;
	eb_add_in_history(d);
	if (d->list)
		result = ft_get_cmd(d);
	eb_history(d);
	d->cursor = NULL;
	d->list = NULL;
	d->tmp.exist = 0;
	return (result);
}

void	eb_arrow_up(t_data *d)
{
	if (!d->tmp.exist)
	{
		d->tmp.exist = 1;
		d->tmp.cursor = d->cursor;
		d->tmp.list = d->list;
		d->history = *(d->cmd);
		d->list = d->history->cmd;
		d->cursor = NULL;
	}
	else
	{
		if (d->history && d->history->prev != NULL)
		{
			d->history = d->history->prev;
			d->list = d->history->cmd;
			d->cursor = NULL;
		}
	}
}

void	eb_arrow_down(t_data *d)
{
	if (d->cmd)
	{
		if (d->history)
		{
			if (d->history->next)
			{
				d->history = d->history->next;
				d->list = d->history->cmd;
				d->cursor = NULL;
			}
			else
			{
				d->history = NULL;
				d->tmp.exist = 0;
				d->cursor = d->tmp.cursor;
				d->list = d->tmp.list;
			}
		}
	}
}
