NAME = cub3d
OS := $(shell uname)
CC = gcc
CFLAGS =  -Wall -Wextra -Werror

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
		src/parsing_utils.c \
		src/raycasting.c \
		src/raycast_utils.c \
		src/scene_info.c \
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
		src/keys_hook.c \
		src/mouse_hook.c \
		src/parsing.h \
		src/shoot.c
# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[1;33m
NO_COLOR = \033[0m

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(CYAN)Linking...$(NO_COLOR)"
	$(CC) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

r: all
	./$(NAME)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(OBJ_DIR) $(NAME)
	@echo "$(GREEN)Build complete!$(NO_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NO_COLOR)"
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(NO_COLOR)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Cleaning all build files...$(NO_COLOR)"
	rm -f $(NAME)

libs:
	make -C libft/
	make -C $(MLX_DIR)

re: fclean libs all


run: re
	./$(NAME) $(MAPS)


.PHONY: art
art:
	@echo "$(CYAN)"
	@echo "\t\t\t\tฅ^•ﻌ•^ฅ"
	@echo "$(NO_COLOR)"

