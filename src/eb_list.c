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

	/*new = (t_list *)malloc(sizeof(t_list));
	new->c = c;
	if (!d->list || *d->list == NULL)
	{
		if (!d->list)
			d->list = (t_list **)malloc(sizeof(t_list *));
		*d->list = new;
		d->cursor = new;
		new->next = NULL;
		new->prev = NULL;
		return ;
	}
	new->next = d->cursor->next;
	new->prev = d->cursor;
	if (d->cursor->next != NULL)
		d->cursor->next->prev = new;
	d->cursor->next = new;
	d->cursor = new;*/

	new = (t_list *)malloc(sizeof(t_list));
	new->c = c;
	new->next = NULL;
	new->prev = NULL;
	if (!d->list || !*d->list)
	{
		if (!d->list)
			d->list = (t_list **)malloc(sizeof(t_list *));
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
		if (d->cursor->next)
			d->cursor->next->prev = new;
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

	/*if (*d->list == NULL)
		return (0);
	if (elt->next == NULL)
	{
		if (*d->list == elt)
			*list = NULL;
		free(elt);
		d->cursor = NULL;
		return (0);
	}
	if (*d->list == elt)
		*d->list = elt->next;
	elt->prev->next = elt->next;
	elt->next->prev = elt->prev;
	d->cursor = elt->prev;
	free(elt);*/

}

void	eb_cursor(char c, char border)
{
	if (border == 0)
	{
		if (c)
			eb_putchar_term(c);
		tputs(tgetstr("mr", NULL), 1, eb_putchar);
		eb_putchar_term(' ');
	}
	else
	{
		tputs(tgetstr("mr", NULL), 1, eb_putchar);
		eb_putchar_term(c);
	}
}

void	eb_print_list(t_data *d, t_list **list, char curs)
{
	t_list	*tmp;

	tputs(tgetstr("rc", NULL), 1, eb_putchar);
	tputs(tgetstr("cd", NULL), 1, eb_putchar);
	tputs(tgetstr("rc", NULL), 1, eb_putchar);
	eb_putstr_term("$> ");
	if (!list || *list == NULL)
	{
		if (curs)
			eb_cursor(0, 0);
	}
	else
	{
		tmp = *list;
		while (tmp != NULL)
		{
			if ((curs && d->cursor == NULL && tmp == *d->list)
				|| (d->cursor && tmp == d->cursor->next))
				eb_cursor(tmp->c, 1);
			else if (curs && d->cursor && d->cursor->next == NULL && tmp->next == NULL)
				eb_cursor(tmp->c, 0);
			else
				eb_putchar_term(tmp->c);
			tputs(tgetstr("me", NULL), 1, eb_putchar);
			tmp = tmp->next;
		}
	}
	if (!curs)
		eb_putchar_term('\n');
}

char	*eb_list_to_string(t_list **list)
{
	char	*str;
	int		i;
	t_list	*tmp;

	tmp = *list;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	tmp = *list;
	i = 0;
	while (tmp != NULL)
	{
		str[i] = tmp->c;
		i++;
		tmp = tmp->next;
	}
	str[i] = '\0';
	return (str);
}
