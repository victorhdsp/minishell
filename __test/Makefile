ROOT=../src
NAME=test
FILES=./utils.c

CC_LIB_FLAG=#-lreadline -lncurses
CC_WARNING_FLAG=-I./src/ -ggdb -O0 -Wall -Wextra #-Werror 
COMPILADOR=cc $(CC_LIB_FLAG) $(CC_WARNING_FLAG)

all: $(NAME)

$(NAME): $(FILES)
	@ $(COMPILADOR) $(FILES) $(ROOT)/**/*.test.c -o ./test -lcriterion
	@ ./test
	@ rm -rf ./test

%.o: %.c
	@ $(COMPILADOR) -c $< -o $@