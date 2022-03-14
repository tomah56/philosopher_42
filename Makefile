CC = gcc
NAME = philo
FLAGS = -Wall -Wextra -Werror
SRC = 	ph*.c
OBJ = $(SRC:.c=.o)

# COLORS
Y = "\033[33m"
P = "\033[93m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

# all: $(NAME)
all: $(NAME)
	@printf "\n"
	@echo $(P)"▄▄▄▄   ▄           ▄▄         "$(X)
	@echo $(P)"█   █• █           ██         "$(X)
	@echo $(P)"████▪  █      ▀    ██    ▄█▀▄ "$(X)
	@echo $(P)"█▌     █▀▀█▌ ▐█   ▐█▌    █▌.▐ "$(X)
	@echo $(P)"█▌     █  █▌ █▌  .▀▐█▐█▌ ▀█▄▀ "$(X)
	@printf "\n\n"

$(NAME): $(OBJ) philo.h
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

no:
	$(CC) $(SRC) -o $(NAME).out
	@printf "\n"
	@echo $(P)"████▄  ▄           ▄▄         "$(X)
	@echo $(P)"█   █• █.          ██         "$(X)
	@echo $(P)"█▄▄▄▪  █      ▀    ██    ▄█▀▄ "$(X)
	@echo $(P)"▐▌     █▀▀█▌ ▐█   ▐█▌    █▌.▐ "$(X)
	@echo $(P)"█▌     █  █▌ █▌  .▀▐█▐█▌ ▀█▄▀ "$(X)
	@printf "\n\n"
# ███
#-------------- Part test ------------------

testh:
	./$(NAME) $(ARG2)

testfh:
	./$(NAME) $(ARG1)
