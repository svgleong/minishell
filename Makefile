# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 20:09:21 by svalente          #+#    #+#              #
#    Updated: 2023/10/14 19:53:48 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

OBJ_PATH	= objs

SRCS		= srcs/libs/ft_calloc.c			\
			  srcs/libs/ft_memset.c			\
			  srcs/libs/ft_split.c			\
			  srcs/libs/ft_strdup.c			\
			  srcs/libs/ft_strlen.c			\
			  srcs/libs/ft_substr.c			\
			  srcs/libs/ft_strncmp.c		\
			  srcs/libs/ft_putendl_fd.c		\
			  srcs/libs/ft_strchr.c			\
			  srcs/libs/ft_strncmp.c		\
			  srcs/libs/ft_isspace.c		\
			  srcs/libs/ft_special_char.c	\
			  srcs/libs/ft_isalnum.c		\
			  srcs/libs/ft_memcpy.c			\
			  srcs/libs/ft_strjoin_free.c	\
			  srcs/libs/lst_utils.c			\
			  srcs/parser/utils.c 			\
			  srcs/parser/checker.c			\
			  srcs/parser/list_utils.c		\
			  srcs/parser/modify_string.c 	\
			  srcs/parser/remove_quotes.c 	\
			  srcs/parser/redirections.c 	\
			  srcs/redirections/redir_lst_utils.c 	\
			  srcs/alloc/utils.c 			\
			  srcs/executer/builtin/env.c	\
			  srcs/executer/builtin/export.c\
			  srcs/executer/builtin/echo.c	\
			  srcs/executer/builtin/echo.c	\
			  srcs/executer/executer.c		\
			  srcs/expansion/expansion.c	\
			  srcs/expansion/expansion_utils.c\
			  srcs/expansion/expansion_utils2.c\
			  srcs/main.c 					\

OBJS		= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(basename $(SRCS))))
INCLUDES	= includes/

#FIXME: Change to CC
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I$(INCLUDES) -fsanitize=address,undefined
LDFLAGS		= -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include -lreadline -lhistory

#$(VERBOSE).SILENT:

all: $(NAME)

$(OBJ_PATH)/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -I /usr/local/include  -c -o $@ $<

$(NAME): $(OBJS)
	clear
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@  $^
	@echo "\033[1;35m---> MINISHELL SUCCESSFULLY COMPILED\033[0m"

run: 
	make re && clear && ./$(NAME)

clean: 
	clear
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;38;5;208m---> All .o files were deleted\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;32m---> ./$(NAME) was deleted\033[0m"

valgrind:	re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind-out.txt --suppressions=readline.supp ./minishell

re: fclean all


.PHONY: all clean fclean re r m