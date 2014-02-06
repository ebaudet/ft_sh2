/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 22:41:07 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/04 22:41:07 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_sh2.h"

void	*eb_get_data(void)
{
	static t_data		*d = NULL;

	if (d == NULL)
	{
		d = (t_data *)malloc(sizeof(t_data));
		d->tmp.exist = 0;
		d->list = NULL;
	}
	return (d);
}
