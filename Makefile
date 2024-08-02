NAME     = ft_mini_ls
CFLAGS   = -Wall -Wextra -Werror -g -Ilibft
LDFLAGS  = -Llibft -lft
SRCS     = ft_mini_ls.c \
		   ft_qsort.c
OBJS     = $(SRCS:.c=.o)
LIB_NAME = libft
LIB_PATH = ./$(LIB_NAME)/$(LIB_NAME).a

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIB_PATH):
	$(MAKE) -C $(LIB_NAME) bonus

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) -C $(LIB_NAME) clean
	$(RM) $(OBJS)

.PHONY: fclean
fclean:
	$(MAKE) -C $(LIB_NAME) fclean
	$(RM) $(OBJS) $(NAME)

.PHONY: re
re: fclean all
