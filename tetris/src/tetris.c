#include <stdio.h>
#include <def.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <keyboard.h>
#include <tetris.h>
#include <stdlib.h>

void draw_element(int x, int y, int c)
{
	x *= 2;
	x++;
	y++;

	printf("\033[%d;%dH\033[?25l", y, x);
	printf("\033[3%dm\033[4%dm[]", c, c);
	fflush(stdout);
	printf("\033[0m");
}

void show_next( void )
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if ( shape_arr[next].s[i][j] == 0 ) {
				draw_element(W+2+j, 2+i, BC);
			} else {
				draw_element(W+2+j, 2+i, FC);
			}
		}
	}
}

void clean_line( void )
{
	for (int i=0; i<H; i++) {
		int t = 0;
		for (int j=0; j<W; j++){
			if( background[i][j] != 0 )
				t++;
		}
		if ( t == W ) {
			for (int k=i; k>0; k--) {
				memcpy(background[k], background[k-1], 
								sizeof background[i]);
			}
			memset(background[0], 0x00, sizeof background[0]);
		}
	}
}

void draw_shape(int x, int y, struct shape p, int c)
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if ( p.s[i][j] != 0 )
				draw_element(x+j, y+i, c);
		}
	}
}

int can_move(int x, int y, struct shape sp)
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if ( sp.s[i][j] == 0 )
				continue;
			if ( x+j < 0 )
				return 0;
			if ( x+j >= W )
				return 0;
			if ( y+i >= H )
				return 0;
			if ( background[y+i][x+j] != 0 )
				return 0;
		}
	}

	return 1;
}

void draw_back( void )
{
	for (int i=0; i<H; i++) {
		for (int j=0; j<W; j++) {
			if ( background[i][j] != 0 ) {
				draw_element(j, i, FC);
			} else {
				draw_element(j, i, BC);
			}
		}
	}
}

void set_back(int x, int y, struct shape sh)
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if (sh.s[i][j] != 0 ) {
				background[y+i][x+j] = FC;
			}
		}
	}
}

void timer_tetris(struct data *p)
{
	draw_shape(p->x, p->y, shape_arr[cur], BC);
	if ( can_move(p->x, p->y+1, shape_arr[cur]) ) {
		p->y++;
	} else {
		set_back(p->x, p->y, shape_arr[cur]);
		clean_line();
		draw_back();
		t.x = 1;
		t.y = 0;
		cur = next;
		next = rand() % 7;
		show_next();
	}
	draw_shape(p->x, p->y, shape_arr[cur], FC);
}

struct shape turn_90(struct shape sp)
{
	struct shape t;
	
	for (int i=0; i<5; i++){
		for (int j=0; j<5; j++){
			t.s[i][j] = sp.s[4-j][i];
		}
	}

	return t;
}

int tetris(struct data *p)
{
	int ret = 0;
	int c = get_key();
	if ( is_up(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		shape_arr[cur] = turn_90(shape_arr[cur]);
		if ( !can_move(p->x, p->y, shape_arr[cur]) ) {
			shape_arr[cur] = turn_90(shape_arr[cur]);
			shape_arr[cur] = turn_90(shape_arr[cur]);
			shape_arr[cur] = turn_90(shape_arr[cur]);
		}
		draw_shape(p->x, p->y, shape_arr[cur], FC);
	}
	if ( is_down(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		if ( can_move(p->x, p->y+1, shape_arr[cur]) ) {
			p->y++;
		}
		draw_shape(p->x, p->y, shape_arr[cur], FC);
	}
	if ( is_left(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		if ( can_move(p->x-1, p->y, shape_arr[cur]) ) {
			p->x--;
		}
		draw_shape(p->x, p->y, shape_arr[cur], FC);
	}
	if ( is_right(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		if ( can_move(p->x+1, p->y, shape_arr[cur]) ) {
			p->x++;
		}
		draw_shape(p->x, p->y, shape_arr[cur], FC);
	}
	if ( is_esc(c) ) {
		ret = 1;
	}

	return ret;
}

