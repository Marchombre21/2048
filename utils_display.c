#include "ascii.h"
#include "main.h"
#include <ncurses.h>

extern volatile sig_atomic_t g_signal;

static int get_pair_color(int number)
{
	int i;
	for (i = 1; i < 25; i++)
	{
		if ((number >> i) & 1)
			return (i);
	}
	return (i);
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
				draw_ascii_number(p_win->window, pos_y + 1, pos_x + 1, h - 2, w - 2, board[i][j]);
				// mvwprintw(p_win->window, pos_y + h / 2, pos_x + w / 2, "%d", board[i][j]);
				wattroff(p_win->window, COLOR_PAIR(pair_color));
			}

			// draw_ascii_number(p_win->window, pos_y + h / 2, pos_x + w / 2, board[i][j]);
		}
	}
	wrefresh(p_win->window);
}

void draw_ascii_number(WINDOW *win, int pos_y, int pos_x, int box_h, int box_w, int number)
{
	int digits[16];
	int len;
	int tmp;
	int start_y;
	int start_x;
	int row;
	int i;
	int digit;

	if (number == 0)
		return;

	len = 0;
	tmp = number;
	while (tmp > 0)
	{
		digits[len] = tmp % 10;
		tmp /= 10;
		len++;
	}

	start_y = pos_y + (box_h - 3) / 2;
	start_x = pos_x + (box_w - (len * 3)) / 2;

	row = 0;
	while (row < 3)
	{
		i = len - 1;
		while (i >= 0)
		{
			digit = digits[i];
			mvwprintw(win, start_y + row, start_x + (len - 1 - i) * 3, "%s", ascii_art[digit][row]);
			i--;
		}
		row++;
	}
}

void init_win_params(WIN *p_win, int board_size, int max_x, int max_y)
{
	p_win->board_size = board_size;
	p_win->box_height = max_y / 5;
	p_win->box_width = max_x / 5;

	while (p_win->box_height < 5 || p_win->box_width < 29)
	{
		clear();
		mvprintw(0, 0, "Your terminal isn't big enough. Please enlarge it.");
		refresh();

		wgetch(stdscr);
		getmaxyx(stdscr, max_y, max_x);
		p_win->box_height = max_y / 5;
		p_win->box_width = max_x / 5;
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
	init_pair(1, COLOR_BLACK, COLOR_WHITE);   // 2
	init_pair(2, COLOR_BLACK, COLOR_CYAN);    // 4
	init_pair(3, COLOR_BLACK, COLOR_GREEN);   // 8
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);  // 16
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA); // 32
	init_pair(6, COLOR_BLACK, COLOR_RED);     // 64

	init_pair(7, COLOR_WHITE, COLOR_BLUE);     // 128
	init_pair(8, COLOR_WHITE, COLOR_CYAN);     // 256
	init_pair(9, COLOR_WHITE, COLOR_GREEN);    // 512
	init_pair(10, COLOR_WHITE, COLOR_YELLOW);  // 1024
	init_pair(11, COLOR_WHITE, COLOR_MAGENTA); // 2048
	init_pair(12, COLOR_WHITE, COLOR_RED);     // 4096

	init_pair(13, COLOR_YELLOW, COLOR_BLUE);    // 8192
	init_pair(14, COLOR_YELLOW, COLOR_CYAN);    // 16384
	init_pair(15, COLOR_YELLOW, COLOR_GREEN);   // 32768
	init_pair(16, COLOR_YELLOW, COLOR_MAGENTA); // 65536
	init_pair(17, COLOR_YELLOW, COLOR_RED);     // 131072

	init_pair(18, COLOR_CYAN, COLOR_BLUE);    // 262144
	init_pair(19, COLOR_CYAN, COLOR_GREEN);   // 524288
	init_pair(20, COLOR_CYAN, COLOR_MAGENTA); // 1048576
	init_pair(21, COLOR_CYAN, COLOR_RED);     // 2097152

	init_pair(22, COLOR_BLACK, COLOR_BLUE);  // 4194304
	init_pair(23, COLOR_RED, COLOR_WHITE);   // 8388608
	init_pair(24, COLOR_BLUE, COLOR_WHITE);  // 16777216
	init_pair(25, COLOR_WHITE, COLOR_BLACK); // 33554432
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
				mvwprintw(menu, start_y + 12 + i, (menu_x / 10) * 7, "%d: %d", i + 1, bests[i]);
			else
				mvwprintw(menu, start_y + 13 + i, menu_x / 5, "%d: %d", i + 1, bests[i]);
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
	int answer = 0;

	wattron(menu, COLOR_PAIR(11));
	mvwprintw(menu, menu_y / 3, menu_x / 2 - 13, "%s: %d", "You lose! Your score is", score);
	wattroff(menu, COLOR_PAIR(11));
	mvwprintw(menu, menu_y / 2, menu_x / 2 - 10, "%s", "Do you want restart?");
	mvwprintw(menu, (menu_y / 4) * 3, menu_x / 2 - 7, "%s", "(press Y or N)");
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
	int answer = 0;

	wattron(menu, COLOR_PAIR(8));
	mvwprintw(menu, (menu_y / 20) * 3, menu_x / 2 - 13, "You win! Your score is %d!", score);
	wattroff(menu, COLOR_PAIR(8));
	mvwprintw(menu, (menu_y / 20) * 7, menu_x / 2 - 25, "%s", "Do you want Restart, Continue this game or Stop it?");
	mvwprintw(menu, (menu_y / 20) * 11, menu_x / 2 - 17, "%s", "(If you continue it will never end.");
	mvwprintw(menu, (menu_y / 20) * 12, menu_x / 2 - 23, "%s", "You will have to press ESC to finish your game.)");
	mvwprintw(menu, (menu_y / 20) * 16, menu_x / 2 - 8, "%s", "(press R, C or S)");
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
