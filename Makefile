LIBFT_SRCS = $(shell cat libft/Makefile | grep "SRCS " | cut -d '=' -f 2)

LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

SRCS_NAMES = built_in_utils.c built_ins.c built_ins2.c env_utils.c executor_utils.c \
executor.c main.c parser_utils.c parser.c parser1.c tknizer_utils.c tokenizer.c \
utils.c expand.c

OBJS_DIR = objs/

SRCS_DIR = src/

HEADER = include/

CC_FLAGS = -Wall -Wextra -Werror -I $(HEADER)

OBJS_NAMES = $(SRCS_NAMES:c=o)

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAMES))

LIBFT_OBJS_DIR = $(addprefix libft/, $(LIBFT_OBJS))

NAME = Minishell

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADER)*
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_OBJS_DIR)
	$(CC) $(CC_FLAGS) $(OBJS) libft/libft.a -o $(NAME) -lreadline

all: $(NAME)

libft/libft.a:
	make --directory=libft

clean:
	rm -rf $(OBJS_DIR)
	make --directory=libft fclean

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
