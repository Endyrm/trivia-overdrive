// The user interface functions of Trivia Overdrive
// @license MIT
// @author Lexi Charron

#include <ncurses.h>
#include <panel.h>

WINDOW *mainWindow[10];
PANEL *mainPanel[10];

// function prototypes for general window manipulation
WINDOW *CreateNewWin(int height, int width, int startY, int startX);
WINDOW *CreateNewWinBoxed(int height, int width, int startY, int startX);
void DestroyWin(WINDOW *localWindow);

// Function prototypes for the interface
void VerifyMinimumScreenSize();
int IsInputBlocked();
void ShowLicense();

int maxY, maxX;



void IntroSequence() {
    
    getmaxyx(stdscr, maxY, maxX);
    // Create each component of the main window
    mainWindow[0] = CreateNewWinBoxed(30, 80, (maxY / 2) - 15, (maxX - 80) / 2);
    mainWindow[1] = CreateNewWinBoxed(6, 40, (maxY / 2) - 9, (maxX - 40) / 2);
    // Set them as panels for the refresh order. from now on, panel utilities are prefered.
    mainPanel[0] = new_panel(mainWindow[0]);
    mainPanel[1] = new_panel(mainWindow[1]);
    mvwprintw(mainWindow[1], 2, 4, "Copyright (C) Lexi Charron, 2023");
    mvwprintw(mainWindow[1], 3, 5, "Licensed under the MIT license");

    // Transition the screen from the intro to main menu
    int i;
    for (i = 0; i <=24; i++)
    {
        // Set the colors of the windows + smooth text transition
        int d = i;
        if (i > 11) { d = i+13; }
        wbkgd(mainWindow[0], COLOR_PAIR(i));
        wbkgd(mainWindow[1], COLOR_PAIR(d));
        update_panels();
        doupdate();
    
        // Calculate a smooth transition while allowing for 2 second read time
        int ms = 250 - (i*10);
        if (i == 0) {ms = 2000; } else if (ms < 50) { ms = 50; };
        msleep(ms);
    }
    // Wait a second before transitioning, also kill the copyright notice
    del_panel(mainPanel[1]);
    DestroyWin(mainWindow[1]);
    msleep(1000);
    for (i = 24; i >=0; i--)
    {
        wbkgd(mainWindow[0], COLOR_PAIR(i));
        update_panels();
        doupdate();
    
        // Calculate a smooth transition while allowing for a 1.2 second pause
        int ms = 250 - (i*10);
        if (i == 0) {ms = 1200; } else if (ms < 50) { ms = 50; };
        msleep(ms);
    }


    // Create a window & panel to do a cool transition
    mainWindow[1] = CreateNewWin(6, 50, (maxY / 2) - 9, (maxX - 50) / 2);
    mainPanel[1] = new_panel(mainWindow[1]);
    mvwprintw(mainWindow[1], 0, 3, "__        __   _                          ");
    mvwprintw(mainWindow[1], 1, 3, "\\ \\      / /__| | ___ ___  _ __ ___   ___ ");
    mvwprintw(mainWindow[1], 2, 3, " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\");
    mvwprintw(mainWindow[1], 3, 3, "  \\ V  V /  __/ | (_| (_) | | | | | |  __/");
    mvwprintw(mainWindow[1], 4, 3, "   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|");
    // play a boom sound
    update_panels();
    doupdate();
    msleep(1000);
    wclear(mainWindow[1]);

    mvwprintw(mainWindow[1], 0, 18, " _____     ");
    mvwprintw(mainWindow[1], 1, 18, "|_   _|__  ");
    mvwprintw(mainWindow[1], 2, 18, "  | |/ _ \\ ");
    mvwprintw(mainWindow[1], 3, 18, "  | | (_) |");
    mvwprintw(mainWindow[1], 4, 18, "  |_|\\___/ ");
    // play a boom sound
    update_panels();
    doupdate();
    msleep(1000);
    del_panel(mainPanel[1]);
    DestroyWin(mainWindow[1]);
}

// Main menu code
void MainMenu(int isFirstRun)
{
    if (isFirstRun == 1) {
        for (int i = 24; i > 0; i--)
        {
            int d = i;
            if (i == 0) { d = 38; }
            wbkgd(mainWindow[0], COLOR_PAIR(d));
            update_panels();
            doupdate();
    
            // Calculate a smooth flash
            int ms = 50;
            if (i == 0) {ms = 5; }
            msleep(ms);
        }
    }
    wbkgd(mainWindow[0], COLOR_PAIR(38));
    update_panels();
    doupdate();
    // Create relevant windows and panels, set the correct background colors
    mainWindow[1] = CreateNewWin(7,  72, (maxY / 2) - 14, (maxX - 72) / 2); // title
    mainWindow[2] = CreateNewWin(20, 54, (maxY / 2) -  6, (maxX - 30) / 2); // cute ascii artpiece
    mainWindow[3] = CreateNewWin(3,  15, (maxY / 2) -  3, (maxX - 70) / 2); // play button
    mainWindow[4] = CreateNewWin(3,  15, (maxY / 2) +  3, (maxX - 60) / 2); // options button
    mainWindow[5] = CreateNewWin(3,  15, (maxY / 2) +  9, (maxX - 50) / 2); // exit button
    mainPanel[1] = new_panel(mainWindow[1]);
    mainPanel[2] = new_panel(mainWindow[2]);
    mainPanel[3] = new_panel(mainWindow[3]);
    mainPanel[4] = new_panel(mainWindow[4]);
    mainPanel[5] = new_panel(mainWindow[5]);
    for (int i = 1; i <= 5; i++) { wbkgd(mainWindow[i], COLOR_PAIR(38)); }

    // Strings of the title text, ascii art strings
    char titleText_row0[72] = " _____     _       _          ___                    _      _           ";
    char titleText_row1[72] = "|_   _| __(_)_   _(_) __ _   / _ \\__   _____ _ __ __| |_ __(_)_   _____ ";
    char titleText_row2[72] = "  | || '__| \\ \\ / / |/ _` | | | | \\ \\ / / _ \\ '__/ _` | '__| \\ \\ / / _ \\";
    char titleText_row3[72] = "  | || |  | |\\ V /| | (_| | | |_| |\\ V /  __/ | | (_| | |  | |\\ V /  __/";
    char titleText_row4[72] = "  |_||_|  |_| \\_/ |_|\\__,_|  \\___/  \\_/ \\___|_|  \\__,_|_|  |_| \\_/ \\___|";
    char titleText_row6[72] = "             Test your knowledge up to the absolute limits!             ";

    char asciiArt[20][54] = {
        { "                                     )                " },
        { "                            )      ((     (           " },
        { "                           (        ))     )          " },
        { "                    )       )      //     (           " },
        { "               _   (        __    (     ~->>          " },
        { "        ,-----' |__,_~~___<'__`)-~__--__-~->> <       " },
        { "        | //  : | -__   ~__ o)____)),__ - '> >-  >    " },
        { "        | //  : |- \\_ \\ -\\_\\ -\\ \\ \\ ~\\_  \\ ->> - ,  >>" },
        { "        | //  : |_~_\\ -\\__\\ \\~'\\ \\ \\, \\__ . -<-  >>   " },
        { "        `-----._| `  -__`-- - ~~ -- ` --~> >          " },
        { "         _/___\\_    //)_`//  | ||]                    " },
        { "   _____[_______]_[~~-_ (.L_/  ||                     " },
        { "  [____________________]' `\\_,/'/                     " },
        { "    ||| /          |||  ,___,'./                      " },
        { "    ||| \\          |||,'______|                       " },
        { "    ||| /          /|| I==||                          " },
        { "    ||| \\       __/_||  __||__                        " },
        { "-----||-/------`-._/||-o--o---o---                    " },
        { "  ~~~~~'                                              " },
        { "                                                      " }
    };

    // button labels
    char startBtn[4][15] =
    {
        { "             " },
        { " --> START <-- " },
        { "     START     " },
        { "             " }
    };
    char optionsBtn[4][15] =
    {
        { "             " },
        { " -> OPTIONS <- " },
        { "    OPTIONS    " },
        { "             " }
    };
    char exitBtn[4][15] =
    {
        { "             " },
        { " --> LEAVE <-- " },
        { "     LEAVE     " },
        { "             " }
    };

    wbkgd(mainWindow[2], COLOR_PAIR(41));
    // Animate the assembly of all intro elements
    for (int i = 0; i <= 100; i++)
    {
        // Reveal the title, letter by letter
        if (i >=  0) { mvwaddch(mainWindow[1], 0, i,    titleText_row0[i]    | A_BOLD | COLOR_PAIR(39) ); }
        if (i >=  5) { mvwaddch(mainWindow[1], 1, i-5,  titleText_row1[i-5]  | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 10) { mvwaddch(mainWindow[1], 2, i-10, titleText_row2[i-10] | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 15) { mvwaddch(mainWindow[1], 3, i-15, titleText_row3[i-15] | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 20) { mvwaddch(mainWindow[1], 4, i-20, titleText_row4[i-20] | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 25) { mvwaddch(mainWindow[1], 6, i-25, titleText_row6[i-25] | A_BOLD | COLOR_PAIR(39) ); }

        // "Start playing" button
        if (i == 30) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v >= 2) { mvwaddch(mainWindow[3], 0, u, startBtn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[3], 1, v, startBtn[1][v] | COLOR_PAIR(40) | A_BOLD);
                       if (u >= 2) { mvwaddch(mainWindow[3], 2, u, startBtn[3][v] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Options" button
        if (i == 50) { 
                    for (int v = 0; v < 15; v++)
                    {
                       mvwaddch(mainWindow[4], 0, 0, optionsBtn[0][v] | COLOR_PAIR(40) | A_BOLD);
                       mvwaddch(mainWindow[4], 1, 0, optionsBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       mvwaddch(mainWindow[4], 2, 2, optionsBtn[3][v] | COLOR_PAIR(40) | A_BOLD);
                    }
                     }
        // "Exit game" button
        if (i == 70) { 
                    for (int v = 0; v < 15; v++)
                    {
                       mvwaddch(mainWindow[5], 0, 0, exitBtn[0][v] | COLOR_PAIR(40) | A_BOLD);
                       mvwaddch(mainWindow[5], 1, 0, exitBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       mvwaddch(mainWindow[5], 2, 2, exitBtn[3][v] | COLOR_PAIR(40) | A_BOLD);
                    }
                     }

        // Ascii art, which reveals character-by character just like with the title
        int d = 100 - i;
        if (d <= 100 && d >= 28) { mvwaddch(mainWindow[2], 20, d-29, asciiArt[19][d-29]); }
        if (d <=  99 && d >= 27) { mvwaddch(mainWindow[2], 19, d-28, asciiArt[18][d-28]); }
        if (d <=  98 && d >= 26) { mvwaddch(mainWindow[2], 18, d-27, asciiArt[17][d-27]); }
        if (d <=  97 && d >= 25) { mvwaddch(mainWindow[2], 17, d-26, asciiArt[16][d-26]); }
        if (d <=  96 && d >= 24) { mvwaddch(mainWindow[2], 16, d-25, asciiArt[15][d-25]); }
        if (d <=  95 && d >= 23) { mvwaddch(mainWindow[2], 15, d-24, asciiArt[14][d-24]); }
        if (d <=  94 && d >= 22) { mvwaddch(mainWindow[2], 14, d-23, asciiArt[13][d-23]); }
        if (d <=  93 && d >= 21) { mvwaddch(mainWindow[2], 13, d-22, asciiArt[12][d-22]); }
        if (d <=  92 && d >= 20) { mvwaddch(mainWindow[2], 12, d-21, asciiArt[11][d-21]); }
        if (d <=  91 && d >= 19) { mvwaddch(mainWindow[2], 11, d-20, asciiArt[10][d-20]); }
        if (d <=  90 && d >= 18) { mvwaddch(mainWindow[2], 10, d-19, asciiArt[9][d-19]); }
        if (d <=  89 && d >= 17) { mvwaddch(mainWindow[2],  9, d-18, asciiArt[8][d-18]); }
        if (d <=  88 && d >= 16) { mvwaddch(mainWindow[2],  8, d-17, asciiArt[7][d-17]); }
        if (d <=  87 && d >= 15) { mvwaddch(mainWindow[2],  7, d-16, asciiArt[6][d-16]); }
        if (d <=  86 && d >= 14) { mvwaddch(mainWindow[2],  6, d-15, asciiArt[5][d-15]); }
        if (d <=  85 && d >= 13) { mvwaddch(mainWindow[2],  5, d-14, asciiArt[4][d-14]); }
        if (d <=  84 && d >= 12) { mvwaddch(mainWindow[2],  4, d-13, asciiArt[3][d-13]); }
        if (d <=  83 && d >= 11) { mvwaddch(mainWindow[2],  3, d-12, asciiArt[2][d-12]); }
        if (d <=  82 && d >= 10) { mvwaddch(mainWindow[2],  2, d-11, asciiArt[1][d-11]); }
        if (d <=  81 && d >=  9) { mvwaddch(mainWindow[2],  1, d-10, asciiArt[0][d-10]); }
        update_panels();
        doupdate();

        msleep(25);
    }

    // The menu keybinds and logic for responsive UI
    int isInputBlocked, ch, selector = 1;
    isInputBlocked = IsInputBlocked();
    while((ch = getch()) != KEY_F(13)) // F13 is a nonstandard key
    {
        // Set the correct highlight indicator
        if (selector == 1)
        {
            mvwaddstr(mainWindow[3], 1, 0, startBtn[1]);
            mvwaddstr(mainWindow[4], 1, 0, optionsBtn[2]);
            mvwaddstr(mainWindow[5], 1, 0, exitBtn[2]);
        } else if (selector == 2)
        {
            mvwaddstr(mainWindow[3], 1, 0, startBtn[2]);
            mvwaddstr(mainWindow[4], 1, 0, optionsBtn[1]);
            mvwaddstr(mainWindow[5], 1, 0, exitBtn[2]);
        } else if (selector == 3)
        {
            mvwaddstr(mainWindow[3], 1, 0, startBtn[2]);
            mvwaddstr(mainWindow[4], 1, 0, optionsBtn[2]);
            mvwaddstr(mainWindow[5], 1, 0, exitBtn[1]);
        }
        update_panels();
        doupdate();

        isInputBlocked = IsInputBlocked();
        if (isInputBlocked == 0)
        {
            mvprintw(maxY-1, 0, "[main/DEBUG]: lastkeypress: %u  \n", ch);
            switch (ch) {
                case KEY_UP:
                case KEY_LEFT:
                // Make the selector move backwards
                selector--;
                if (selector < 1) { selector = 3; }
                mvprintw(maxY-2, 0, "[main/DEBUG]: selector is: %d  ", selector);
                break;
                case KEY_DOWN:
                case KEY_RIGHT:
                // Make the selector move forward
                selector++;
                if (selector > 3) { selector = 1; }
                mvprintw(maxY-2, 0, "[main/DEBUG]: selector is: %d  ", selector);
                break;
                case KEY_F(1):
                    endwin();
                    exit(0);
                case 10: // ASCII code of newline
                case 13: // ASCII code of carriage return (kinda like a newline)
                switch(selector)
                {
                    case 1:
                        // call start game function
                        break;
                    case 2:
                        // call options menu, temp junk for now
                        ShowLicense();
                        MainMenu(0);
                        break;
                    case 3:
                        // call a quit function, for now we will just endwin()
                        endwin();
                        exit(0);
                }
               default:
                    break;
            }
        }
    }
}

// SIGWINCH handler for dynamic screen resize
void UpdateScreen(int sig) {
    // Refresh the screen
    endwin();
    refresh();
    update_panels();

    VerifyMinimumScreenSize();
}

// Verify the minimum screen size to ensure smooth sailing
void VerifyMinimumScreenSize()
{
    // Declare and initialize variables required for the resize window prompt
    int varX = 0, varY = 0, smallScrTrig = -1;

    getmaxyx(stdscr, maxY, maxX);

    // Determine correct spacing for best attempt centering of text
    switch (varX) { case 0 ... 9: varX = 1; break; case 10 ... 99: varX = 2; break; default: varX = 3; break;};
    switch (varY) { case 0 ... 9: varY = 1; break; case 10 ... 99: varY = 2; break; default: varY = 3; break;};
    int variableXLength = 20+varX;

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
    
    }
    refresh();
    update_panels(); 
}

// Helper to block input when not required
int IsInputBlocked() {
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    if (maxX < 80 || maxY < 30) {
        // Block input
        return 1;
    } else {
        // Don't block input
        return 0;
    }
}

// This starts the screen function, along with required options
void InitializeScreen() {
    // Start the ncurses screen with color
    initscr();
    start_color();

    // Disable control characters; invisible cursor; disable buffering, enable function/keypad keys
    curs_set(0);
    cbreak();
    noecho();
    nonl();
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

