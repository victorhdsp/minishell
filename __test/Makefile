FILES=../src/**/*.c ../src/utils.c 
INCLUDE=../include/**/*.c
TESTS=./**/*.test.c

TEST_UTILS=./utils.c
NAME=test

CC_LIB_FLAG=-lreadline -lncurses -lcriterion
CC_WARNING_FLAG=-I./src/ -ggdb -O0 #-Wall #-Wextra #-Werror 
COMPILADOR=cc $(CC_LIB_FLAG) $(CC_WARNING_FLAG)

all: $(NAME)

$(NAME): 
	@ $(COMPILADOR) $(TEST_UTILS) $(TESTS) $(FILES) $(INCLUDE) -o ./$(NAME) $(CC_LIB_FLAG)
	@ ./$(NAME)

fclean:
	@ rm -rf ./$(NAME)

re: fclean all

%.o: %.c
	@ $(COMPILADOR) -c $< -o $@ $(CC_LIB_FLAG)