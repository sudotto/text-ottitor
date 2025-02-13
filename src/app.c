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
	for(int y = 0; y < 500; y++){
		inst.lines[y] = malloc(500);
		if(!fgets(inst.lines[y], 500, file_ptr)){
			for(int x = 0; x < 500; x++){
				if(inst.lines[y][x] == '\n'){
					inst.lines[y][x] = ' ';
					break;
				}
			}
			inst.line_count = y;
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
			strcat(contents, '\n');
		}
	}
	fprintf(file_ptr, contents);
	fclose(file_ptr);
}

void move_session_cursor(session* sesh, int x, int y){
	sesh->cursor_x += x;
	sesh->cursor_y += y;inst.lines[y][x]
	if(sesh->cursor_x < 0 || sesh->cursor_y < 0 || sesh->cursor_x >= 500 || sesh->cursor_y >= 500){
		sesh->cursor_x -= x;
		sesh->cursor_y -= y;
	}
	if(x){
		if(!sesh->lines[sesh->cursor_y][sesh->cursor_x]){
			sesh->lines[sesh->cursor_y][sesh->cursor_x] = ' ';
		}
	}
	if(y){
		if(sesh->cursor_y >= sesh->line_count){
			sesh->line_count++;
			sesh->lines[sesh->cursor_y][sesh->cursor_x] = ' ';
		}
		while(!sesh->lines[sesh->cursor_y][sesh->cursor_x]){
			sesh->cursor_x--;
		}
	}
}

void update_session(session* sesh, char* key){
	switch(*key){
		case 'w':
			move_session_cursor(sesh, 0, -1);
			break;
		case 'a':
			move_session_cursor(sesh, -1, 0);
			break;
		case 's':
			move_session_cursor(sesh, 0, 1);
			break;
		case 'd':
			move_session_cursor(sesh, 1, 0);
			break;
		case 'k':
			cycle_session_char(sesh, sesh->cursor_x, sesh->cursor_y);
			break;
		case 'l':
			cycle_session_char(sesh, sesh->cursor_x, sesh->cursor_y);
			break;
		case 'j':
			sesh->lines[sesh->cursor_y][sesh->cursor_x] = ' ';
			break;
	}
}

void cycle_session_char(session* sesh, int x, int y){
	sesh->lines[y][x]++;
	if(sesh->lines[y][x] > 126){
		sesh->lines[y][x] = 33;
	}
	if(sesh->lines[y][x] < 33){
		sesh->lines[y][x] = 126;
	}
}

void render_session(session* sesh, canvas* canv, int x, int y){
	// Dear future me:
	//    if you're trying to figure out why the file keeps getting cut off even when below 500 lines,
	//  you might have forgotten to increment sesh.line_count elsewhere
	char* line_num;
	for(int i = 0; i < sesh->line_count; i++){
		sprintf(line_num, "%i", i + 1);
		print_canvas(canv, line_num, false, x, i + y);
		print_canvas(canv, sesh->lines[i], false, x + 3, i + y);
		write_canvas(canv, sesh->lines[sesh->cursor_y][sesh->cursor_x], true, (sesh->cursor_x + x) + 3, sesh->cursor_y + y);
	}
}
