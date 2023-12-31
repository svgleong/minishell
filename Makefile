# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 20:09:21 by svalente          #+#    #+#              #
#    Updated: 2023/11/18 16:02:41 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

OBJ_PATH	= objs

SRCS		= srcs/libs/ft_calloc.c						\
			  srcs/libs/ft_memset.c						\
			  srcs/libs/ft_split.c						\
			  srcs/libs/ft_strdup.c						\
			  srcs/libs/ft_strlen.c						\
			  srcs/libs/ft_substr.c						\
			  srcs/libs/ft_strncmp.c					\
			  srcs/libs/ft_putendl_fd.c					\
			  srcs/libs/ft_strchr.c						\
			  srcs/libs/ft_strncmp.c					\
			  srcs/libs/ft_isspace.c					\
			  srcs/libs/ft_special_char.c				\
			  srcs/libs/ft_isalnum.c					\
			  srcs/libs/ft_memcpy.c						\
			  srcs/libs/ft_strjoin_free.c				\
			  srcs/libs/free_utils.c					\
			  srcs/libs/ft_strjoin.c					\
			  srcs/libs/ft_itoa.c						\
			  srcs/libs/ft_atoi.c						\
			  srcs/libs/get_next_line.c					\
			  srcs/parser/utils.c 						\
			  srcs/parser/checker.c						\
			  srcs/parser/list_utils.c					\
			  srcs/parser/modify_string.c 				\
			  srcs/parser/remove_quotes.c 				\
			  srcs/parser/remove_quotes2.c 				\
			  srcs/parser/parser.c 						\
			  srcs/redirections/redir_lst_utils.c 		\
			  srcs/redirections/redirections.c 			\
			  srcs/redirections/type_redir.c 			\
			  srcs/redirections/clean_redirections.c 	\
			  srcs/redirections/redirections_checker.c 	\
			  srcs/alloc/utils.c 						\
			  srcs/executer/builtin/env.c				\
			  srcs/executer/builtin/env_utils.c			\
			  srcs/executer/builtin/export.c			\
			  srcs/executer/builtin/unset.c				\
			  srcs/executer/builtin/export_utils.c		\
			  srcs/executer/builtin/echo.c				\
			  srcs/executer/builtin/pwd.c				\
			  srcs/executer/builtin/cd.c				\
			  srcs/executer/builtin/exit.c				\
			  srcs/executer/executer.c					\
			  srcs/executer/executer_utils.c			\
			  srcs/executer/executer_utils2.c			\
			  srcs/executer/signals.c					\
			  srcs/executer/heredoc.c					\
			  srcs/executer/heredoc_utils.c				\
			  srcs/expansion/expansion.c				\
			  srcs/expansion/expansion_utils.c			\
			  srcs/expansion/expansion_utils2.c			\
			  srcs/main_utils.c 						\
			  srcs/main.c 								\
			  srcs/print_functions.c 					\


OBJS		= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(basename $(SRCS))))
INCLUDES	= includes/

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDES) #-g -fsanitize=address


all: $(NAME)

$(OBJ_PATH)/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -I /usr/local/include  -c -o $@ $<

$(NAME): $(OBJS)
	clear
	@$(CC) $(CFLAGS) -o $@  $^ -lreadline -lhistory
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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind-out.txt --suppressions=readline.supp --trace-children=yes ./minishell

re: fclean all


.PHONY: all clean fclean re r m