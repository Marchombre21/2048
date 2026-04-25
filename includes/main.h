#include <stdlib.h>
#include <ncurses.h>

#ifndef MAIN_H
# define MAIN_H

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	int grid_size;
	int	box_width;
	int	box_height;
	WINDOW	*window;
	WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win, int grid_size, int max_x, int max_y);
void create_box(WIN *win, int grid_size, int array[grid_size][grid_size]);

#endif