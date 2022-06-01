NAME := minishell
ifeq ($(shell uname), Darwin)
	CFLAGS += -I$(shell brew --prefix readline)/include
	LDFLAGS += -L$(shell brew --prefix readline)/lib -lreadline
else
	LDFLAGS += -lreadline
endif
#CFLAGS := -I $(shell brew --prefix readline)/include #-Wall -Werror -Wextra
#LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib
INCLUDE := ./includes
LIBFT := ./libft
SRCS_DIR := ./srcs
OBJS_DIr := ./objs

SRCS := $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/signal/signal.c \
		$(SRCS_DIR)/utils/ft_strcmp.c

OBJS := $(patsubst $(SRCS_DIR)%,$(OBJS_DIr)%,$(SRCS:.c=.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) -I $(INCLUDE) $(OBJS) $(LIBFT)/libft.a -o $@

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