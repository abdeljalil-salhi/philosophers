# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 03:02:44 by absalhi           #+#    #+#              #
#    Updated: 2023/01/23 09:16:09 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CFLAGS	=	-Wall -Wextra -Werror -pthread -flto
CC		=	cc
RM		=	rm -rf
MKDIR	=	mdkir -p

NONE	=	'\033[0m'
GREEN	=	'\033[32m'
RED		=	'\033[1;91m'
GRAY	=	'\033[2;37m'
ITALIC	=	'\033[3m'

_SDIR	=	srcs
_SRCS	=	main.c ft_errors.c ft_init.c ft_philo_utils.c ft_utils.c \
			ft_functions.c ft_philo.c
SRCS	=	$(addprefix $(_SDIR)/, $(_SRCS))
OBJS	=	$(SRCS:.c=.o)

.c.o	:
			@echo $(ITALIC)$(GRAY) "     - Making $<..." $(NONE)
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			@echo $(ITALIC)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
			@$(CC) $(CFLAGS) $(OBJS) -o $@
			@echo $(GREEN)"- Compiled -"$(NONE)clean	:
			@echo $(ITALIC)$(GRAY) "     - Removing object files..." $(NONE)
			@$(RM) $(OBJS)

fclean	:	clean
			@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
			@$(RM) $(NAME)

re		:	fclean all

norm	:
			@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking header files norminette..." $(GRAY)
			@norminette includes/*.h
			@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking source files norminette..." $(GRAY)
			@norminette srcs/*.c

.PHONY	:	all clean fclean re norm
