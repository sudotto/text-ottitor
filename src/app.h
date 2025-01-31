#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "canvas.h"

///////////////////
// SESSION STRUCTURE
///////////////////

typedef struct {
	FILE* file_ptr;
	char* name;
	char* lines[500];
	int cursor_x;
	int cursor_y;
	bool load_fail;
	int line_count;
} session;

session create_session(char* filename);
void save_file(session* sesh);
void update_session(session* sesh, char* key);
void cycle_session_char(session* sesh, int x, int y, int amount);
void render_session(session* sesh, canvas* canv);

#endif
