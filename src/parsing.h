/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:11:31 by lnicolli          #+#    #+#             */
/*   Updated: 2025/02/15 23:02:29 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define INVALID_MAP 0
# define ERROR_WRONG_NUMBER_OF_ARG "wrong number of arguments"
# define ERROR_MISSING_DOTCUB "map file must have .cub extension"
# define ERROR_MISSING_TEXTURE "missing textures in map file"
# define ERROR_MISSING_COLOR "missing color(s) in map file"
# define ERROR_MISSING_MAP "missing map"
# define ERROR_INVALID_MAP "invalid map"
# define ERROR_INVALID_COL "invalid color"
# define ERROR_MISSING_MAPFILE "mapfile is missing"
# define ERROR_MAPFILE_DOES_NOT_EXIST "mapfile does not exist"
# define ERROR_TEXTURE_DOES_NOT_EXIST "texture file does not exist"
# define ERROR_NO_PLAYER "no player in map"
# define ERROR_MULTIPLE_PLAYER "multiple players in map"
# define ERROR_INVALID_PLAYER_DIRECTION "invalid player direction"
# define ERROR_MALLOC_FAILED "malloc failed"
# define ERROR_NO_MAP "no map in mapfile"
# define ERROR_MAP_TOO_SMALL "map is too small"
# define ERROR_INVALID_MAP_CHAR "invalid characters in map"
# define ERROR_MAP_NOT_CLOSED "map is not surrounded by walls"
# define ERROR_TOO_MANY_PLAYERS "too many players in map"
# define ERROR_DUPLICATE_TEXTURE "duplicate texture or color in mapfile"
# define ERROR_TEX_IS_DIR "texture file is a directory"
# define ERROR_INVALID_TEX "texture file is not valid"
# define ERROR_COLOR_RANGE "color range is not valid"

# define MALLOC_FAILED 9

# define TEXTURE_NBR 4
# define COLOR_NBR 2

# define OK 0

# define VALID_MAP 1
# define INVALID_COLOR -2
# define BUFFER_SIZE 10
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define EMPTY_SPACE 9

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_dim
{
	int		cols;
	int		rows;
	int		start;
}			t_dim;

# define WEAPON_FRAMES 24

typedef struct s_map
{
	char	*wall_tex[5];

	char	*ak_tex[WEAPON_FRAMES];
	char	*awp_tex[WEAPON_FRAMES];

	int		c_color;
	int		f_color;

	t_dim	dim;
	int		**map;

	char	directions[4];

	int		zoom;
	int		nbr_of_players;
}			t_map;

void		free_map(int **map, int rows);
void		free_char_array(char **arr);
void		free_int_array(int **arr, int rows);
void		handle_texture(int index, char *line, t_map *map);

// ERRORS
int			print_errors(char *error);
int			is_dotcub(char *mapfile);
int			mapfile_exists(int fd);
int			has_textures(char *mapfile);
int			is_line_empty(char *line);
int			is_mapfile_valid(char *mapfile, int fd);
char		*get_texture_path(char *line);
int			get_color(char *line, int *color);
int			get_scene_infos(char *line, t_map *map);
int			malloc_set_empty_spaces(int **map, int cols, int rows);
int			get_longest_map_line(char **file, int lines_count, int map_start);
int			get_map_start(char **file, int lines_count);
int			is_line_map(char *line);
int			count_lines(char *mapfile);
int			is_map_walled(int ***map, t_dim dim);
int			scene_errors(t_map *m);

char		*remove_spaces(char *line);
void		free_char_array(char **arr);
void		*ft_palloc(size_t size);
int			open_file(char *file, int *fd);

// # define PL printf("line: %d file: %s\n", __LINE__, __FILE__);

#endif
