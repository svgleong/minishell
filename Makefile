# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 22:11:35 by svalente          #+#    #+#              #
#    Updated: 2023/09/20 12:49:22 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/parser/list_utils.c\
		

OBJ			=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

SRC_DIR		=	srcs

OBJ_DIR		=	objs

NAME		=	minishell

SHELL		=	/bin/bash

#LIB			=	lib/printf_fd/libprintf_fd.a

INC			=	includes/

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g -I$(INC) #-fsanitize=address

RM			=	rm -rf

LIBFT_PATH = ./srcs/Libft
FT_PRINTF_PATH = ./srcs/ft_printf

LIBFT = ./srcs/Libft/libft.a
FT_PRINTF = ./srcs/ft_printf/libftprintf.a

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m


COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m


all:	$(NAME)

header:
	@printf "%b" "$(COM_COLOR)"
	@echo "        ___  _____ ___  ___      _        "
	@echo "       /   |/ __  \|  \/  |     | |       "
	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___| v2"
	@echo

$(NAME):	$(LIB) $(OBJ)
	@printf "%b" "$(OK_COLOR)"
	@echo  "✨✨ Upgraded Successfuly!! ✨✨"
	@make bonus -C $(LIBFT_PATH)
	@make -C $(FT_PRINTF_PATH)
	@$(CC) $(CFLAGS) $(LIBFT) $(FT_PRINTF) -o $(NAME) $(OBJ) -lreadline
	@printf "%b" "$(NO_COLOR)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@printf "%b" "$(OBJ_COLOR)"
	@echo  "🔨🔨  Compiling Objects... 🔨🔨"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I includes -I /usr/local/include -I lib/printf_fd/include -c $< -o $@
	@printf "%b" "$(NO_COLOR)"

$(LIB):
	make -C lib/printf_fd

clean:	header
	@echo $(PURPLE) "🧹🧹 Cleaning... 🧹🧹" $(EOC)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(FT_PRINTF_PATH)
	@$(RM) $(OBJ_DIR)
	@printf "%b" "$(NO_COLOR)"

fclean:	clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(FT_PRINTF_PATH)
	@$(RM) $(NAME)

git:
	@git add .
	@git commit -m "$m"
	@git push
	@echo "Commit sent to github"

valgrind:	re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind-out.txt ./minishell

re:	fclean all


#@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L lib/printf_fd -lprintf_fd
#@make clean -C lib/printf_fd