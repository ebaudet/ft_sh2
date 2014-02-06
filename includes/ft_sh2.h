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


# define FD_STD_OUT 1
# define FD_STD_ERR 2

# define NOT_ARROW 0
# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4

typedef struct		s_list
{
	char			c;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct		s_cmd
{
	t_list			**cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_tmp
{
	char			exist;
	t_list			*cursor;
	t_list			**list;
}					t_tmp;

typedef struct		s_data
{
	char			**av;
	int				ac;
	char			bp[1024];
	char			read_char[5];
	char			**env;
	char			*name_cmd;
	pid_t			pid;
	char			*prompt;
	char			error;
	t_list			*cursor;
	t_list			**list;
	t_cmd			**cmd;
	t_tmp			tmp;
}					t_data;

/*
** main.c
*/
int				eb_wait_for_it(t_data *data);
int				ft_get_cmd(t_data *data);

/*
** funct.c
*/
int				ft_count_c(char *str, char c);
int				ft_exec(t_data *data);
void			ft_exec_cmd_cd(t_data *data);
int				ft_exec_cmd(t_data *data);

/*
** print_error.c
*/
void			p_err(char *s1, char *s2, int error);
void			ft_error(char *msg);

/*
** eb_data.c
*/
void			*eb_get_data(void);

/*
** eb_env.c
*/
char			**eb_get_path(char **env);
char			*eb_getenv(char **env, char *name);
int				eb_sizeenv(char **env);
char			**eb_envcpy(char **env);
int				eb_envfree(char **env);

/*
** eb_env2.c
*/
int				eb_editenv(char **env, char *name, char *value);
char			**eb_newenv(char **env, char *name, char *value);
char			**eb_delenv(char **env, char *name);

/*
** eb_list.c
*/
void			eb_move_cursor(t_data *d);
void			eb_new_elt(t_data *d, t_list **list, char c);
void			eb_free_list(t_list **list);
int				eb_del_elt(t_data *d);
void			eb_print_list(t_data *d, t_list **list, char curs);
char			*eb_list_to_string(t_list **list);

/*
** eb_is_key.c
*/
int				is_space(char *buf);
int				is_enter(char *buf);
int				is_del(char *buf);
int				is_delete(char *buf);
int				is_esc(char *buf);

/*
** eb_is_key_arrow.c
*/
int				is_arrow(char *buf);

/*
** eb_term.c
*/
struct termios	*eb_get_init_conf(void);
void			eb_init(void);
void			eb_close(void);
void			eb_putchar_term(char c);
void			eb_putstr_term(char *str);

/*
** eb_tools.c
*/
int				eb_putchar(int c);
int				eb_putchar_output(int c);
/*void			eb_clear_screen(t_data *d);*/
/*void			*eb_get_data(void);*/
/*void			eb_get_winsize(t_data *d);*/

/*
** eb_signal.c
*/
/*void			eb_sig_resize(void);*/
/*void			eb_sig_clear(void);*/
/*void			eb_sig_fg(void);*/
void			eb_sig_action(int s);
void			eb_getsig(void);

#endif
