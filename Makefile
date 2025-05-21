VARS_OLD := $(.VARIABLES)
CC = cc

CFLAGS = -Wall -Wextra -Werror $(LDIR:%=-I%) -I/usr/include
DEBUG = -fsanitize=address

RM = rm -f
NAME = minirt

LIB = libft/libft.a matft/matft.a mlx_linux/libmlx_Linux.a

SRCS = \
	src/minirt.c \

OBJS = $(addprefix $(ODIR), $(SRCS:$(SDIR)%.c=%.o))

LDIR = $(dir $(LIB))
SDIR = src/
ODIR = obj/

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) $(CFLAGS) -o $(NAME)
	@echo $(NAME)" compiled!\n"

debug: $(OBJS) $(LIB)
	$(CC) $(DEBUG) $(OBJS) $(LIB) $(CFLAGS) -o $(NAME)
	@echo $(NAME)" compiled with debug!\n"

%.a:
	$(foreach lib, $@, $(MAKE) -C $(dir $(lib)) -s;)

$(ODIR)%.o: $(SDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(foreach lib,$(LDIR), $(MAKE) $@ -C $(lib) -s;)
	$(RM) $(OBJS)

fclean:
	$(foreach lib,$(LDIR), $(MAKE) $@ -C $(lib) -s;)
	$(RM) $(OBJS) $(NAME)

re: clean all

run: $(NAME)
	./$(NAME)

libs: $(LIB)

vars:
	@echo "VARIABLES:";
	@echo "$(foreach v, $(filter-out $(VARS_OLD) VARS_OLD,$(.VARIABLES)),\n | $(v)	:	$($(v)))" | column -t "-s	";

targets:
	@echo "TARGETS:";
	@LC_ALL=C $(MAKE) -pRrq : 2>/dev/null | awk -v RS= -F: '/(^|\n)# Files(\n|$$)/,/(^|\n)# Finished Make data base/ {if ($$1 !~ "^#") {print " | "$$1}}'

info: vars targets

.PHONY: all clean fclean re run libs info vars targets
