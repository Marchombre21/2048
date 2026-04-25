#include "main.h"

int main(void) {

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
			printw("\nYou can't chose another number than 4 or 5. Please play the game.");
	}

	clear();
	refresh();

	int	grid[grid_size][grid_size];
	for (int i = 0; i < grid_size; i++)
	{
		for (int j = 0; j < grid_size; j++)
			if (i == 2 && j == 1)
				grid[i][j] = 128;
			else
				grid[i][j] = 0;

	}
	
	getmaxyx(stdscr, max_y, max_x);
	
	/* Initialize the window parameters */
	init_win_params(&win, grid_size, max_x, max_y);
	make_pairs();
	create_box(&win, grid_size, grid);

	while((ch = getch()) != 27)
	{	switch(ch)
		{	case KEY_LEFT:
				// left(grid_size, )
				break;
			case KEY_RIGHT:
				break;
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;	
		}
	}
	endwin();
	return 0;
}
