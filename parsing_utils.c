#include "cub3d.h"

int	is_line_empty(char *line)
{
	if (*line == '\n')
        return (true);
    while (*line)
	{
        if (!ft_isspace(*line))
            return (false);
        line++;
    }
    return (true);
}
