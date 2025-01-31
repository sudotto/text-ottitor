#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>

#include "canvas.h"
#include "app.h"

void get_key(char* key) {
	struct termios old_term, new_term;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	*key = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

void topbar(canvas* canv, session sesh){
	fill_line(canv, ' ', true, 0);
	print_canvas(canv, sesh.name, true, 0, 0);
}

int main(int argc, char** argv){
	canvas canv = create_canvas();
	char key;
	if(!argv[1]){
		printf("\033[31m[ERROR] Provide a file jackass\033[0m\n");
		return 1;
	}
	session sesh = create_session(argv[1]);
	if(sesh.load_fail){
		printf("\033[31m[ERROR] %s isn't a real file dipshit\033[0m\n", argv[1]);
		return 1;
	}
	bool running = true;
	while(running){
		system("clear");
		//fill_canvas(&canv, '-', false);
		topbar(&canv, sesh);
		update_session(&sesh, &key);
		render_session(&sesh, &canv);
		render_canvas(&canv);

		get_key(&key);
		switch(key){
			case 'q':
				running = false;
				system("clear");
				printf("\033[34m[INFO] closed without saving hahaha\033[0m\n");
				break;
			case 'f':
				save_file(&sesh);
				running = false;
				system("clear");
				printf("\033[34m[INFO] closed and saved\033[0m\n");
				break;
		}
	}

	return 0;
}
