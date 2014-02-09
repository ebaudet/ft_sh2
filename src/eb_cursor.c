/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 15:28:52 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/07 15:28:52 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh2.h"

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
		eb_arrow_up(d);
	}
	if ((is_arrow(d->read_char) == DOWN))
	{
		eb_arrow_down(d);
	}
}
