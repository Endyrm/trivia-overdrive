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
    InitializeScreen();

    signal(SIGWINCH, UpdateScreen);

    for (int i = 0; i == 0;)
    {
        printw("heythere");
        int k = getch();

        if (k == 0)
        {
            endwin();
            return 0;
        }
        //endwin();
    }
    endwin();
    return 0;
}