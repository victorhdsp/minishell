#include "env.h"

int	ft_count_arr_size(char **arr)
{
	int	index = 0;

	while (arr[index] != NULL)
		index++;
	return (index);
}