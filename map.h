
#ifndef MAP_H
# define INVALID_MAP -1
# define INVALID_COLOR -2

# define VALID_MAP 0

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
	char		**map;
}				t_map_data;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			c_color[3];
	int			f_color[3];

	t_map_data	map;
}				t_map;

# define PL printf("line: %d file: %s\n", __LINE__, __FILE__);

#endif
