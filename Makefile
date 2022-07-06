NAME := minishell
ifeq ($(shell uname), Darwin)
	CFLAGS += -I$(shell brew --prefix readline)/include
	LDFLAGS += -L$(shell brew --prefix readline)/lib -lreadline
else
	CFLAGS += -fsanitize=leak -g
	LDFLAGS += -L/usr/include -lreadline
endif
INCLUDE := ./includes
LIBFT := ./libft
SRCS_DIR := ./srcs
OBJS_DIr := ./objs

SRCS := $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/signal/signal.c \
		$(SRCS_DIR)/utils/ft_strcmp.c \
		$(SRCS_DIR)/utils/free.c \
		$(SRCS_DIR)/builtin/cd.c \
		$(SRCS_DIR)/builtin/echo.c \
		$(SRCS_DIR)/builtin/exit.c \
		$(SRCS_DIR)/builtin/export.c \
		$(SRCS_DIR)/builtin/pwd.c \
		$(SRCS_DIR)/builtin/unset.c \
		$(SRCS_DIR)/lexer/lexer.c \
		$(SRCS_DIR)/utils/x_func.c \
		$(SRCS_DIR)/utils/x_func_second.c \
		$(SRCS_DIR)/execute/execute.c \
		$(SRCS_DIR)/builtin/builtin_core.c \
		$(SRCS_DIR)/builtin/builtin_utils.c \
		$(SRCS_DIR)/env/status.c \
		$(SRCS_DIR)/env/env_list.c \
		$(SRCS_DIR)/parser/parse_utils.c \
		$(SRCS_DIR)/parser/parser.c \
		$(SRCS_DIR)/gnl/get_next_line.c \
		$(SRCS_DIR)/gnl/get_next_line_utils.c \
		$(SRCS_DIR)/expand/expand.c \
		$(SRCS_DIR)/expand/expand_out.c \
		$(SRCS_DIR)/expand/expand_in.c \
		$(SRCS_DIR)/builtin/env.c \
		$(SRCS_DIR)/execute/execute_utils.c \
		$(SRCS_DIR)/execute/execve_utils.c \
		$(SRCS_DIR)/builtin/export_utils.c \


OBJS := $(patsubst $(SRCS_DIR)%,$(OBJS_DIr)%,$(SRCS:.c=.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(LDFLAGS) $(LIBFT)/libft.a -o $@

$(OBJS_DIr)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIr)/$(*D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) -rf $(OBJS_DIr)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

.PHONY: re
re: fclean all
