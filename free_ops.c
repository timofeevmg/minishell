#include "minishell.h"

void	free_d_arr(char **array)
{
	int	j;

	j = 0;
	while (array[j] != NULL)
	{
		free(array[j]);
		j++;
	}
	free(array);
}