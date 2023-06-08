NAME=draw.a

FILES= draw vectors shadertoy closing utils

OBJ=$(FILES:=.o)

FLAGS = -Wall -Wextra #-Werror

LINKS= gcc -I /usr/local/include -O3 $(FILES:=.c) -L /usr/local/lib \
    -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME):
	$(LINKS)  
	./a.out
#ar rcs $(NAME) $(OBJ) 

clean:
	rm -rf $(OBJ) 
fclean:
	rm -rf $(OBJ) $(NAME)

re: fclean all