#include "main.h"

volatile sig_atomic_t g_signal = 0;

void sighandler(int signum)
{
	if (signum == SIGQUIT || signum == SIGINT)
		g_signal = 1;
}

int main(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);

	WIN win;
	WINDOW *menu;
	int ch, max_y, max_x, board_size, menu_x, menu_y, game_on, score, already_won;
	
	game_on = 1;
	already_won = 0;
	board_size = 0;
	initscr();
	start_color();
	cbreak();
	noecho();
	while (game_on && !g_signal)
	{
		getmaxyx(stdscr, max_y, max_x);
		
		menu = create_newwin(max_y * 0.5, max_x * 0.5, max_y * 0.25, max_x * 0.25);
		getmaxyx(menu, menu_y, menu_x);
		board_size = get_board_size(menu, menu_y, menu_x);

		if (g_signal || board_size < 4)
			break;
		int board[board_size][board_size];
		for (int i = 0; i < board_size; i++)
			for (int j = 0; j < board_size; j++)
				board[i][j] = 0;
	
		add_nb(board_size, board);
		add_nb(board_size, board);

		init_win_params(&win, board_size, max_x, max_y);
		make_pairs();
		create_box(&win, board_size, board);
	
		wtimeout(win.window, 100);
		while (!g_signal && (ch = wgetch(win.window)) != 27)
		{
			if (g_signal)
				break;
			switch (ch)
			{
			case ERR:
				continue;
			case KEY_LEFT:
				if (can_move_dir(board_size, board, 'L'))
					left(board_size, board);
				break;
			case KEY_RIGHT:
				if (can_move_dir(board_size, board, 'R'))
					right(board_size, board);
				break;
			case KEY_UP:
				if (can_move_dir(board_size, board, 'T'))
					up(board_size, board);
				break;
			case KEY_DOWN:
				if (can_move_dir(board_size, board, 'B'))
					down(board_size, board);
				break;
			case KEY_RESIZE:
				destroy_win(win.window);
				clear();
				refresh();

				getmaxyx(stdscr, max_y, max_x);
				init_win_params(&win, board_size, max_x, max_y);
				wtimeout(win.window, 100);
				create_box(&win, board_size, board);
				break;
			}
			if (is_loose(board_size, board))
			{
				score = game_best_score(board_size, board);
				menu = create_newwin(max_y * 0.5, max_x * 0.5, max_y * 0.25, max_x * 0.25);
				getmaxyx(menu, menu_y, menu_x);
				int answer = lose_menu(menu, menu_y, menu_x, score);
				if (answer == 110 || answer == 27)
					game_on = 0;
				break;
			}
			if (!already_won && is_win(board_size, board))
			{
				menu = create_newwin(max_y * 0.5, max_x * 0.5, max_y * 0.25, max_x * 0.25);
				getmaxyx(menu, menu_y, menu_x);
				int answer = win_menu(menu, menu_y, menu_x);
				//Stop
				if (answer == 115 || answer == 27)
				{
					game_on = 0;
					break;
				}
				//Restart
				if (answer == 114)
				{
					if (already_won)
						already_won = 0;
					break;
				}
				//Continue
				if (answer == 99)
					already_won = 1;
			}
			clean_win(win.window);
			create_box(&win, board_size, board);
		}
		if (ch == 27)
			game_on = 0;
		destroy_win(win.window);
		if (game_best_score(board_size, board) > all_time_best_score())
			save_score(game_best_score(board_size, board));
	}
	endwin();
	return 0;
}
