#ifndef __TETRIS_H_
#define __TETRIS_H_

void draw_element(int x, int y, int c);

void draw_back( void );

void draw_shape(int x, int y, struct shape p, int c);

void timer_tetris(struct data *p);

int tetris(struct data *p);

void show_next( void );

#endif //__TETRIS_H_

