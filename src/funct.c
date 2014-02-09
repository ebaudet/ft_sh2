/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 22:40:37 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/27 19:30:11 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_sh2.h"

int		ft_count_c(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

int		ft_exec(t_data *data)
{
	char	*tmp;
	char	**path;
	int		i;
	int		t;

	path = eb_get_path(data->env);
	i = 0;
	data->error = 0;
	if (execve(data->name_cmd, data->av, data->env) == -1)
		data->error = 1;
	while (path[i] != 0)
	{
		tmp = ft_strjoin(path[i], data->name_cmd);
		t = access(tmp, X_OK);
		if (execve(tmp, data->av, data->env) != -1)
			data->error = 0;
		free(tmp);
		i++;
	}
	if (t == -1 && ft_strcmp(data->name_cmd, "exit") != 0)
		p_err("command not found: ", data->name_cmd, NO_ERR);
	else if (data->error == 1 && ft_strcmp(data->name_cmd, "exit") != 0)
		p_err("permission denied: ", data->av[0], NO_ERR);
	return (0);
}

void	ft_exec_cmd_cd(t_data *data)
{
	char	*str;
	char	buff[PATH_MAX + 1];

	if (ft_strcmp(data->av[1], "-") == 0)
		data->av[1] = eb_getenv(data->env, "OLDPWD");
	else if (data->av[1][0]== '~')
		data->av[1] = ft_strjoin(eb_getenv(data->env, "HOME"), data->av[1] + 1);
	if (data->av[1])
	{
		if (access(data->av[1], X_OK) == -1)
			p_err("cd: permission denied: ", data->av[1], NO_ERR);
		else if ((chdir(data->av[1])) == -1)
			p_err("cd: no such file or directory: ", data->av[1], NO_ERR);
		else
		{
			eb_editenv(data->env, "OLDPWD", eb_getenv(data->env, "PWD"));
			eb_editenv(data->env, "PWD", getcwd(buff, PATH_MAX + 1));
		}
	}
	else
	{
		chdir(str = ft_strsplit(data->env[3], '=')[1]);
		free(str);
	}
}

int		ft_exec_cmd2(t_data *data)
{
	if (ft_strcmp(data->name_cmd, "cd") == 0)
		ft_exec_cmd_cd(data);
	else if (ft_strcmp(data->name_cmd, "setenv") == 0)
	{
		if (data->ac != 3)
		{
			p_err(data->av[0], ": no many argument", NO_ERR);
			return (0);
		}
		data->env = eb_newenv(data->env, data->av[1], data->av[2]);
	}
	else if (ft_strcmp(data->name_cmd, "unsetenv") == 0)
	{
		if (data->ac != 2)
		{
			p_err(data->av[0], ": no many argument", NO_ERR);
			return (0);
		}
		data->env = eb_delenv(data->env, data->av[1]);
	}
	else
		data->pid = fork();
	return (1);
}

int		ft_exec_cmd(t_data *data)
{
	int		ret;

	if (ft_strcmp(data->name_cmd, "exit") == 0)
	{
		eb_close();
		eb_envfree(data->env);
		exit(0);
	}
	if (ft_exec_cmd2(data) == 0)
		return (0);
	if (data->pid == -1)
	{
		ft_putstr("fork : problem.");
		ft_putchar('\n');
	}
	if (data->pid == 0 && (ft_strcmp(data->name_cmd, "cd") != 0))
	{
		ft_exec(data);
		exit(0);
	}
	if (data->pid > 0)
		wait(&ret);
	return (0);
}
