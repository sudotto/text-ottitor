#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "canvas.h"
#include "app.h"

///////////////////
// SESSION STRUCTURE
///////////////////

session create_session(char* filename){
	session inst;
	if(!fopen(filename, "r")){
		inst.load_fail = true;
		return inst;
	}
	FILE* file_ptr = fopen(filename, "r");
	inst.name = filename;
	for(int i = 0; i < 500; i++){
		inst.lines[i] = malloc(500);
		if(!fgets(inst.lines[i], 500, file_ptr)){
			inst.line_count = i;
			break;
		}
	}
	inst.cursor_x = 0;
	inst.cursor_y = 0;
	fclose(file_ptr);
	return inst;
}

void save_file(session* sesh){
	FILE* file_ptr = fopen(sesh->name, "w");
	fprintf(file_ptr, "");
	char* contents = malloc(500);
	for(int i = 0; i < 500; i++){
		if(sesh->lines[i]){
			strcat(contents, sesh->lines[i]);
			strcat(contents, "\n");
		}
	}
	fprintf(file_ptr, contents);
	fclose(file_ptr);
}

void update_session(session* sesh, char* key){
	switch(*key){
		case 'w':
			sesh->cursor_y -= 1;
			break;
		case 'a':
			sesh->cursor_x -= 1;
			break;
		case 's':
			sesh->cursor_y += 1;
			break;
		case 'd':
			sesh->cursor_x += 1;
			break;
		case 'k':
			cycle_session_char(sesh, sesh->cursor_x, sesh->cursor_y, 1);
			break;
		case 'l':
			cycle_session_char(sesh, sesh->cursor_x, sesh->cursor_y, -1);
			break;
		case 'j':
			sesh->lines[sesh->cursor_y][sesh->cursor_x] = ' ';
			break;
	}
}

void cycle_session_char(session* sesh, int x, int y, int amount){
	sesh->lines[y][x] += amount;
	if(sesh->lines[y][x] > 126){
		sesh->lines[y][x] = 33 + (sesh->lines[y][x] - 126);
	}
	if(sesh->lines[y][x] < 33){
		sesh->lines[y][x] = 126 - (sesh->lines[y][x] + 33);
	}
}

void render_session(session* sesh, canvas* canv){
	// Dear future me:
	//    if you're trying to figure out why the file keeps getting cut off even when below 500 lines,
	//  you might have forgotten to increment sesh.line_count elsewhere
	for(int i = 0; i < sesh->line_count; i++){
		print_canvas(canv, sesh->lines[i], false, 0, i + 1);
		write_canvas(canv, sesh->lines[sesh->cursor_y][sesh->cursor_x], true, sesh->cursor_x, sesh->cursor_y + 1);
	}
}
