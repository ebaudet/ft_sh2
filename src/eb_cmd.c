/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 15:16:30 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/07 15:16:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_sh2.h"

void	eb_add_in_history(t_data *d)
{
	int		history;

	if (d->list && *d->list)
	{
		if ((history = open(".history", O_WRONLY | O_CREAT | O_APPEND, 0644))
			== -1)
			ft_error("Can't open .history");
		ft_putstr_fd(eb_list_to_string(d->list), history);
		ft_putstr_fd("\n", history);
		close(history);
	}
}

void	eb_free_cmd(t_data *d)
{
	t_cmd	*tmp;

	if (d->cmd && *d->cmd)
	{
		tmp = *d->cmd;
		while (tmp->prev)
		{
			tmp = tmp->prev;
			eb_free_list(tmp->next->cmd);
			free(tmp->next);
		}
		eb_free_list(tmp->cmd);
		free(tmp);
		*d->cmd = NULL;
		d->history = NULL;
	}
}

void	eb_history(t_data *d)
{
	int		history;
	char	*line;
	int		ret;

	eb_free_cmd(d);
	line = NULL;
	if ((history = open(".history", O_RDONLY | O_CREAT, 0644)) == -1)
		ft_error("Can't open .history");
	while ((ret = get_next_line(history, &line)) > 0)
	{
		eb_add_string_to_cmd(d, line);
		free(line);
	}
	close(history);
}

t_list	**eb_string_to_list(char *str)
{
	t_list	**list;
	int		i;
	t_list	*new;
	t_list	*tmp;

	list = (t_list **)malloc(sizeof(t_list *));
	*list = (t_list *)malloc(sizeof(t_list));
	new = *list;
	tmp = new;
	i = -1;
	while (str[++i])
	{
		new = ((new == NULL) ? (t_list *)malloc(sizeof(t_list)) : new);
		new->prev = ((new == tmp) ? NULL : tmp);
		new->next = NULL;
		tmp->next = ((tmp == new) ? NULL : new);
		tmp = new;
		new->c = str[i];
		new = new->next;
	}
	return (list);
}

void	eb_add_string_to_cmd(t_data *d, char *str)
{
	t_cmd		*new;

	if ((new = (t_cmd *)malloc(sizeof(t_cmd))) == NULL)
		ft_error("error malloc");
	new->next = NULL;
	new->prev = NULL;
	new->cmd = eb_string_to_list(str);
	if (!d->cmd)
	{
		d->cmd = NULL;
		if ((d->cmd = (t_cmd **)malloc(sizeof(t_cmd *))) == NULL)
			ft_error("error malloc");
	}
	if (!d->cmd || *d->cmd == NULL)
		*d->cmd = new;
	else
	{
		(*(d->cmd))->next = new;
		new->prev = *(d->cmd);
		*d->cmd = new;
	}
}
