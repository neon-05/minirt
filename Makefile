NAME = minirt

all: $(NAME)

$(NAME):
	make -C parsing/
	cp parsing/minirt .

clean:
	make clean -C parsing/

fclean:
	make fclean -C parsing/
	rm minirt

re:
	make fclean -C parsing/
	rm minirt
	make

.PHONY: all clean fclean re run libs info vars targets
