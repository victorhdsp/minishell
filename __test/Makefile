FILES=./src/main.o ./src/tokenizer/wordbreaker.o ./src/tokenizer/lexer.o ./src/sentences/pipes.o ./src/tokenizer/parser.o ./src/env/get_env.o ./src/env/utils.o ./src/env_management/export.o ./src/env_management/unset.o ./src/env_management/utils.o ./src/echo/echo.o ./src/exec/exec.o ./src/exec/prepare.o ./src/utils.o ./src/cd/cd.o ./src/cd/utils.o ./src/ambient/ambient.o ./src/traitement/quote.o ./src/traitement/variable.o ./src/pwd/pwd.o
./src/readline/readline.o
INCLUDE=../include/**/*.c
TESTS=./**/*.test.c

TEST_UTILS=./utils.c
NAME=test

CC_LIB_FLAG=-lreadline -lncurses
CC_WARNING_FLAG=-I./src/ -ggdb -O0 #-Wall #-Wextra #-Werror 
COMPILADOR=cc $(CC_LIB_FLAG) $(CC_WARNING_FLAG)

all: $(NAME)

$(NAME): 
	@ $(COMPILADOR) $(TEST_UTILS) $(TESTS) $(FILES) $(INCLUDE) -o ./$(NAME) -lcriterion
	@ ./$(NAME)

fclean:
	@ rm -rf ./$(NAME)

re: fclean all

%.o: %.c
	@ $(COMPILADOR) -c $< -o $@