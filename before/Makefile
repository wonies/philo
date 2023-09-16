NAME = philo

CC = CC
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

HEADER	=	inc/philo.h

SRCS = srcs/philo.c \
srcs/init.c \

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