#ifndef MAP_H

# define INVALID_MAP 0

# define ERROR_MISSING_DOTCUB (char *)"map file must have .cub extension"
# define ERROR_MISSING_TEXTURE (char *)"missing textures in map file"
# define ERROR_MISSING_COLOR (char *)"missing color(s) in map file"
# define ERROR_MISSING_MAP (char *)"missing map"
# define ERROR_INVALID_MAP (char *)"invalid map"
# define ERROR_INVALID_COLOR (char *)"invalid color"
# define ERROR_MISSING_MAPFILE (char *)"mapfile is missing"
# define ERROR_MAPFILE_DOES_NOT_EXIST (char *)"mapfile does not exist"
# define ERROR_TEXTURE_DOES_NOT_EXIST (char *)"texture file does not exist"
# define ERROR_MULTIPLE_PLAYER (char *)"multiple players in map"
# define ERROR_INVALID_PLAYER_DIRECTION (char *)"invalid player direction"


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

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// typedef struct s_map_data
// {
// 	int		**map;
// }				t_map_data;

typedef struct s_dim
{
	int			cols;	// number of columns
	int			rows; // number of rows
	int			start; // start row number
} 				t_dim;

typedef struct s_map
{
	// char		*no;
	// char		*so;
	// char		*we;
	// char		*ea;

	char		*wall_tex[5];
	char 		*weapon_tex[5];

	int			c_color;
	int			f_color;

	int 		p_direction;

	t_dim		dim;
	int			**map;

	char 		directions[4];

}				t_map;


void	free_map(int **map, int rows);

// ERRORS
void print_errors(char *error);
int is_dotcub(char *mapfile);
int mapfile_exists(char *mapfile);
int has_textures(char *mapfile);
int	is_line_empty(char *line);
int	is_mapfile_valid(char *mapfile);
char	*get_texture_path(char *line);
int	get_color(char *line);
int	get_scene_infos(char *line, t_map *map);
int malloc_set_empty_spaces(int **map, int cols, int rows);
void	printmap(int **map, int cols, int rows);
int	get_longest_map_line(char **file, int lines_count, int map_start);
int	ft_isnewline(char c);
int	get_map_start(char **file, int lines_count);
int	is_line_map(char *line);
int	count_lines(char *filename);
int	is_map_walled(int ***map, t_dim dim);
int scene_errors(t_map *m);




# define PL printf("line: %d file: %s\n", __LINE__, __FILE__);

#endif
