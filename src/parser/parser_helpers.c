#include "../../inc/cub3d.h"

char *normalize_spaces(const char *str)
{
    if (!str)
        return NULL;

    int i;
	int j;
    int space_flag;

    size_t len;

	i = 0;
	j = 0;
	space_flag = 1;
	len = 0;

    while (str[len])
        len++;

    char *dup = malloc(len + 1);
    if (!dup)
        return (NULL);

    while (str[i])
    {
        if (str[i] == 9 || str[i] == 32 || (str[i] >= 11 && str[i] <= 13))
        {
            if (!space_flag && j > 0)
            {
                dup[j++] = ' ';
                space_flag = 1;
            }
        }
        else
        {
            dup[j++] = str[i];
            space_flag = 0;
        }
        i++;
    }
    if (j > 0 && dup[j - 1] == ' ')
        j--;

    dup[j] = '\0';
    return (dup);
}
