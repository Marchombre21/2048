#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>


#ifndef MAIN_H
#define MAIN_H

#ifndef SCORE_FILE
#define SCORE_FILE "best_score.txt"
#endif // !SCORE_FILE

enum e_const
{
	WIN_VALUE = 2048
};

typedef struct _win_border_struct
{
	chtype ls, rs, ts, bs, tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct
{
	int        startx, starty;
	int        height, width;
	int        board_size;
	int        box_width;
	int        box_height;
	WINDOW    *window;
	WIN_BORDER border;
} WIN;

void  init_win_params(WIN *p_win, int board_size, int max_x, int max_y);
void  create_box(WIN *win, int board_size, int array[board_size][board_size]);
int   can_move_dir(int board_size, int board[board_size][board_size], char dir);
int   is_loose(int board_size, int board[board_size][board_size]);
int   is_win(int board_size, int board[board_size][board_size]);
char *ft_itoa(int n);
int   ft_strlen(const char *s);
int   ft_atoi(const char *nptr);
void  up(int board_size, int board[board_size][board_size]);
void  down(int board_size, int board[board_size][board_size]);
void  left(int board_size, int board[board_size][board_size]);
void  right(int board_size, int board[board_size][board_size]);
void  add_nb(int board_size, int board[board_size][board_size]);
void  make_pairs(void);
int   game_best_score(int board_size, int board[board_size][board_size]);
int   save_score(int score);
int   all_time_best_score(void);
void clean_win(WINDOW *local_win);
WINDOW *create_newwin(int height, int width, int starty, int startx);
int	get_board_size(WINDOW *menu, int max_y, int max_x);
int	lose_menu(WINDOW *menu, int max_y, int max_x, int score);
int	win_menu(WINDOW *menu, int menu_y, int menu_x);
void sighandler(int signum);
void destroy_win(WINDOW *local_win);

#endif
