NAME=minishell
FILES=./src/main.o ./src/tokenizer/wordbreaker.o ./src/tokenizer/lexer.o ./src/sentences/pipes.o ./src/tokenizer/parser.o ./src/env/get_env.o ./src/env/utils.o ./src/env_management/export.o ./src/env_management/unset.o ./src/env_management/utils.o ./src/echo/echo.o ./src/exec/exec.o ./src/exec/prepare.o ./src/exec/utils.o ./src/utils.o ./src/cd/cd.o ./src/cd/utils.o ./src/flow/ambient.o ./src/flow/ambient_utils.o ./src/flow/program.o ./src/traitement/quote.o ./src/traitement/variable.o ./src/builtin/exec.o ./src/pwd/pwd.o ./src/readline/readline.o ./src/signals_handler/signals_handler.o ./src/exit/exit.o
LIBFT_PATH=./include/libft
LIBFT_NAME=./include/libft/libft.a

TEST_DOCKER=./__test/docker-compose.yml
TEST_CONTAINER_NAME=criterion_minishell_rpassos_videsou

CC_LIB_FLAG=-lreadline -lncurses
CC_WARNING_FLAG=-ggdb -Wall -Wextra #-Werror 
COMPILADOR=cc $(CC_WARNING_FLAG)

all: $(NAME) $(LIBFT_NAME)

$(NAME): $(FILES) $(LIBFT_NAME)
	$(COMPILADOR) $^ -o $(NAME) $(CC_LIB_FLAG)

%.o: %.c
	$(COMPILADOR) -c $< -o $@

$(LIBFT_NAME):
	@make -C $(LIBFT_PATH)

clean:
	@rm -f $(FILES)
	@make clean -C $(LIBFT_PATH) 

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_NAME)

re: fclean all

test: $(TEST_CONTAINER_NAME) 
	@ clear
	@ docker exec -it $(TEST_CONTAINER_NAME) make re -C __test

$(TEST_CONTAINER_NAME): $(TEST_DOCKER)
	@if ! docker ps --format '{{.Names}}' | grep -q '^$(TEST_CONTAINER_NAME)$$'; then \
		echo "Iniciando Docker..."; \
		docker-compose -f $(TEST_DOCKER) up --detach; \
	fi