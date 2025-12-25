NAME = philo

CC = cc

C_FLAGS = -Wall -Wextra -Werror


OBJS_DIR = objs/
SRCS_DIR = srcs/


HEADERS = -I ./include

SRCS = main.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
.SECONDARY: ${OBJS}

all: $(NAME)

$(LIBFT):
	make
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS)  -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean