NAME = cub3D
OS := $(shell uname)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

ifeq ($(OS),Darwin)
	MLX_DIR = mlx
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
else
	MLX_DIR = mlx_linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif

SRC_DIR = src
SRC =   src/draw.c \
		src/errors.c \
		src/hud.c \
		src/inits.c \
		src/keys_hook.c \
		src/main.c \
		src/map.c \
		src/mapfile_errors.c \
		src/map_utils.c \
		src/minimap.c \
		src/mini_player.c \
		src/mouse_hook.c \
		src/objects.c \
		src/parsing.c \
		src/parsing2.c \
		src/parsing_utils.c \
		src/raycasting.c \
		src/raycast_utils.c \
		src/scene_info.c \
		src/scene_info2.c \
		src/score.c \
		src/shoot.c \
		src/sniper.c \
		src/time_utils.c \
		src/utils.c
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS =  src/cub.h \
		src/hud.h \
		src/keys.h \
		src/parsing.h

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[1;33m
NO_COLOR = \033[0m

# Main Target
$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(OBJ)
	@echo "$(CYAN)Linking...$(NO_COLOR)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build all
all: $(OBJ_DIR) $(NAME)
	@echo "$(GREEN)Build complete!$(NO_COLOR)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NO_COLOR)"
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

# Clean object files
clean:
	@echo "$(YELLOW)Cleaning object files...$(NO_COLOR)"
	rm -rf $(OBJ_DIR)

# Full clean
fclean: clean
	@echo "$(YELLOW)Cleaning all build files...$(NO_COLOR)"
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(MLX_DIR)/libmlx.a

# Library building with "quiet" check to avoid unnecessary rebuilds
libs: $(LIBFT) $(MLX_DIR)/libmlx.a

$(LIBFT):
	@if [ ! -f $@ ]; then \
		echo "$(YELLOW)Building libft...$(NO_COLOR)"; \
		make -C $(LIBFT_DIR); \
	elif ! make -C $(LIBFT_DIR) -q; then \
		echo "$(YELLOW)Updating libft...$(NO_COLOR)"; \
		make -C $(LIBFT_DIR); \
	fi

$(MLX_DIR)/libmlx.a:
	@if [ ! -f $@ ]; then \
		echo "$(YELLOW)Building mlx...$(NO_COLOR)"; \
		make -C $(MLX_DIR); \
	elif ! make -C $(MLX_DIR) -q; then \
		echo "$(YELLOW)Updating mlx...$(NO_COLOR)"; \
		make -C $(MLX_DIR); \
	fi

# Rebuild
re: fclean all

# Phony Targets
.PHONY: libs clean fclean re art

# Optional ASCII Art
art:
	@echo "$(CYAN)"
	@echo "\t\t\t\tฅ^•ﻌ•^ฅ"
	@echo "$(NO_COLOR)"

