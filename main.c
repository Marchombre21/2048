#include "main.h"

int main(void)
{
	WIN win;
	WINDOW *menu;
	int ch, max_y, max_x, grid_size;

	grid_size = 4;
	initscr();
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	getmaxyx(stdscr, max_y, max_x);

	menu = create_newwin(max_y, max_x, (LINES - max_y) / 2, (COLS - max_x) / 2);
	grid_size = get_grid_size(menu, max_y, max_x);

	int grid[grid_size][grid_size];
	for (int i = 0; i < grid_size; i++)
		for (int j = 0; j < grid_size; j++)
			grid[i][j] = 0;

	add_nb(grid_size, grid);
	add_nb(grid_size, grid);

	/* Initialize the window parameters */
	init_win_params(&win, grid_size, max_x, max_y);
	make_pairs();
	create_box(&win, grid_size, grid);

	while ((ch = getch()) != 27)
	{
		switch (ch)
		{
		case KEY_LEFT:
			if (can_move_dir(grid_size, grid, 'L'))
				left(grid_size, grid);
			break;
		case KEY_RIGHT:
			if (can_move_dir(grid_size, grid, 'R'))
				right(grid_size, grid);
			break;
		case KEY_UP:
			if (can_move_dir(grid_size, grid, 'T'))
				up(grid_size, grid);
			break;
		case KEY_DOWN:
			if (can_move_dir(grid_size, grid, 'B'))
				down(grid_size, grid);
			break;
		}
		if (is_loose(grid_size, grid))
		{
			menu = create_newwin(max_y, max_x, (LINES - max_y) / 2, (COLS - max_x) / 2);
			
			break;
		}
		// if (is_win(grid_size, grid))


		clean_win(win.window);
		create_box(&win, grid_size, grid);
	}
	destroy_win(win.window);
	endwin();
	if (game_best_score(grid_size, grid) > all_time_best_score())
		save_score(game_best_score(grid_size, grid));
	return 0;
}
