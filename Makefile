# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 20:09:21 by svalente          #+#    #+#              #
#    Updated: 2023/09/21 11:00:41 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

OBJ_PATH	= objs

SRCS		= $(shell find srcs/ -name '*.c')
OBJS		= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(basename $(SRCS))))
INCLUDES	= includes/

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I$(INCLUDES) -fsanitize=address,undefined
RM			= rm -f

#$(VERBOSE).SILENT:

all: $(NAME)

$(OBJ_PATH)/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -I /usr/local/include -c -o $@ $<

$(NAME): $(OBJS)
	clear
	@$(CC) $(CFLAGS) -lreadline -o $@  $^
	@echo "\033[1;35m---> MINISHELL SUCCESSFULLY COMPILED\033[0m"

run: $(NAME)
	./$(NAME)

clean: 
	clear
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;38;5;208m---> All .o files were deleted\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;32m---> ./$(NAME) was deleted\033[0m"

valgrind:	re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes valgrind --tool=helgrind --log-file=valgrind-out.txt ./minishell

re: fclean all

.PHONY: all clean fclean re r m