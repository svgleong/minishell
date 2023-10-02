# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 20:09:21 by svalente          #+#    #+#              #
#    Updated: 2023/09/27 15:51:45 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

OBJ_PATH	= objs

SRCS		= srcs/main.c					\
			  srcs/libs/ft_calloc.c			\
			  srcs/libs/ft_memset.c			\
			  srcs/libs/ft_split.c			\
			  srcs/libs/ft_strdup.c			\
			  srcs/libs/ft_strlen.c			\
			  srcs/libs/ft_substr.c			\
			  srcs/libs/ft_strchr.c			\
			  srcs/libs/ft_strncmp.c		\
			  srcs/libs/ft_isspace.c		\
			  srcs/libs/ft_special_char.c	\
			  srcs/parser/list_utils.c 		\
			  srcs/parser/utils.c 			\
			  srcs/parser/check_quotes.c	\
			  srcs/parser/modify_string.c 	\
			  srcs/parser/redirections.c 	\
			  srcs/alloc/utils.c 			\
			  


OBJS		= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(basename $(SRCS))))
INCLUDES	= includes/

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I$(INCLUDES) -fsanitize=address #,undefined 
RM			= rm -f

FT_PRINTF_PATH = ./srcs/ft_printf
FT_PRINTF = ./srcs/ft_printf/libftprintf.a

$(VERBOSE).SILENT:

all: $(NAME)

$(OBJ_PATH)/%.o:%.c
	@make -C $(FT_PRINTF_PATH)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -I /usr/local/include -c -o $@ $<

$(NAME): $(OBJS)
	clear
	@$(CC) $(CFLAGS) $(FT_PRINTF) -lreadline -o $@  $^
	@echo "\033[1;35m---> MINISHELL SUCCESSFULLY COMPILED\033[0m"

run: 
	make re && clear && ./$(NAME)

clean: 
	clear
	@make clean -C $(FT_PRINTF_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;38;5;208m---> All .o files were deleted\033[0m"

fclean: clean
	@make fclean -C $(FT_PRINTF_PATH)
	@rm -rf $(NAME)
	@echo "\033[1;32m---> ./$(NAME) was deleted\033[0m"

valgrind:	re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes valgrind --tool=helgrind --log-file=valgrind-out.txt --suppressions=readline.supp ./minishell

re: fclean all

.PHONY: all clean fclean re r m