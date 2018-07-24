#ifndef __DEF_H__
#define __DEF_H__

#define FC 3
#define BC 7

#define H 20
#define W 10

struct shape {
	int s[5][5];
};

struct data {
	int x;
	int y;
};

extern struct shape shape_arr[7];
extern struct data t;
extern int background[H][W];
extern int cur;
extern int next;


#endif // __DEF_H__

