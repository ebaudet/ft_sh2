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
FILES	= main.c funct.c print_error.c eb_env.c
SRCS	= $(addprefix src/, $(FILES))
OBJS	= $(SRCS:src/%.c=.obj/%.o)
INC		= -I includes -I libft/includes
FLAGS	= -Wall -Wextra -Werror
LIB		= -L libft -lft

all: $(NAME)

$(NAME): $(OBJS) 
	make -C libft
	cc $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) \
	-L /usr/X11/lib -lmlx -lXext -lX11

.obj/%.o: src/%.c
	mkdir -p .obj
	cc -c $< -o $@ $(FLAGS) $(INC)

gdb:
	make -C libft
	cc -g $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) \
	-L /usr/X11/lib -lmlx -lXext -lX11
	gdb $(NAME)

clean:
	rm -rf .obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all gdb clean fclean re
