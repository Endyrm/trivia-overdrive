// Trivia Overdrive: A game project for my Microprocessors course, developed and released publicly.
// @license MIT
// @author Lexi Charron


// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <errno.h>

// Include program-specifc functions
#include "core.c"
#include "interface.c"
#include "sounds.c"
#include "utils.c"




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
        }
    } while (isInputBlocked == 1);
    clear();


    int ch;
    while((ch = getch()) != '\n')
    {
        isInputBlocked = IsInputBlocked();
        if (isInputBlocked == 0)
        {
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
    }
    endwin();
    return 0;
}