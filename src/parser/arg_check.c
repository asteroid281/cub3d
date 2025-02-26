#include "../../inc/cub3d.h"
#include "fcntl.h"
#include "stdbool.h"

static char is_dir(char *argv)
{
	int fd;

	fd = open(argv, O_DIRECTORY);
	if(fd >= 0)
	{
		close(fd);
		return (true);
	}
	return(false);
}

static char is_cub(char *argv)
{
	int len;

	len = ft_strlen(*argv);

	if (argv[len - 4] == '.' || argv[len - 3] == 'c' || argv[len - 2] == 'u' || argv[len - 1] == 'b')
		return(true);
	return(false);
}


int file_check (char *argv)
{
	int fd;

	if (is_dir(argv))
		return(print_error("Not directory"), -1);
	if (!is_cub(argv))
		return(print_error("File is not cub file."), -1 );
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return(print_error("File could not be opened."), -1);
	return(fd);
}

