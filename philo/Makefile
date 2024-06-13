NAME = philo

CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRCS = philo.c utils.c routines.c init.c pick_forks.c check_and_drop.c checks.c frees.c monitor.c

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
