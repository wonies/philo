NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
//CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f

HEADER	=	inc/philo.h

SRCS = srcs/main.c \
srcs/init.c \
srcs/life.c \
srcs/table.c \
srcs/setting.c \
srcs/time.c \
srcs/valid.c \
srcs/eat.c \
srcs/eatutil.c \
srcs/utils.c \

OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: 
	make clean
	$(RM) $(NAME)

re: 
	make fclean 
	make all
	
.PHONY: all clean fclean re bonus