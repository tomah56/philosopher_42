CC = gcc
NAME = philo_bonus
FLAGS = -Wall -Wextra -Werror
SRC = 	ph*.c
SRCC = 	ph_brain.c ph_long_atoi.c ph_run_game.c ph_utils.c philo.c 
OBJO = 	ph_brain.o ph_long_atoi.o ph_run_game.o ph_utils.o philo.o 
OBJ = $(SRCC:.c=.o)

PPP=-g -fsanitize=thread
LLL=-g -fsanitize=address
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
	@echo $(X)"▄▄▄▄   ▄           ▄▄             ▄      "$(X)
	@echo $(B)"█   █• █           ██             █      "$(X)
	@echo $(P)"████▪  █      ▀    ██    ▄█▀▄     ██▀▄   "$(X)
	@echo $(G)"█▌     █▀▀█▌ ▐█   ▐█▌    █▌.▐     █▌. ▐   "$(X)
	@echo $(R)"█▌     █  █▌ █▌  .▀▐█▐█▌ ▀█▄▀ ▀   ▐█▄▀  ▀ "$(X)
	@printf "\n\n"

$(NAME): $(OBJO) philo.h
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)


clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

fa:
	$(CC) $(SRC) $(PPP) -o $(NAME)
val:
	$(CC) $(SRCC) -lpthread -o $(NAME)
no:
	$(CC) $(SRC) -o $(NAME)
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
