# include "cub3d.h"

void print_errors(char *error)
{
	printf("Error: ");
	printf("%s\n", error);
}

int has_textures(char *mapfile)
{
	return (true);
}

int mapfile_exists(char *mapfile)
{
	int fd;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
	{
		print_errors(ERROR_MAPFILE_DOES_NOT_EXIST);
		return (false);
	}
	close(fd);
	return (true);
}

int is_dotcub(char *mapfile) {
	int len = ft_strlen(mapfile);
	if (len < 4 || ft_strncmp(mapfile + len - 4, ".cub", 4) != 0)
	{
		print_errors(ERROR_MISSING_DOTCUB);
		return (false);
	}

	return (true);
}

