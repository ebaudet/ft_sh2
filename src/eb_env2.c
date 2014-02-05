/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 02:54:52 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/05 02:54:52 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh2.h"

int		eb_editenv(char **env, char *name, char *value);
char	**eb_newenv(char **env, char *name, char *value);
char	**eb_delenv(char **env, char *name);

int		eb_editenv(char **env, char *name, char *value)
{
	int		i;
	char	loop;
	char	*tmp;

	i = 0;
	loop = 'y';
	while (*(env + i) != NULL && loop == 'y')
	{
		if (ft_strncmp(*(env + i), name, ft_strlen(name)) == 0)
		{
			/*free(env[i]);*/
			tmp = ft_strjoin(name, "=");
			env[i] = ft_strjoin(tmp, value);
			free(tmp);
			loop = 'n';
		}
		else
			i++;
	}
	if (loop == 'y')
		return (-1);
	return (0);
}

char	**eb_newenv(char **env, char *name, char *value)
{

}

char	**eb_delenv(char **env, char *name)
{

}
