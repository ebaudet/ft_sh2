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
	char	**result;
	int		i;
	char	*tmp;

	if (eb_editenv(env, name, value) == -1)
	{
		result = (char **)malloc(sizeof(char *) * (eb_sizeenv(env) + 2));
		i = -1;
		while (env[++i])
			result[i] = ft_strdup(env[i]);
		tmp	= ft_strjoin(name, "=");
		result[i] = ft_strjoin(tmp, value);
		result[++i] = ft_strdup("");
		free(tmp);
		eb_envfree(env);
		return (result);
	}
	return (env);
}

char	**eb_delenv(char **env, char *name)
{
	char	**result;
	int		i;
	int		j;

	if (eb_getenv(env, name) == NULL)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * eb_sizeenv(env));
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (ft_strncmp(*(env + i), name, ft_strlen(name)) != 0)
		{
			result[j] = ft_strdup(env[i]);
			j++;
		}
	}
	return (result);
}
