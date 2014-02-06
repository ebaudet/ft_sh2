/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 02:52:27 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/05 02:52:27 by ebaudet          ###   ########.fr       */
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

int		eb_sizeenv(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**eb_envcpy(char **env)
{
	char	**env_cpy;
	int		i;

	env_cpy = (char **)malloc(sizeof(char *) * (eb_sizeenv(env) + 1));
	i = -1;
	while (env[++i])
		env_cpy[i] = ft_strdup(env[i]);
	env_cpy[i] = ft_strdup("");
	return (env_cpy);
}

int		eb_envfree(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env[i]);
	free(env);
	return (0);
}
