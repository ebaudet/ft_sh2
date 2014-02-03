/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 15:03:14 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/27 19:30:06 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_sh2.h"

void	p_err(char *s1, char *s2, int error)
{
	ft_putstr(s1);
	ft_putstr(s2);
	ft_putstr("\n");
	if (error != NO_ERR)
		exit(error);
}
