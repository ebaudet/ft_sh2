/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 22:40:32 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/27 19:29:47 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

/*
# include <unistd.h>

# include <errno.h>
# include <assert.h>
# include <sys/wait.h>
*/
# include <sys/types.h>
# include "libft.h"

# ifndef NO_ERR
#  define NO_ERR 42
# endif

# ifndef PATH_MAX
#  define PATH_MAX 512
# endif

typedef struct		s_data
{
	char			**argv;
	char			**env;
	char			*name_cmd;
	pid_t			pid;
	char			*prompt;
	char			error;
}					t_data;

/*
** main.c
*/
int		ft_get_cmd(t_data *data);
char	*ft_get_user(char **tab);

/*
** funct.c
*/
int		ft_count_c(char *str, char c);
char	**ft_get_path(char **tab);
int		ft_exec(t_data *data);
void	ft_exec_cmd_cd(t_data *data);
int		ft_exec_cmd(t_data *data);

/*
** print_error.c
*/
void	p_err(char *s1, char *s2, int error);

/*
** eb_env.c
*/
char	**eb_get_path(char **env);
char	*eb_getenv(char **env, char *name);
int		eb_editenv(char **env, char *name, char *value);

#endif
