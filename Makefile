# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 03:02:44 by absalhi           #+#    #+#              #
#    Updated: 2023/01/18 18:00:46 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
BNAME	=	philo_bonus

CFLAGS	=	-Wall -Wextra -Werror -pthread -O3 -fsanitize=address
CC		=	cc
RM		=	rm -rf

NONE	=	'\033[0m'
GREEN	=	'\033[32m'
GRAY	=	'\033[2;37m'
ITALIC	=	'\033[3m'

_SRCS	=	main.c ft_errors.c ft_init.c ft_philo_utils.c ft_utils.c \
			ft_functions.c
SRCS	=	$(addprefix mandatory/srcs/, $(_SRCS))
OBJS	=	$(SRCS:.c=.o)

_BSRCS	=	main.c
BSRCS	=	$(addprefix bonus/srcs/, $(_SRCS))
BOBJS	=	$(SRCS:.c=.o)

.c.o	:
			@echo $(ITALIC)$(GRAY) "     - Making $<..." $(NONE)
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			@echo $(ITALIC)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo $(GREEN)"- Compiled -"$(NONE)

bonus	:	$(BOBJS)
			@echo $(ITALIC)$(GRAY) "     - Compiling $(BNAME)..." $(NONE)
			@$(CC) $(CFLAGS) $(BOBJS) -o $(NAME)
			@echo $(GREEN)"- Compiled -"$(NONE)

clean	:
			@echo $(ITALIC)$(GRAY) "     - Removing object files..." $(NONE)
			@$(RM) $(OBJS) $(BOBJS)

fclean	:	clean
			@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
			@$(RM) $(NAME) $(BNAME)

re		:	fclean all

.PHONY	:	all clean fclean re
