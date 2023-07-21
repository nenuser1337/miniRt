NAME=sphere.a

FILES=  main sphere_cylinder  utils utils2 vectors shader_utils

OBJ=$(FILES:=.o)

FLAGS = -Wall -Wextra #-Werror

LINKS= gcc -I /usr/local/include -O3 $(FILES:=.c) -L /usr/local/lib \
    -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME):
	$(LINKS)  
	
#ar rcs $(NAME) $(OBJ) 

clean:
	rm -rf $(OBJ) 
fclean:
	rm -rf $(OBJ) $(NAME)

re: fclean all