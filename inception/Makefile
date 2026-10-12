NAME	:= inception
COMPOSE	:= $(shell if docker compose version >/dev/null 2>&1; then echo "docker compose"; else echo "docker-compose"; fi)

all:
	@mkdir -p /home/hael-hal/data/mariadb /home/hael-hal/data/wordpress
	$(COMPOSE) -f srcs/docker-compose.yml up -d --build

down:
	$(COMPOSE) -f srcs/docker-compose.yml down

clean: down
	docker system prune -af

fclean:
	$(COMPOSE) -f srcs/docker-compose.yml down --volumes --remove-orphans
	@docker run --rm -v /home/hael-hal/data:/data debian:bookworm sh -c "rm -rf /data/mariadb/* /data/wordpress/* && chown -R 1000:1000 /data" 2>/dev/null || true
	@rm -rf /home/hael-hal/data/mariadb/* /home/hael-hal/data/wordpress/* 2>/dev/null || true
	docker system prune -af --volumes

re: fclean all

status:
	$(COMPOSE) -f srcs/docker-compose.yml ps

logs:
	$(COMPOSE) -f srcs/docker-compose.yml logs -f

.PHONY: all down clean fclean re status logs
