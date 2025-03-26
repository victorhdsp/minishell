ROOT=../src
INCLUDE=../include
NAME=test
FILES=./utils.c

CC_LIB_FLAG=#-lreadline -lncurses
CC_WARNING_FLAG=-I./src/ -ggdb -O0 #-Wall #-Wextra #-Werror 
COMPILADOR=cc $(CC_LIB_FLAG) $(CC_WARNING_FLAG)

all: $(NAME)

$(NAME): $(FILES)
	@ $(COMPILADOR) $(FILES) $(ROOT)/**/*.c $(INCLUDE)/**/*.c -o ./test -lcriterion
	@ ./test



fclean:
	@ rm -rf ./test

re: fclean all

%.o: %.c
	@ $(COMPILADOR) -c $< -o $@