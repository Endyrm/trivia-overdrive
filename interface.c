// The user interface functions of Trivia Overdrive
// @license MIT
// @author Lexi Charron

#include <ncurses.h>

// function prototypes for general window manipulation
WINDOW *CreateNewWin(int height, int width, int startY, int startX);
WINDOW *CreateNewWinBoxed(int height, int width, int startY, int startX);
void DestroyWin(WINDOW *localWindow);

// Function prototypes for the interface
int VerifyMinimumScreenSize();


void IntroSequence() {

}

// SIGWINCH handler for dynamic screen resize
void UpdateScreen(int sig) {
    // Refresh the screen
    endwin();
    refresh();

    // Prevent early segfault
    if (VerifyMinimumScreenSize() == 1) {
        //mvwprintw(stdscr, 2, 1, "isInputBlocked = 1"); DEBUG
        return;
    } else if (VerifyMinimumScreenSize() == 0) {
        //mvwprintw(stdscr, 2, 1, "isInputBlocked = 0"); DEBUG
        return;
    }
}

// Verify the minimum screen size to ensure smooth sailing
int VerifyMinimumScreenSize()
{
    // Declare and initialize variables required for the resize window prompt
    int varX = 0, varY = 0, smallScrTrig = -1;
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    // Determine correct spacing for best attempt centering of text
    switch (varX) { case 0 ... 9: varX = 1; break; case 10 ... 99: varX = 2; break; default: varX = 3; break;};
    switch (varY) { case 0 ... 9: varY = 1; break; case 10 ... 99: varY = 2; break; default: varY = 3; break;};
    int variableXLength = 20+varX;
    
    // TODO: make window data pause all inputs in favor for ensuring the resize \
       prompt does not disappear and carry on accepting inputs when it's too small. \
       Make it show the screen once the conflict is resolved, resume input afterwards.
    

    // Check if the screen is below minimums
    if (maxX < 80 || maxY < 30) {
        // Clear the screen
        clear();

        // Create the window, center it on the screen and place important text into it
        WINDOW *resizeWin;
        resizeWin = CreateNewWinBoxed(5, 30, (maxY / 2) - 2, (maxX - 30) / 2);
        mvwprintw(resizeWin, 1, 2, "Please resize your screen.");
        mvwprintw(resizeWin, 2, (5 - varX), "(Current size: %d, %d)", maxX, maxY);
        mvwprintw(resizeWin, 3, 4, "(Minimum size: 80, 30)");
        wrefresh(resizeWin); 
        return 1;
    } 
    return 0;
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

// There is likely a smarter way to do this, but I have limited time. \
   This function prints out the MIT license on screen.
void ShowLicense() {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    WINDOW *licenseWindow;
    licenseWindow = CreateNewWinBoxed(30, 80, (maxY / 2) - 15, (maxX - 80) / 2);

    // Print out the MIT license
    mvwprintw(licenseWindow, 1, 1, "Copyright (c) 2023 Lexi Charron");

    mvwprintw(licenseWindow, 3, 1, "Permission is hereby granted, free of charge, to any person obtaining a copy");
    mvwprintw(licenseWindow, 4, 1, "of this software and associated documentation files (the \"Software\"), to deal");
    mvwprintw(licenseWindow, 5, 1, "in the Software without restriction, including without limitation the rights");
    mvwprintw(licenseWindow, 6, 1, "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell");
    mvwprintw(licenseWindow, 7, 1, "copies of the Software, and to permit persons to whom the Software is");
    mvwprintw(licenseWindow, 8, 1, "furnished to do so, subject to the following conditions:");

    mvwprintw(licenseWindow, 10, 1, "The above copyright notice and this permission notice shall be included in all");
    mvwprintw(licenseWindow, 11, 1, "copies or substantial portions of the Software.");

    mvwprintw(licenseWindow, 13, 1, "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
    mvwprintw(licenseWindow, 14, 1, "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
    mvwprintw(licenseWindow, 15, 1, "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE");
    mvwprintw(licenseWindow, 16, 1, "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
    mvwprintw(licenseWindow, 17, 1, "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
    mvwprintw(licenseWindow, 18, 1, "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
    mvwprintw(licenseWindow, 19, 1, "SOFTWARE.");

    // Tell the user how to exit this prompt, then exit.
    mvwprintw(licenseWindow, 29, 20, " (i): Press any key to exit this prompt ");
    wrefresh(licenseWindow);
    getch();
    DestroyWin(licenseWindow);
    clear();
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

void DestroyWin(WINDOW *localWindow) {
    // Remove the border, refresh the window and then destroy it.
    wborder(localWindow, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(localWindow);
    delwin(localWindow);
}