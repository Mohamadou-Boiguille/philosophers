# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/13 20:34:10 by moboigui          #+#    #+#              #
#    Updated: 2022/11/14 06:45:59 by moboigui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		ft_atoi.c ft_bzero.c ft_calloc.c \
			ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isalnum.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_strchr.c ft_strdup.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_tolower.c ft_toupper.c \
			ft_substr.c ft_split.c ft_strjoin.c ft_strtrim.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c \

SRCSB =		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c \

NAME =		libft.a

OBJS =		$(SRCS:.c=.o)
OBJSB =		$(SRCSB:.c=.o)

FLAGS =		-Wall -Wextra -Werror -I.
CC =		gcc $(FLAGS)
RM =		rm -f

all:		$(NAME)

$(NAME): ${OBJS}
	@ar rcs $(NAME) $(OBJS)
	@echo "libft compiled"

clean:
	@$(RM) $(OBJS) $(OBJSB)
	@echo "clean done"

fclean:	clean
	@$(RM) $(NAME)
	@echo "fclean done"

re:		fclean $(NAME)

bonus:$(OBJSB)	$(OBJS) 
	@ar rcs $(NAME) $(OBJS) $(OBJSB)
	@echo "libft bonuses compiled"

.PHONY:		all clean fclean re bonus
