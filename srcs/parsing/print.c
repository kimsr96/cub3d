#include "cub3d.h"

void	print_identifier(t_game *g)
{
	int	i;

	i = 0;
	//while (i < 6)
	//{
	//	printf("path: %s\n", g->asset.split_line[i][1]);
	//	i++;
	//}
	printf("floor: %d\n", g->asset.floor_color);
	printf("ceiling: %d\n", g->asset.ceiling_color);
}

void	print_map(t_game *g)
{
	size_t	i;

	i = 0;
	while (i < g->map.row)
	{
		printf("%s\n", g->map.map_2d[i]);
		i++;
	}
}