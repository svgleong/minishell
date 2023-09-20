# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 14:36:05 by svalente          #+#    #+#              #
#    Updated: 2023/09/19 22:09:13 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr\
ft_memcmp ft_strlen ft_strlcpy ft_strlcat ft_strchr ft_strrchr\
ft_strnstr ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum\
ft_isascii ft_isprint ft_toupper ft_tolower ft_calloc ft_strdup\
ft_itoa	ft_strtrim ft_substr ft_strjoin ft_split ft_striteri\
ft_strmapi ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd\

BONUS = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast\
ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap\

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs

$(VERBOSE).SILENT:

all: $(NAME)

$(NAME): $(SRC:=.o)
			$(AR) $(NAME) $(SRC:=.o)
			echo -e "\n[libft successfully compiled :D]"

bonus: $(SRC:=.o) $(BONUS:=.o)
		$(AR) $(NAME) $(SRC:=.o) $(BONUS:=.o)

clean:
	$(RM) $(SRC:=.o) $(BONUS:=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all