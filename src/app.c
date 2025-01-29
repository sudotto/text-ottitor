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
	for(int i = 0; i < 200; i++){
		inst.lines[i] = malloc(200);
		if(!fgets(inst.lines[i], 200, file_ptr)){
			inst.line_count = i;
			break;
		}
		inst.lines[i][strcspn(inst.lines[i], "\n")] = '\0';
	}
	inst.cursor_x = 0;
	inst.cursor_y = 0;
	fclose(file_ptr);
	return inst;
}

void render_session(session* sesh, canvas* canv){
	// Dear future me:
	//    if you're trying to figure out why the file keeps getting cut off even when below 500 lines,
	//  you might have forgotten to increment sesh.line_count elsewhere
	for(int i = 0; i < sesh->line_count; i++){
		print_canvas(canv, sesh->lines[i], false, 0, i + 1);
	}
}
