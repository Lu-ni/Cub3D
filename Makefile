NAME = cub3d
OS := $(shell uname)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(OS),Darwin)
	MLX_DIR = mlx
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = mlx_linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif

SRC = $(wildcard *.c)
OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS = $(wildcard *.h)

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[1;33m
NO_COLOR = \033[0m

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(OBJ_DIR) $(NAME)
	@echo "$(GREEN)Build complete!$(NO_COLOR)"

$(NAME): $(OBJ)
	@echo "$(CYAN)Linking...$(NO_COLOR)"
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(DEPS) | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NO_COLOR)"
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

run: art clean $(OBJ_DIR) $(OBJ)
	@echo "$(CYAN)Rebuilding without compilation flags...$(NO_COLOR)"
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Running the program...$(NO_COLOR)"
	./$(NAME)

r: all
	./$(NAME)

clean:
	@echo "$(YELLOW)Cleaning object files...$(NO_COLOR)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Cleaning all build files...$(NO_COLOR)"
	rm -f $(NAME)

re: fclean all

.PHONY: art
art:
	@echo "$(CYAN)"
	@echo "\t\t\t\tฅ^•ﻌ•^ฅ"
	@echo "$(NO_COLOR)"

