// The user interface functions of Trivia Overdrive
// @license MIT
// @author Lexi Charron

#include <ncurses.h>

// function prototypes for general window manipulation
WINDOW *CreateNewWin(int height, int width, int startY, int startX);
WINDOW *CreateNewWinBoxed(int height, int width, int startY, int startX);
void DestroyWin(WINDOW *localWindow);





void UpdateScreen(int sig) {
    endwin();
    refresh();

    int varX = 0, varY = 0, smallScrTrig = -1;
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    switch (varX) { case 0 ... 9: varX = 1; break; case 10 ... 99: varX = 2; break; default: varX = 3; break;};
    switch (varY) { case 0 ... 9: varY = 1; break; case 10 ... 99: varY = 2; break; default: varY = 3; break;};
    int variableXLength = 20+varX;
    
    // TODO: make window data pause all inputs in favor for ensuring the resize \
       prompt does not disappear and carry on accepting inputs when it's too small. \
       Make it show the screen once the conflict is resolved, resume input afterwards.
    

    if (maxX < 80 || maxY < 20) {
        clear();
        WINDOW *resizeWin;

        resizeWin = CreateNewWinBoxed(5, 30, (maxY / 2) - 3, (maxX - 30) / 2);
        //int smallWin = newwin(maxY, maxX, 0, 0);
        mvwprintw(resizeWin, 1, 2, "Please resize your screen.");
        mvwprintw(resizeWin, 2, (5 - varX), "(Current size: %d, %d)", maxX, maxY);
        mvwprintw(resizeWin, 3, 4, "(Minimum size: 80, 20)");
        wrefresh(resizeWin); // Refresh the screen
    }

    
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




WINDOW *CreateNewWin(int height, int width, int startY, int startX)
{
    WINDOW *localWindow;

    // Create the window with a standard box on the border.
    localWindow = newwin(height, width, startY, startX);
    wrefresh(localWindow);

    return localWindow;
}

WINDOW *CreateNewWinBoxed(int height, int width, int startY, int startX)
{
    WINDOW *localWindow;

    // Create the window with a standard box on the border
    localWindow = newwin(height, width, startY, startX);
    box (localWindow, 0, 0);
    wrefresh(localWindow);

    return localWindow;
}