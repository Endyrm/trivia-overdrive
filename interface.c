// The user interface functions of Trivia Overdrive
// @license MIT
// @author Lexi Charron

#include <ncurses.h>


int UpdateScreen(int sig) {
    endwin();
    refresh();

    int varX = 0, varY = 0, smallScrTrig = -1;
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    switch (varX) { case 0 ... 9: varX = 1; break; case 10 ... 99: varX = 2; break; default: varX = 3; break;};
    switch (varY) { case 0 ... 9: varY = 1; break; case 10 ... 99: varY = 2; break; default: varY = 3; break;};
    int variableXLength = 20+varX;
    
    // The concept is to show this message on a window overlapping stdscr, though I evidently do not fully comprehend this for now.

    //if (smallScrTrig != 0)
    //{
    //    
    //    WINDOW *smallWin=newwin((maxY/2)-3, (maxX-28)/2, 5, 28);
    //    int createsmallWin = smallWin;
    //    box(smallWin, 0, 0);
    //}

    if (maxX < 80 || maxY < 20) {
        clear();
        
        //int smallWin = newwin(maxY, maxX, 0, 0);
        mvwprintw(stdscr, (maxY / 2) - 1, (maxX - 26) / 2, "Please resize your screen.");
        mvwprintw(stdscr, (maxY / 2), (maxX - variableXLength) / 2, "(Current size: %d, %d)", maxX, maxY);
        mvwprintw(stdscr, (maxY / 2) + 1, (maxX - 22) / 2, "(Minimum size: 80, 20)");
        wrefresh(stdscr); // Refresh the screen
    } //else {
    //    delwin("smallWin");
    //}

    
}

// This starts the screen function, along with required options
void InitializeScreen() {
    // Start the ncurses screen
    initscr();

    // Disable control characters; disable buffering, enable function/keypad keys
    raw();
    noecho();
    keypad(stdscr, TRUE);
}


