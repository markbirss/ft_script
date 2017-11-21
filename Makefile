# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 13:59:57 by mfrisby           #+#    #+#              #
#    Updated: 2017/11/21 15:10:30 by mfrisby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ft_script

SRCS = 	srcs/main.c srcs/ft_script.c srcs/get_params.c srcs/ft_mmap.c \
		srcs/ft_mmap_strdup.c srcs/create_pty.c srcs/get_shell.c \
		srcs/ft_posix_openpt.c srcs/ft_ptsname.c srcs/ft_grantpt.c \
		srcs/ft_unlockpt.c

OBJS = 	$(patsubst srcs/%.c, objs/%.o, $(SRCS))

INCS = -I ./includes

FLAGS =	-Wall -Wextra -Werror

CC =	gcc

all: $(NAME)

$(NAME):	objs $(OBJS)
			@make -C libft/
			@$(CC) $(FLAGS) -o $(NAME) $(OBJS) ./libft/libft.a
			@echo "\033[32mCompilation OK\033[m"

objs/%.o:	srcs/%.c
			@$(CC) $(FLAGS) $(INCS) -o $@ -c $<

objs:
			@mkdir -p objs

clean:
	@make -C libft/ clean
	@rm -rf objs
	@rm -rf ft_script.dSYM

fclean: 		clean
	@make -C libft/ fclean
	@/bin/rm -f $(NAME)

re: 			fclean all

.PHONY = 		all clean fclean re
