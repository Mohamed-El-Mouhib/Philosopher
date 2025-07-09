CC=cc
CFLAGS=-Wall -Werror -Wextra -fsanitize=thread -g
NAME=philo
SRC=main.c thread_routins.c analyse_arg.c monitor.c
OBJ=$(SRC:%.c=%.o)

all: $(NAME)
 
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

PHONY: clean fclean re all

.SECONDARY: $(OBJ)