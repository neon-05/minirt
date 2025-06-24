VARS_OLD := $(.VARIABLES)
CC = cc

CFLAGS = -Wall -Wextra -Werror -g -gdwarf-4 $(LDIR:%=-I%) -I/usr/include
LFLAGS = -L$(LIBDIR) -L/usr/lib -lXext -lX11 -lm -lbsd
DEBUG = -fsanitize=address

RM = rm -f
NAME = minirt

LIB = ../42_libft/libft.a ../42_matft/matft.a

SRCS = \
	parser.c \
	parsing_utils.c \
	check_once.c \
	check_others.c \
	ambiant.c \
	light.c \
	camera.c \
	transf.c \
	sphere.c \
	plane.c \
	cylinder.c \

OBJS = $(addprefix $(ODIR), $(SRCS:$(SDIR)%.c=%.o))

LDIR = $(dir $(LIB))
SDIR =
ODIR =

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) $(CFLAGS) $(LFLAGS) -o $(NAME)
	@echo $(NAME)" compiled!\n"
	make clean

debug: $(OBJS) $(LIB)
	$(CC) $(DEBUG) $(OBJS) $(LIB) $(CFLAGS) $(LFLAGS) -o $(NAME)
	@echo $(NAME)" compiled with debug!\n"

%.a:
	$(foreach lib, $@, $(MAKE) -C $(dir $(lib)) -s;)

$(ODIR)%.o: $(SDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-$(foreach lib,$(LDIR), $(MAKE) $@ -C $(lib) -s;)
	$(RM) $(OBJS)

fclean:
	-$(foreach lib,$(LDIR), $(MAKE) $@ -C $(lib) -s;)
	$(RM) $(OBJS) $(NAME)

re: clean all

run: $(NAME)
	./$(NAME)

libs: $(LIB)

vars:
	@echo "VARIABLES:";
	@echo "$(foreach v, $(filter-out $(VARS_OLD) VARS_OLD,$(.VARIABLES)),\n| $(v) : $($(v)))" | sort | column -t -l4 -T4;

targets:
	@echo "TARGETS:";
	@LC_ALL=C $(MAKE) -pRrq : 2>/dev/null | awk -v RS= -F: '/(^|\n)# Files(\n|$$)/,/(^|\n)# Finished Make data base/ {if ($$1 !~ "^#") {print "| "$$1}}' | sort

info: vars targets

.PHONY: all clean fclean re run libs info vars targets
