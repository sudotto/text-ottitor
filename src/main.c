#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>

#include "canvas.h"

char get_key(char* key) {
	struct termios old_term, new_term;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	*key = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

void topbar(canvas* canv){
	fill_line(canv, ' ', true, 0);
	print_canvas(canv, "file", true, 0, 0);
}

int main(int argc, char** argv){
	canvas canv = create_canvas();
	char key;
	while(key != 'q' && key != 'Q'){
		system("clear");

		topbar(&canv);

		render_canvas(&canv);
		get_key(&key);
	}
	return 0;
}
