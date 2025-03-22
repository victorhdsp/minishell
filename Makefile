CC_LIB_FLAG=-lreadline -lncurses
CC_WARNING_FLAG=-ggdb -Wall -Wextra #-Werror 
COMPILADOR=cc

NAME=minishell
FILES=./src/main.o ./src/tokenizer/wordbreaker.c

LIBFT_PATH=./include/libft
LIBFT_NAME=./include/libft/libft.a

TEST_DOCKER=./__test/docker-compose.yml
TEST_CONTAINER_NAME=criterion_minishell_rpassos_videsou

all: $(NAME) $(LIBFT_NAME)

$(NAME): $(FILES)
	$(COMPILADOR) $(LIBFT_NAME) $(CC_LIB_FLAG) $(CC_WARNING_FLAG) $^ -o $(NAME)

%.o: %.c
	$(COMPILADOR) $(LIBFT_NAME) $(CC_LIB_FLAG) $(CC_WARNING_FLAG) -c $< -o $@

$(LIBFT_NAME):
	@make -C $(LIBFT_PATH)

clean:
	rm -f $(FILES)

fclean: clean
	rm -f $(NAME)

re: clean all

test: $(TEST_CONTAINER_NAME) 
	@ clear
	@ docker exec -it $(TEST_CONTAINER_NAME) make re -C __test

$(TEST_CONTAINER_NAME): $(TEST_DOCKER)
	@if ! docker ps --format '{{.Names}}' | grep -q '^$(TEST_CONTAINER_NAME)$$'; then \
		echo "Iniciando Docker..."; \
		docker-compose -f $(TEST_DOCKER) up --detach; \
	fi