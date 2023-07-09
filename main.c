#include "so_long.h"

int main(int argc, char **argv)
{
	//system("sudo leaks so_long");
	t_map c;
	t_entity player;
	t_in fw; // Framework

	fw.map = &c;
	fw.player = &player;
	fw.player->value = 'P';
	c.map_name = argv[1];

	check_argc(argc);
	check_file_extension(argv[1], ".ber");
	process_map_file(&fw);

	fw.map->mlx = mlx_init();
	fw.map->mlx_win = mlx_new_window(fw.map->mlx, fw.map->columns * BPP,
	fw.map->lines * BPP, "Pokemon Adventures");

	mlx_process(&fw);
	mlx_key_hook(c.mlx_win, key_hook, &fw);
	mlx_hook(fw.map->mlx_win, 17, 0, close_window_event, &fw);
	mlx_expose_hook(fw.map->mlx_win, expose_window_event, &fw);
	mlx_loop_hook(c.mlx, loop_hook, &fw);
	mlx_loop(fw.map->mlx);
	//system("sudo leaks so_long");
	return 0;
}
