#ifndef MAP_H

# define INVALID_MAP 0
# define VALID_MAP 1
# define INVALID_COLOR -2
# define BUFFER_SIZE 10
# define NO 1
# define SO 2
# define WE 3
# define EA 4

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map_data
{
	int		**map;
}				t_map_data;

typedef struct s_dim
{
	int			cols;	// number of columns
	int			rows; // number of rows
	int			start; // start row number
} 				t_dim;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			c_color;
	int			f_color;
	t_dim		dim;

	int			**map;
}				t_map;

# define PL printf("line: %d file: %s\n", __LINE__, __FILE__);

#endif
