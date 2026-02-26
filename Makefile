NAME = codexion

CC = cc
RM = rm -rf
CFLAGS += -Wall -Wextra -Werror

SRCS = codexion.c coders/param_test.c coders/str_util.c coders/str_util_2.c

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all:	$(NAME) 

$(NAME): $(OBJS)
	  $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/coders

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
