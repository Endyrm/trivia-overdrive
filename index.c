// Trivia Overdrive: A game project for my Microprocessors course, developed and released publicly.
// @license MIT
// @author Lexi Charron


// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sndfile.h>
#include <fcntl.h>
#include <ncurses.h>
#include <panel.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

// Include program-specifc functions
#include "colors.c"
#include "utils.c"
#include "sounds.c"
#include "core.c"
#include "interface.c"



int main() {
    // Start the screen with standard options, then check if term size is correct
    InitializeScreen();
    signal(SIGWINCH, UpdateScreen); // Screen resizer signal

    // Check if input is blocked due to minimum size requirements. Avoids unintended behavior.
    int isInputBlocked;
    isInputBlocked = IsInputBlocked();

    do {
        // Essentially check initially if the terminal is at the correct size \
           and if not, make them verify screen size before the intro sequence begins.
        isInputBlocked = IsInputBlocked();
        if (isInputBlocked == 1) {
            mvwprintw(stdscr, 1, 1, "(i) Increase screen size, then press any key.");
            wrefresh(stdscr);
            getch();
        } else if (isInputBlocked == 0) {
            // I had no time or energy to fully make this program auto resize due to the time limitation.
            mvwprintw(stdscr, 1, 1, "(i) Make sure to not resize the screen during gameplay beyond this.");
            mvwprintw(stdscr, 2, 5, "You will avoid unintended yet unavoidable behavior by respecting this requirement.");
            mvwprintw(stdscr, 4, 5, "(Press any key to begin...)");
            getch();
        }
    } while (isInputBlocked == 1);
    clear();
    DefineColorPairs();
    // Start the intro sequence towards the main menu
    IntroSequence();
    // Main menu initialization -- from now on all UI code runs under interface.c functions
    MainMenu(1); // the 1 triggers the flash
    
    
    
    
    
    // Keybind test for debugging purposes
    
    endwin();
    printf("something made the program quit early\n");
    return 0;
}