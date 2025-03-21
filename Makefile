CC_LIB_FLAG=-lreadline -lncurses
CC_WARNING_FLAG=-I./src/ -ggdb -O0 -Wall -Wextra -Werror 
COMPILADOR=cc #$(CC_WARNING_FLAG)

NAME=minishell
FILES=./src/main.o

LIBFT_PATH=./include/libft
LIBFT_NAME=./include/libft/libft.a

TEST_DOCKER=./__test/docker-compose.yml
TEST_CONTAINER_NAME=criterion_minishell_rpassos_videsou

all: $(NAME) $(LIBFT_NAME)

$(NAME): $(FILES)
	@$(COMPILADOR) $^ -o $(NAME)

.o: .c
	$(COMPILADOR) -c $< -o $@

$(LIBFT_NAME):
	@make -C $(LIBFT_PATH)

docker: $(DOCKER)
	@if ! docker ps --format '{{.Names}}' | grep -q '^$(CONTAINER_NAME)$$'; then \
		echo "Iniciando Docker..."; \
		docker-compose -f $(DOCKER) up -d; \
	fi

test: docker
	@ clear
	@ docker exec -it $(CONTAINER_NAME) make all -C __test
