#include <cstdio>
#include <ncurses.h>
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char** argv)
{
	printf("Welcome to Travelling Salesman\n");
	printf("Initializing ncurses.");
	// Running the setup functions for curses
	initscr();
	noecho();
	curs_set(FALSE); // Sets cursor to invisible ~~SPOOKY~~
	keypad(stdscr, true); // Allow curses to interpret escape sequences for us. Really not sure why this isn't a default feature.

	// Initialize colors
	if (has_colors() == false) {
		endwin();
		printf("Your terminal does not support color.");
		return 1; // Exit with error code
	}
	start_color();

	// Initial refresh
	refresh();

	/* Main Game Loop */
	bool running = true; // Set to false to stop the game
	while(running) {
		// get keypress in default state, substates can implement their own key handlers but must be called from here somehow
		char key = getch();
		switch(key) {
			case 27: // Escape key
				running = false;
				break;
		}
		
	}
	clear();
	mvprintw(LINES/2, COLS/2, "ENDING SESSION...");
	refresh();
	sleep(2);
	// Nicely Exit Ncurses, -- NOTE: Do not attempt to exit this program without first calling the functions below
	endwin();

	printf("\n\n\n");
	return 0;
}
