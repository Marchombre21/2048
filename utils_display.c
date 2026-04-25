#include "main.h"
#include "ascii.h"

int	get_pair_color(int number)
{

	if (number == 2)
		return (1);
	if (number == 4)
		return (2);
	if (number == 8)
		return (3);
	if (number == 16)
		return (4);
	if (number == 32)
		return (5);
	if (number == 64)
		return (6);
	if (number == 128)
		return (7);
	if (number == 256)
		return (8);
	if (number == 512)
		return (9);
	if (number == 1024)
		return (10);
	else
		return (11);
}

void create_box(WIN *p_win, int grid_size, int grid[grid_size][grid_size])
{
	int w, h, pos_x, pos_y, pair_color;

	w = p_win->box_width;
	h = p_win->box_height;

	for (int i = 0; i < p_win->grid_size; i++)
	{
		for (int j = 0; j < p_win->grid_size; j++)
		{
			pos_x = j * (w - 1);
			pos_y = i * (h - 1);
			mvwaddch(p_win->window, pos_y, pos_x, p_win->border.tl);
			mvwaddch(p_win->window, pos_y, pos_x + w - 1, p_win->border.tr);
			mvwaddch(p_win->window, pos_y + h - 1, pos_x, p_win->border.bl);
			mvwaddch(p_win->window, pos_y + h - 1, pos_x + w - 1, p_win->border.br);

			mvwhline(p_win->window, pos_y, pos_x + 1, p_win->border.ts, w - 2);
			mvwhline(p_win->window, pos_y + h - 1, pos_x + 1, p_win->border.bs, w - 2);
			mvwvline(p_win->window, pos_y + 1, pos_x, p_win->border.ls, h - 2);
			mvwvline(p_win->window, pos_y + 1, pos_x + w - 1, p_win->border.rs, h - 2);
			if (grid[i][j] != 0)
			{
				pair_color = get_pair_color(grid[i][j]);
				wattron(p_win->window, COLOR_PAIR(pair_color));
				mvwprintw(p_win->window, pos_y + h / 2, pos_x + w / 2, "%d", grid[i][j]);
				wattroff(p_win->window, COLOR_PAIR(pair_color));
			}

				// draw_ascii_number(p_win->window, pos_y + h / 2, pos_x + w / 2, grid[i][j]);
		}
	}
	wrefresh(p_win->window);
}

void draw_ascii_number(WINDOW *win, int start_y, int start_x, int number)
{
    int divisor = 1;
    int temp = number;
    int espacement_x = 4;
    int i = 0;
    int digit;

    while (temp >= 10)
    {
        divisor *= 10;
        temp /= 10;
    }

    while (divisor > 0)
    {
        digit = (number / divisor) % 10;

        for (int ligne = 0; ligne < 3; ligne++)
        {
            mvwprintw(win, start_y + ligne, start_x + (i * espacement_x), "%s", ascii_art[digit][ligne]);
        }

        divisor /= 10;
        i++;
    }
}

void	init_win_params(WIN *p_win, int grid_size, int max_x, int max_y)
{
	p_win->grid_size = grid_size;
	p_win->box_height = max_y * 0.2;
	p_win->box_width = max_x * 0.2;

	if (p_win->box_height < 3 || p_win->box_width < 8)
		{
			printw("Your terminal isn't big enough. Please enlarge it (press any key to close).");
			while(1)
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

void	make_pairs(void)
{
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_GREEN, COLOR_YELLOW);
	init_pair(3, COLOR_YELLOW, COLOR_CYAN);
	init_pair(4, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(5, COLOR_MAGENTA, COLOR_RED);
	init_pair(6, COLOR_RED, COLOR_GREEN);
	init_pair(7, COLOR_BLUE, COLOR_GREEN);
	init_pair(8, COLOR_GREEN, COLOR_BLUE);
	init_pair(9, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_RED, COLOR_BLACK);
}