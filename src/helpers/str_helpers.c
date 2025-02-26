#include "../../inc/cub3d.h"

char **str_arr_realloc(char **str_arr, char *element)
{
	char **rtrn;

	int i;

	if (!str_arr)
	{
		rtrn = ft_calloc(sizeof(char *), 2);
		if (!rtrn)
			return(NULL);
		rtrn[0] = ft_strdup(element);
		return(rtrn);
	}
	rtrn = ft_calloc(sizeof(char *), str_arr_len(str_arr) + 2);
	if (!rtrn)
		return(NULL);
	i = -1;

	while (str_arr[++i])
		rtrn[i] = str_arr[i];
	rtrn[i] = ft_strdup(element);
	return(rtrn);
}

char *without_lines(char **str_arr)
{

}