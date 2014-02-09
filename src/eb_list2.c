/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 22:43:34 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/09 22:43:34 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdlib.h>
#include "ft_sh2.h"

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

void	eb_position_cursor(void)
{
	tputs(tgetstr("rc", NULL), 1, eb_putchar);
	tputs(tgetstr("cd", NULL), 1, eb_putchar);
	tputs(tgetstr("rc", NULL), 1, eb_putchar);
	eb_putstr_term("$> ");
}

void	eb_print_list(t_data *d, t_list **list, char curs)
{
	t_list	*tmp;

	eb_position_cursor();
	if ((!list || *list == NULL) && curs)
		eb_cursor(0, 0);
	else
	{
		tmp = *list;
		while (tmp != NULL)
		{
			if ((curs && d->cursor == NULL && tmp == *d->list)
				|| (d->cursor && tmp == d->cursor->next))
				eb_cursor(tmp->c, 1);
			else if (curs && d->cursor && d->cursor->next == NULL
				&& tmp->next == NULL)
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
