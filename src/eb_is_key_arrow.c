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
