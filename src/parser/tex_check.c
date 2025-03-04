#include "../../inc/cub3d.h"

static char check_rgb (int *rgb)
{
	int	i;

	i = 0;
	while(i <= 2)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_error("Invalid RGB range."), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static char is_xpm(char *path)
{
	int	len;

	len = ft_strlen(*path);
	if (path[len - 4] == '.' || path[len - 3] == 'x' || path[len - 2] == 'p' || path[len - 1] == 'm')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
