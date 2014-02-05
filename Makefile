# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/13 18:29:55 by ebaudet           #+#    #+#              #
#    Updated: 2014/01/13 18:29:55 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_sh2
FILES	= main.c funct.c print_error.c eb_data.c eb_env.c eb_env2.c\
		eb_list.c eb_is_key.c eb_is_key_arrow.c eb_term.c eb_tools.c\
		eb_signal.c
SRCS	= $(addprefix src/, $(FILES))
OBJS	= $(SRCS:src/%.c=.obj/%.o)
INC		= -I includes -I libft/includes
LIB_TERMCAT = -L /usr/lib -ltermcap
FLAGS	= -Wall -Wextra -Werror
LIB		= -L libft -lft

all: createfolder $(NAME)

$(NAME): $(OBJS) 
	make -C libft
	cc $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(LIB) $(LIB_TERMCAT)

.obj/%.o: src/%.c
	cc -c $< -o $@ $(FLAGS) $(INC)

createfolder:
	mkdir -p .obj

gdb:
	make -C libft
	cc -g $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) $(LIB_TERMCAT)
	gdb $(NAME)

clean:
	rm -rf .obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all gdb clean fclean re createfolder
