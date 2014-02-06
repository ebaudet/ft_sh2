/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_is_key_arrow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 02:51:39 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/05 02:51:39 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_sh2.h"

int		is_arrow(char *buf)
{
	if (buf[0] == 27 && buf[1] == 91)
	{
		if (buf[2] == 65)
			return (UP);
		else if (buf[2] == 66)
			return (DOWN);
		else if (buf[2] == 68)
			return (LEFT);
		else if (buf[2] == 67)
			return (RIGHT);
	}
	return (NOT_ARROW);
}

int		eb_press_enter(t_data *d)
{
	t_cmd		*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->cmd = d->list;
	if (!d->cmd)
		d->cmd = (t_cmd **)malloc(sizeof(t_cmd *));
	if (*d->cmd == NULL)
		*d->cmd = cmd;
	else
		eb_add_first_cmd(d, cmd);
	d->list = NULL;
	d->cursor = NULL;
}

void	eb_add_first_cmd(t_data *d, t_cmd *cmd)
{
	(*(d->cmd))->prev = cmd;
	cmd->next = *(d->cmd);
	*d->cmd = cmd;
}

void	eb_arrow_up(t_data *d)
{
	t_cmd	*tmp

	if (!d->tmp.exist)
	{
		d->tmp.exist = 1;
		d->tmp.cursor = d->cursor;
		d->tmp.list = d->list;
		d->list = d->cmd->cmd;
		d->cursor = NULL
	}
	else
	{
		tmp = *d->cmd;
		while (tmp && tmp->cmd != d->list)
			tmp = tmp->prev;
		tmp = ((tmp != NULL) && (tmp->prev != NULL) ? tmp->prev : NULL);
		if (tmp)
		{
			d->list = tmp->cmd;
			d->cursor = tmp->cursor;
		}
	}
}

void	eb_arrow_down(t_data *d)
{
	t_cmd	*tmp;

	if (d->cmd)
	{
		tmp = *d->cmd;
		while (tmp && tmp->cmd != d->list)
			tmp = tmp->prev;
		if ((tmp != NULL) && (tmp->next != NULL))
			tmp	= tmp->next;
		else if ((tmp != NULL) && (tmp->next == NULL))
		{
			if (d->tmp.exist)
			{
				d->tmp.exist = 0;
				d->cursor = d->tmp.cursor;
				d->list = d->tmp.list;
			}
		}
	}
}

void	eb_move_cursor(t_data *d)
{
	if ((is_arrow(d->read_char) == LEFT) && d->cursor && d->list && *d->list)
		d->cursor = d->cursor->prev;
	if ((is_arrow(d->read_char) == RIGHT) && d->list && *d->list)
	{
		if (!d->cursor)
			d->cursor = *(d->list);
		else if (d->cursor && d->cursor->next)
			d->cursor = d->cursor->next;
	}
	if ((is_arrow(d->read_char) == UP) && d->cmd)
	{
		eb_arrow_up(d)
	}
	if ((is_arrow(d->read_char) == DOWN))
	{
		eb_arrow_down(d)
	}
}
