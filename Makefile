CC = cc

DEBUG = -fsanitize=address

CFLAGS = -Wall -Wextra -Werror $(addrpefix, -I, $(LDIR)) -I/usr/include
RM = rm -f

NAME = minirt
LIB = libft/libft.a matft/matft.a

SRCS = \

OBJS = $(addprefix $(ODIR)/, $(SRCS:.c=.o))
LDIR = $(dir $(LIB))
ODIR = obj

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) $(CFLAGS) -o $(NAME)
	@echo $(NAME)" compiled!\n"

debug: $(OBJS) $(LIB)
	$(CC) $(DEBUG) $(OBJS) $(LIB) $(CFLAGS) -o $(NAME)
	@echo $(NAME)" compiled with debug!\n"

%.a:
	$(foreach lib, $@, $(MAKE) -C $(dir $(lib)) -s;)

$(ODIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(foreach lib,$(LDIR), $(MAKE) $@ -C $(lib) -s;)
	$(RM) $(OBJS)

fclean:
	$(foreach lib,$(LDIR), $(MAKE) $@ -C $(lib) -s;)
	$(RM) $(OBJS) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

libs: $(LIB)

info:
	@echo "name: $(NAME)"
	@echo "libs: $(LIB)";
	@echo "srcs: $(SRCS)";
	@echo "objs: $(ODIR)/";

.PHONY: all clean fclean re run libs info
