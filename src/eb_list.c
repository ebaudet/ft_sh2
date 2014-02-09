/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 22:45:25 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/05 01:24:39 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_sh2.h"

void	eb_new_elt(t_data *d, t_list **list, char c)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	new->c = c;
	new->prev = NULL;
	if ((!d->list || !*d->list) && !(new->next = NULL))
	{
		d->list = ((!d->list) ? (t_list **)malloc(sizeof(t_list *)) : d->list);
		*d->list = new;
		d->cursor = new;
	}
	else if (*list && !d->cursor)
	{
		d->cursor = new;
		(*list)->prev = new;
		new->next = *list;
		*list = new;
	}
	else
	{
		new->next = d->cursor->next;
		new->prev = d->cursor;
		d->cursor->next = new;
		d->cursor = new;
	}
}

void	eb_free_list(t_list **list)
{
	t_list	*tmp;

	if (!list || *list == NULL)
		return ;
	tmp = *list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free(tmp->prev);
	}
	free(tmp);
}

int		eb_del_elt(t_data *d)
{
	t_list	*tmp;

	if (!d->list || !*d->list || !d->cursor)
		return (0);
	else if (d->cursor == *d->list)
	{
		*d->list = (*(d->list))->next;
		if (d->cursor->next)
			d->cursor->next->prev = NULL;
		free(d->cursor);
		d->cursor = NULL;
	}
	else
	{
		if (d->cursor->prev)
			d->cursor->prev->next = d->cursor->next;
		if (d->cursor->next)
			d->cursor->next->prev = d->cursor->prev;
		tmp = d->cursor;
		d->cursor = d->cursor->prev;
		free(tmp);
	}
	return (0);
}
