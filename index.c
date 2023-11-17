// Trivia Overdrive: A game project for my Microprocessors course, developed and released publicly.
// @license MIT
// @author Lexi Charron


// Include your required libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>

// Include your functions
#include "core.c"
#include "interface.c"
#include "sounds.c"


int main() {
    // Start the screen with standard options, then check if term size is correct
    InitializeScreen();
    signal(SIGWINCH, UpdateScreen); // Screen resizer signal

    // Declare & initialize this variable to sanitize all input to prevent small \
       screen disappearance (0 = Do not block input; 1 = Block input)
    int isInputBlocked = VerifyMinimumScreenSize();
    while (isInputBlocked == 1)
    {
        // Essentially check initially if the terminal is at the correct size \
           and if not, make them verify screen size before the intro sequence begins.
        mvwprintw(stdscr, 1, 1, "(i) Verify screen size.");
        wrefresh(stdscr);
    }
    clear();
    printw("(i) you have the minimum size requirements set.");
    wrefresh(stdscr);


    int ch;
    while((ch = getch()) != '\n')
    {
        // Handle global shortcuts
        switch (ch) {
            case KEY_F(1):
                endwin();
                return 0;
            case KEY_F(3):
                printw("sample text, ");
                break;
            case KEY_F(12):
                ShowLicense();
                break;
            default:
                break;
        }
    }
    endwin();
    return 0;
}