NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror

SRCS = philo.c utils.c init.c routines.c forks.c checks.c destroy_free.c threads.c

OBJS = $(SRCS:.c=.o)

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
