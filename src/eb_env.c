/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 16:44:22 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/03 16:44:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_sh2.h"

char	**eb_get_path(char **env)
{
	char	**path;
	char	**tmp;
	int		i;
	int		j;

	if((tmp = ft_strsplit(eb_getenv(env, "PATH"), ':')) == NULL)
		return (NULL);
	i = ft_count_c(eb_getenv(env, "PATH"), ':') + 1;
	if ((path = (char **)malloc(i * sizeof(char *))) == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		if ((path[j] = ft_strjoin(tmp[j], "/")) == NULL)
			return (NULL);
		free(tmp[j]);
		j++;
	}
	path[i] = NULL;
	free(tmp);
	return (path);
}

char	*eb_getenv(char **env, char *name)
{
	int		i;
	char	loop;

	i = 0;
	loop = 'y';
	while (*(env + i) != NULL && loop == 'y')
	{
		if (ft_strncmp(*(env + i), name, ft_strlen(name)) == 0)
			loop = 'n';
		else
			i++;
	}
	if (loop == 'y')
		return (NULL);	
	return (*(env + i) + ft_strlen(name) + 1);
}

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
