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
	if (*list == NULL)
	{
		*list = new;
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
	d->cursor = new;
}

void	eb_free_list(t_list **list)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	tmp = *list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free(tmp->prev);
	}
	free(tmp);
}

void	eb_print_list(t_data *d, t_list **list)
{
	t_list	*tmp;

	tputs(tgetstr("ch", 0), 1, eb_putchar);
	tputs(tgetstr("dl", NULL), 1, eb_putchar);
	eb_putstr_term("$> ");
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp == d->cursor)
			tputs(tgetstr("us", NULL), 1, eb_putchar);
		eb_putchar_term(tmp->c);
		tputs(tgetstr("me", NULL), 1, eb_putchar);
		tmp = tmp->next;
	}
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
