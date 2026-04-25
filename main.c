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
	return 0;
}
void init_win_params(WIN *p_win, int grid_size, int max_x, int max_y)
{
	p_win->grid_size = grid_size;
	p_win->box_height = max_y * 0.2;
	p_win->box_width = max_x * 0.2;

	if (p_win->box_height < 3 || p_win->box_width < 8)
	{
		printw("Your terminal isn't big enough. Please enlarge it (press any "
		       "key to close).");
		while (1)
		{
			if (getch())
			{
				endwin();
				exit(1);
			}
		}
	}

	p_win->height = grid_size * (p_win->box_height - 1) + 1;
	p_win->width = grid_size * (p_win->box_width - 1) + 1;
	p_win->starty = (max_y - p_win->height) / 2;
	p_win->startx = (max_x - p_win->width) / 2;

	p_win->window = newwin(p_win->height, p_win->width, p_win->starty, p_win->startx);
	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
}

void create_box(WIN *p_win, int grid_size, int grid[grid_size][grid_size])
{
	int w, h, pos_x, pos_y;

	w = p_win->box_width;
	h = p_win->box_height;

	for (int i = 0; i < p_win->grid_size; i++)
	{
		for (int j = 0; j < p_win->grid_size; j++)
		{
			pos_x = i * (w - 1);
			pos_y = j * (h - 1);
			mvwaddch(p_win->window, pos_y, pos_x, p_win->border.tl);
			mvwaddch(p_win->window, pos_y, pos_x + w - 1, p_win->border.tr);
			mvwaddch(p_win->window, pos_y + h - 1, pos_x, p_win->border.bl);
			mvwaddch(p_win->window, pos_y + h - 1, pos_x + w - 1, p_win->border.br);

			mvwhline(p_win->window, pos_y, pos_x + 1, p_win->border.ts, w - 2);
			mvwhline(p_win->window, pos_y + h - 1, pos_x + 1, p_win->border.bs, w - 2);
			mvwvline(p_win->window, pos_y + 1, pos_x, p_win->border.ls, h - 2);
			mvwvline(p_win->window, pos_y + 1, pos_x + w - 1, p_win->border.rs, h - 2);
			if (grid[i][j] != 0)
				mvwprintw(p_win->window, pos_y + h / 2, pos_x + w / 2, "%d", grid[i][j]);
			else
				mvwprintw(p_win->window, pos_y + h / 2, pos_x + w / 2, " ");
		}
	}
	wrefresh(p_win->window);
}
