#include "ascii.h"
#include "main.h"
#include <ncurses.h>

extern volatile sig_atomic_t g_signal;

int get_pair_color(int number)
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

void clean_win(WINDOW *local_win)
{
	werase(local_win);
	wrefresh(local_win);
}

void destroy_win(WINDOW *local_win)
{
	werase(local_win);
	wrefresh(local_win);
	delwin(local_win);
}

void create_box(WIN *p_win, int board_size, int board[board_size][board_size])
{
	int w, h, pos_x, pos_y, pair_color;

	w = p_win->box_width;
	h = p_win->box_height;

	for (int i = 0; i < p_win->board_size; i++)
	{
		for (int j = 0; j < p_win->board_size; j++)
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
			if (board[i][j] != 0)
			{
				pair_color = get_pair_color(board[i][j]);
				wattron(p_win->window, COLOR_PAIR(pair_color));
				for (int bg_pos_y = pos_y + 1; bg_pos_y < pos_y + h - 1; bg_pos_y++)
					for (int bg_pos_x = pos_x + 1; bg_pos_x < pos_x + w - 1; bg_pos_x++)
						mvwaddch(p_win->window, bg_pos_y, bg_pos_x, ' ');
				mvwprintw(p_win->window, pos_y + h / 2, pos_x + w / 2, "%d", board[i][j]);
				wattroff(p_win->window, COLOR_PAIR(pair_color));
			}

			// draw_ascii_number(p_win->window, pos_y + h / 2, pos_x + w / 2, board[i][j]);
		}
	}
	wrefresh(p_win->window);
}

// void draw_ascii_number(WINDOW *win, int start_y, int start_x, int number)
// {
// 	int divisor = 1;
// 	int temp = number;
// 	int espacement_x = 4;
// 	int i = 0;
// 	int digit;

// 	while (temp >= 10)
// 	{
// 		divisor *= 10;
// 		temp /= 10;
// 	}

// 	while (divisor > 0)
// 	{
// 		digit = (number / divisor) % 10;

// 		for (int ligne = 0; ligne < 3; ligne++)
// 		{
// 			mvwprintw(win, start_y + ligne, start_x + (i * espacement_x), "%s", ascii_art[digit][ligne]);
// 		}

// 		divisor /= 10;
// 		i++;
// 	}
// }

void init_win_params(WIN *p_win, int board_size, int max_x, int max_y)
{
	p_win->board_size = board_size;
	p_win->box_height = max_y * 0.2;
	p_win->box_width = max_x * 0.2;

	while (p_win->box_height < 3 || p_win->box_width < 8)
	{
		clear();
		mvprintw(0, 0, "Your terminal isn't big enough. Please enlarge it.");
		refresh();

		wgetch(stdscr);
		getmaxyx(stdscr, max_y, max_x);
		p_win->box_height = max_y * 0.2;
		p_win->box_width = max_x * 0.2;
	}

	p_win->height = board_size * (p_win->box_height - 1) + 1;
	p_win->width = board_size * (p_win->box_width - 1) + 1;
	p_win->starty = (max_y - p_win->height) / 2;
	p_win->startx = (max_x - p_win->width) / 2;

	p_win->window = newwin(p_win->height, p_win->width, p_win->starty, p_win->startx);
	keypad(p_win->window, TRUE);
	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
}

void make_pairs(void)
{
	init_pair(1, COLOR_GREEN, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);
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

int get_board_size(WINDOW *menu, int menu_y, int menu_x)
{
	int board_size = 0;
	int bests[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	int start_y = menu_y / 17;
	int start_x = menu_x / 2;

	mvwprintw(menu, start_y + 0, start_x - 16, " ____     ___    _  _      ___  ");
	mvwprintw(menu, start_y + 1, start_x - 16, "|___ \\   / _ \\  | || |    ( _ ) ");
	mvwprintw(menu, start_y + 2, start_x - 16, "  __) | | | | | | || |_   / _ \\ ");
	mvwprintw(menu, start_y + 3, start_x - 16, " / __/  | |_| | |__   _| | (_) |");
	mvwprintw(menu, start_y + 4, start_x - 16, "|_____|  \\___/     |_|    \\___/ ");

	mvwprintw(menu, start_y + 7, start_x - 20, "%s", "What board size do you want? 4x4 or 5x5?");
	mvwprintw(menu, start_y + 8, start_x - 7, "%s", "(press 4 or 5)");
	if (get_10_best_score(bests) < 0)
		mvwprintw(menu, start_y + 11, start_x - 19, "%s", "Error during parsing of best score file");
	else
	{
		mvwprintw(menu, start_y + 11, start_x - 6, "%s", "Best scores :");
		for (int i = 0; i < 10 && bests[i] > 0; i++)
		{
			if (i % 2)
				mvwprintw(menu, start_y + 12 + i, menu_x * 0.7, "%d: %d", i + 1, bests[i]);
			else
				mvwprintw(menu, start_y + 13 + i, menu_x * 0.2, "%d: %d", i + 1, bests[i]);
		}
	}

	wrefresh(menu);

	wtimeout(menu, 100);
	while (!g_signal)
	{
		board_size = wgetch(menu);
		if (board_size == ERR)
			continue;
		if (board_size == 52 || board_size == 53 || board_size == 27)
			break;
	}

	werase(menu);
	wrefresh(menu);
	delwin(menu);
	return (board_size - 48);
}

int lose_menu(WINDOW *menu, int menu_y, int menu_x, int score)
{
	char answer = 0;

	wattron(menu, COLOR_PAIR(11));
	mvwprintw(menu, menu_y / 3, menu_x / 2 - 13, "%s: %d", "You lose! Your score is", score);
	wattroff(menu, COLOR_PAIR(11));
	mvwprintw(menu, menu_y / 2, menu_x / 2 - 10, "%s", "Do you want restart?");
	mvwprintw(menu, menu_y * 0.75, menu_x / 2 - 7, "%s", "(press Y or N)");
	wrefresh(menu);

	wtimeout(menu, 100);
	while (!g_signal)
	{
		answer = wgetch(menu);
		if (answer == ERR)
			continue;
		if (answer == 121 || answer == 110 || answer == 27)
			break;
	}

	werase(menu);
	wrefresh(menu);
	delwin(menu);
	return (answer);
}

int win_menu(WINDOW *menu, int menu_y, int menu_x, int score)
{
	char answer = 0;

	wattron(menu, COLOR_PAIR(8));
	mvwprintw(menu, menu_y * 0.15, menu_x / 2 - 13, "You win! Your score is %d!", score);
	wattroff(menu, COLOR_PAIR(8));
	mvwprintw(menu, menu_y * 0.35, menu_x / 2 - 25, "%s", "Do you want Restart, Continue this game or Stop it?");
	mvwprintw(menu, menu_y * 0.55, menu_x / 2 - 17, "%s", "(If you continue it will never end.");
	mvwprintw(menu, menu_y * 0.6, menu_x / 2 - 23, "%s", "You will have to press ESC to finish your game.)");
	mvwprintw(menu, menu_y * 0.8, menu_x / 2 - 8, "%s", "(press R, C or S)");
	wrefresh(menu);

	wtimeout(menu, 100);
	while (!g_signal)
	{
		answer = wgetch(menu);
		if (answer == ERR)
			continue;
		if (answer == 114 || answer == 99 || answer == 115 || answer == 27)
			break;
	}

	werase(menu);
	wrefresh(menu);
	delwin(menu);
	return (answer);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	keypad(local_win, TRUE);
	box(local_win, 0, 0);
	wrefresh(local_win);

	return local_win;
}
