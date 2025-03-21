DOCKER=./__test/docker-compose.yml
NAME=
CONTAINER_NAME=criterion_minishell_rpassos_videsou

all: $(NAME)

docker: $(DOCKER)
	@if ! docker ps --format '{{.Names}}' | grep -q '^$(CONTAINER_NAME)$$'; then \
		echo "Iniciando Docker..."; \
		docker-compose -f $(DOCKER) up -d; \
	fi

test: docker
	@ clear
	@ docker exec -it $(CONTAINER_NAME) make all -C __test
