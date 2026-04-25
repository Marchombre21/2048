#include <main.h>

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
	while (grid_size != 52 && grid_size != 53)
	{
		grid_size = getch();
		if (grid_size != 52 && grid_size != 53)
			printw("\nYou can't chose another number than 4 or 5. Please play the game.");
	}
	int	grid[grid_size][grid_size];
	for (int i; i < grid_size; i++)
	{
		for (int j; j < grid_size; j++)
			grid[i][j] = 0;
	}
	
	getmaxyx(stdscr, max_y, max_x);
	// init_pair(1, COLOR_CYAN, COLOR_BLACK);
	
	/* Initialize the window parameters */
	init_win_params(&win, grid_size, max_x, max_y);
	create_box(&win, grid_size);

	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case KEY_LEFT:
				break;
			case KEY_RIGHT:
				break;
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;	
		}
	}
	endwin();			/* End curses mode		  */
	return 0;
}
void init_win_params(WIN *p_win, int grid_size, int max_x, int max_y)
{
	p_win->height = grid_size * 5;
	p_win->width = grid_size * 10;
	p_win->starty = (max_y - p_win->height)/2;
	p_win->startx = (max_x - p_win->width)/2;

	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';

}

void create_box(WIN *p_win, int grid_size)
{
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	for (int i; i < grid_size; i++)
	{
		mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);

	}

	refresh();

}