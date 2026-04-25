#include "main.h"

int main(void)
{
	WIN win;
	int ch, max_y, max_x, grid_size;

	(void) ch;
	grid_size = 0;
	initscr();
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	printw("Chose if you want to play on a 4x4 grid or a 5x5 (press 4 or 5).");
	while (grid_size != 4 && grid_size != 5)
	{
		grid_size = getch() - 48;
		if (grid_size != 4 && grid_size != 5)
			printw("\nYou can't chose another number than 4 or 5. Please play "
			       "the game.");
	}

	clear();
	refresh();

	int grid[grid_size][grid_size];
	for (int i = 0; i < grid_size; i++)
		for (int j = 0; j < grid_size; j++)
			grid[i][j] = 0;

	add_nb(grid_size, grid);
	add_nb(grid_size, grid);

	getmaxyx(stdscr, max_y, max_x);
	// init_pair(1, COLOR_CYAN, COLOR_BLACK);

	/* Initialize the window parameters */
	init_win_params(&win, grid_size, max_x, max_y);
	make_pairs();
	create_box(&win, grid_size, grid);

	while ((ch = getch()) != 27)
	{
		if (is_loose(grid_size, grid))
			break;
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
		create_box(&win, grid_size, grid);
	}
	endwin();
	if (game_best_score(grid_size, grid) > all_time_best_score())
		save_score(game_best_score(grid_size, grid));
	return 0;
}
