NAME = philo_bonus

OS = $(shell uname)
ifeq ($(OS),Linux)
CFLAGS = -Wall -Wextra -Werror
else
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
endif

SRCS = philo.c utils.c init.c routines.c forks.c checks.c destroy_free.c threads.c

OBJS = $(SRCS:.c=.o)

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
	@make -C ./ clean
	clear
	@echo "\033[0;32mCompiled successfully"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
