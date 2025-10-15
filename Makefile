VARS_OLD := $(.VARIABLES)
CC = cc

CFLAGS = -Wall -Wextra -Werror -g -gdwarf-4 $(LDIR:%=-I%) -I/usr/include -std=c99
LFLAGS = -L -L/usr/lib -lXext -lX11 -lm -lbsd
DEBUG = -fsanitize=address

RM = rm -f
NAME = minirt

LIB = 42_libft/libft.a 42_matft/matft.a mlx_linux/libmlx_Linux.a

SRCSP = \
	parsing/parser.c \
	parsing/assign.c \
	parsing/utils/parsing_utils.c \
	parsing/utils/check_once.c \
	parsing/utils/check_others.c \
	parsing/utils/split_assign.c \
	parsing/utils/split_ispace.c \
	parsing/utils/transf.c \
	parsing/utils/debug.c \
	parsing/utils/clear.c \
	parsing/objects/ambiant.c \
	parsing/objects/light.c \
	parsing/objects/camera.c \
	parsing/objects/sphere.c \
	parsing/objects/plane.c \
	parsing/objects/cylinder.c \
	parsing/objects/boundings.c \

OBJSP = $(SRCSP:$(SDIRP)%.c=%.o)

SRCS = \
	src/minirt.c \
	src/vsh.c \
	src/initialize_structs.c \
	src/allocs.c \
	src/ray_dist_functions.c \

OBJS = $(addprefix $(ODIR), $(SRCS:$(SDIR)%.c=%.o))

LDIR = $(dir $(LIB))
SDIR = src/
ODIR = obj/

all: $(NAME) target

$(NAME): $(OBJS) $(OBJSP) $(LIB)
	$(CC) $(OBJS) $(OBJSP) $(LIB) $(CFLAGS) $(LFLAGS) -o $(NAME)
	@echo $(NAME)" compiled!\n"

debug: $(OBJS) $(OBJSP) $(LIB)
	$(CC) $(DEBUG) $(OBJS) $(OBJSP) $(LIB) $(CFLAGS) $(LFLAGS) -o $(NAME)
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
	$(RM) $(OBJS) $(OBJSP) $(NAME)

re: clean all

run: $(NAME)
	./$(NAME)

libs: $(LIB)

vars:
	@echo "VARIABLES:";
	@echo "$(foreach v, $(filter-out $(VARS_OLD) VARS_OLD,$(.VARIABLES)),\n| $(v) : $($(v)))" | sort | column -t -l4 -T4;

target:
	@echo $(NAME)

targets:
	@echo "TARGETS:";
	@LC_ALL=C $(MAKE) -pRrq : 2>/dev/null | awk -v RS= -F: '/(^|\n)# Files(\n|$$)/,/(^|\n)# Finished Make data base/ {if ($$1 !~ "^#") {print "| "$$1}}' | sort

info: vars targets

.PHONY: all clean fclean re run libs info vars targets target
