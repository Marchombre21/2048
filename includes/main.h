#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>

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
size_t  ft_strlen(const char *s);
int     ft_atoi(const char *nptr);
void    up(int board_size, int board[board_size][board_size]);
void    down(int board_size, int board[board_size][board_size]);
void    left(int board_size, int board[board_size][board_size]);
void    right(int board_size, int board[board_size][board_size]);
void    add_nb(int board_size, int board[board_size][board_size]);
void    make_pairs(void);
int     game_best_score(int board_size, int board[board_size][board_size]);
int     save_score(int score);
int     score_file_format(void);
int     get_10_best_score(int tab[10]);
void    clean_win(WINDOW *local_win);
WINDOW *create_newwin(int height, int width, int starty, int startx);
int     get_board_size(WINDOW *menu, int max_y, int max_x);
int     lose_menu(WINDOW *menu, int max_y, int max_x, int score);
int     win_menu(WINDOW *menu, int menu_y, int menu_x, int score);
void    sighandler(int signum);
void    destroy_win(WINDOW *local_win);
void    ft_bzero(void *s, size_t n);
char  **ft_split(char const *s, char c);
char   *ft_substr(char const *s, unsigned int start, size_t len);
int     is_absolute_win(int board_size, int board[board_size][board_size]);
void draw_ascii_number(WINDOW *win, int pos_y, int pos_x, int box_h, int box_w, int number);

#endif
