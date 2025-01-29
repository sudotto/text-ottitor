#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#include "canvas.h"

///////////////////
// TERMINAL INFO
///////////////////

void get_term_size(int* w, int* h){
	struct winsize t;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &t);
	*w = t.ws_col;
	*h = t.ws_row;
}

///////////////////
// GLYPH STRUCTURE
///////////////////

glyph create_glyph(char c, bool inv){
	glyph inst;
	inst.c = c;
	inst.inv = inv;
	return inst;
}

///////////////////
// CANVAS STRUCTURE
///////////////////

canvas create_canvas(){
	canvas inst;
	int w, h;
	get_term_size(&w, &h);
	inst.w = w - 5;
	inst.h = h - 5;
	for(int y = 0; y <= h; y++){
		for(int x = 0; x <= w; x++){
			inst.glyphs[y][x] = create_glyph(' ', false);
		}
	}
	return inst;
}

void write_canvas(canvas* canv, char c, bool inv, int x, int y){
	if(x >= 0 && x <= canv->w && y >= 0 && y <= canv->h){
		canv->glyphs[y][x].c = c;
		canv->glyphs[y][x].inv = inv;
	}
}

void fill_line(canvas* canv, char c, bool inv, int line){
	for(int x = 0; x <= canv->w; x++){
		write_canvas(canv, c, inv, x, line);
	}
}

void fill_canvas(canvas* canv, char c, bool inv){
	for(int y = 0; y <= canv->h; y++){
		fill_line(canv, c, inv, y);
	}
}

void print_canvas(canvas* canv, char* str, bool inv, int x, int y){
	for(int i = 0; i < strlen(str); i++){
		write_canvas(canv, str[i], inv, x, y);
		x++;
	}
}

void render_canvas(canvas* canv){
	for(int y = 0; y <= canv->h; y++){
		for(int x = 0; x <= canv->w; x++){
			if(canv->glyphs[y][x].inv){
				printf("\033[7m");
			}
			printf("%c", canv->glyphs[y][x].c);
			printf("\033[0m");
		}
		printf("\n");
	}
}
