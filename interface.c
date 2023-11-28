// The user interface functions of Trivia Overdrive
// @license MIT
// @author Lexi Charron

#include <ncurses.h>
#include <panel.h>

WINDOW *mainWindow[10];
PANEL *mainPanel[10];

WINDOW *sessionWindow[10];
PANEL *sessionPanel[10];

// function prototypes for general window manipulation
WINDOW *CreateNewWin(int height, int width, int startY, int startX);
WINDOW *CreateNewWinBoxed(int height, int width, int startY, int startX);
void DestroyWin(WINDOW *localWindow);
void wraptxtw(WINDOW* localWindow, const char* input, int maxWidth);

// Function prototypes for the interface
void VerifyMinimumScreenSize();
int IsInputBlocked();
void ShowLicense();
void IntroSequence();
void MainMenu();
void StartGameTopicSelect();
void StartGameSession(int topic);

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
        { " -> LICENSE <- " },
        { "    LICENSE    " },
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
                       if (v <= 12) { mvwaddch(mainWindow[3], 0, v, startBtn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[3], 1, v, startBtn[1][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[3], 2, v, startBtn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Options" button
        if (i == 50) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[4], 0, v, optionsBtn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[4], 1, v, optionsBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[4], 2, v, optionsBtn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Exit game" button
        if (i == 70) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[5], 0, v, exitBtn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[5], 1, v, exitBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[5], 2, v, exitBtn[3][u] | COLOR_PAIR(40) | A_BOLD); }
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
       
        // Update the screen every 25ms as per the animation's speed
        update_panels();
        doupdate();
        msleep(25);
    }

    // Add the input hints at the bottom of the window, then update screen
    mvwprintw(mainWindow[0], 29, 3, " (F1): Exit Now ");
    mvwprintw(mainWindow[0], 29, 31, " (^) (<) (v) (>) ");
    mvwprintw(mainWindow[0], 29, 60, " (ENTER): Select ");
    update_panels();
    doupdate();

    // The menu keybinds and logic for responsive UI
    int isInputBlocked, ch, selector = 1;
    isInputBlocked = IsInputBlocked();
    while((ch = getch()) != KEY_F(13)) // F13 is a nonstandard key
    {
        
        msleep(25);

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
                        // Remove all main menu-specific windows
                        del_panel(mainPanel[1]); DestroyWin(mainWindow[1]);
                        del_panel(mainPanel[2]); DestroyWin(mainWindow[2]);
                        del_panel(mainPanel[3]); DestroyWin(mainWindow[3]);
                        del_panel(mainPanel[4]); DestroyWin(mainWindow[4]);
                        del_panel(mainPanel[5]); DestroyWin(mainWindow[5]);

                        // Then start the game with the topic selector
                        StartGameTopicSelect();
                        break;
                    case 2:
                        // call license menu after removing main menu windows
                        del_panel(mainPanel[1]); DestroyWin(mainWindow[1]);
                        del_panel(mainPanel[2]); DestroyWin(mainWindow[2]);
                        del_panel(mainPanel[3]); DestroyWin(mainWindow[3]);
                        del_panel(mainPanel[4]); DestroyWin(mainWindow[4]);
                        del_panel(mainPanel[5]); DestroyWin(mainWindow[5]);
                        update_panels(); doupdate();

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

        // refresh the buttons for responsiveness
        if (selector == 1)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwaddch(mainWindow[3], 1, v, startBtn[1][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, optionsBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, exitBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
            }
        } else if (selector == 2)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwaddch(mainWindow[3], 1, v, startBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, optionsBtn[1][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, exitBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
            }
        } else if (selector == 3)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwaddch(mainWindow[3], 1, v, startBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, optionsBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, exitBtn[1][v] | COLOR_PAIR(40) | A_BOLD);
            }
        }
        update_panels();
        doupdate();
    }
}


void StartGameTopicSelect()
{
    // Flash the screen as we show the topic selector
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
    // Set the right background color of the window
    wbkgd(mainWindow[0], COLOR_PAIR(38));

    // Create the relevant windows for topic selection, set correct background color
    mainWindow[1] = CreateNewWin(7,  72, (maxY / 2) - 14, (maxX - 72) / 2); // menu title
    mainWindow[2] = CreateNewWin(3,  15, (maxY / 2) -  3, (maxX - 60) / 2); // random topic button
    mainWindow[3] = CreateNewWin(3,  15, (maxY / 2) +  3, (maxX - 50) / 2); // Butchery topic button
    mainWindow[4] = CreateNewWin(3,  15, (maxY / 2) +  9, (maxX - 60) / 2); // Cities of Canada topic button
    mainWindow[5] = CreateNewWin(3,  15, (maxY / 2) -  3, (maxX + 30) / 2); // Social Media Platforms topic button
    mainWindow[6] = CreateNewWin(3,  15, (maxY / 2) +  3, (maxX + 20) / 2); // Elements topic button
    mainWindow[7] = CreateNewWin(3,  15, (maxY / 2) +  9, (maxX + 30) / 2); // Web Browser topic button
    mainWindow[8] = CreateNewWin(1,  78, (maxY / 2) -  6, (maxX - 78) / 2); // Context selection for exact topic name
    mainPanel[1] = new_panel(mainWindow[1]);
    mainPanel[2] = new_panel(mainWindow[2]);
    mainPanel[3] = new_panel(mainWindow[3]);
    mainPanel[4] = new_panel(mainWindow[4]);
    mainPanel[5] = new_panel(mainWindow[5]);
    mainPanel[6] = new_panel(mainWindow[6]);
    mainPanel[7] = new_panel(mainWindow[7]);
    mainPanel[8] = new_panel(mainWindow[8]);
    for (int i = 1; i <= 8; i++) { wbkgd(mainWindow[i], COLOR_PAIR(38)); }
    update_panels();
    doupdate();


    // Text graphics of all the window elements
    char menuTitle[7][72] = {
        { " ____       _           _                   _____           _        _  " },
        { "/ ___|  ___| | ___  ___| |_       __ _     |_   _|__  _ __ (_) ___  | | " },
        { "\\___ \\ / _ \\ |/ _ \\/ __| __|     / _` |      | |/ _ \\| '_ \\| |/ __| | | " },
        { " ___) |  __/ |  __/ (__| |_     | (_| |      | | (_) | |_) | | (__  |_| " },
        { "|____/ \\___|_|\\___|\\___|\\__|     \\__,_|      |_|\\___/| .__/|_|\\___| (_) " },
        { "                                                     |_|                " },
        { "       Select the topic you would like to test your skills with!        " }
    };

    char randTopicBtn[4][15] =
    {
        { "             " },
        { " -> RANDOM! <- " },
        { "    RANDOM!    " },
        { "             " }
    };

    char topic1Btn[4][15] =
    {
        { "             " },
        { " --> MEATS <-- " },
        { "     MEATS     " },
        { "             " }
    };

    char topic2Btn[4][15] =
    {
        { "             " },
        { " --> TOWNS <-- " },
        { "     TOWNS     " },
        { "             " }
    };

    char topic3Btn[4][15] =
    {
        { "             " },
        { " --> MEDIA <-- " },
        { "     MEDIA     " },
        { "             " }
    };

    char topic4Btn[4][15] =
    {
        { "             " },
        { " -> ELEMENT <- " },
        { "    ELEMENT    " },
        { "             " }
    };

    char topic5Btn[4][15] =
    {
        { "             " },
        { " -> BROWSER <- " },
        { "    BROWSER    " },
        { "             " }
    };

    // Start the animation immediately after the flash
    for (int i = 0; i <= 100; i++)
    {
        // Have the menu-specific title appear character by character
        if (i >=  0) { mvwaddch(mainWindow[1], 0, i,    menuTitle[0][i]    | A_BOLD | COLOR_PAIR(39) ); }
        if (i >=  5) { mvwaddch(mainWindow[1], 1, i-5,  menuTitle[1][i-5]  | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 10) { mvwaddch(mainWindow[1], 2, i-10, menuTitle[2][i-10] | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 15) { mvwaddch(mainWindow[1], 3, i-15, menuTitle[3][i-15] | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 20) { mvwaddch(mainWindow[1], 4, i-20, menuTitle[4][i-20] | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 25) { mvwaddch(mainWindow[1], 5, i-25, menuTitle[5][i-25] | A_BOLD | COLOR_PAIR(39) ); }
        if (i >= 30) { mvwaddch(mainWindow[1], 6, i-30, menuTitle[6][i-30] | A_BOLD | COLOR_PAIR(39) ); }



        // "Random selection" button
        if (i == 30) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[2], 0, v, randTopicBtn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[2], 1, v, randTopicBtn[1][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[2], 2, v, randTopicBtn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Butchery" button
        if (i == 40) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[3], 0, v, topic1Btn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[3], 1, v, topic1Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[3], 2, v, topic1Btn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Cities of Canada" button
        if (i == 50) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[4], 0, v, topic2Btn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[4], 1, v, topic2Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[4], 2, v, topic2Btn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Social Media Platforms" button
        if (i == 60) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[5], 0, v, topic3Btn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[5], 1, v, topic3Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[5], 2, v, topic3Btn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Elements" button
        if (i == 70) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[6], 0, v, topic4Btn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[6], 1, v, topic4Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[6], 2, v, topic4Btn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }
        // "Web Browsers" button
        if (i == 80) { 
                    for (int v = 0; v < 15; v++)
                    {
                       int u = v-2;
                       if (v <= 12) { mvwaddch(mainWindow[7], 0, v, topic5Btn[0][v] | COLOR_PAIR(40) | A_BOLD); }
                       mvwaddch(mainWindow[7], 1, v, topic5Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                       if (v >= 2) { mvwaddch(mainWindow[7], 2, v, topic5Btn[3][u] | COLOR_PAIR(40) | A_BOLD); }
                    }
                     }



        update_panels();
        doupdate();
        msleep(25);
    }
    
    
    // The menu keybinds and logic for responsive UI
    int isInputBlocked, ch, selectorX = 1, selectorY = 1, selector = 1;
    isInputBlocked = IsInputBlocked();
    mvwprintw(mainWindow[8], 0, 20, "     Choose at random.. Spooky!     ");
    update_panels(); doupdate();
    while((ch = getch()) != KEY_F(13)) // F13 is a nonstandard key
    {
        
        msleep(25);

        isInputBlocked = IsInputBlocked();
        if (isInputBlocked == 0)
        {
            mvprintw(maxY-1, 0, "[main/DEBUG]: lastkeypress: %u  \n", ch);
            switch (ch) {
                case KEY_UP:
                // Move upwards
                selectorY--;
                if (selectorY < 1) { selectorY = 3; }
                mvprintw(maxY-2, 0, "[main/DEBUG]: selector is: (%d, %d)  ", selectorX, selectorY);
                break;
                case KEY_LEFT:
                // Move left
                selectorX--;
                if (selectorX < 1) { selectorX = 2; }
                mvprintw(maxY-2, 0, "[main/DEBUG]: selector is: (%d, %d)  ", selectorX, selectorY);
                break;
                case KEY_DOWN:
                // Move downwards
                selectorY++;
                if (selectorY > 3) { selectorY = 1; }
                mvprintw(maxY-2, 0, "[main/DEBUG]: selector is: (%d, %d)  ", selectorX, selectorY);
                break;
                case KEY_RIGHT:
                // Move left
                selectorX++;
                if (selectorX > 2) { selectorX = 1; }
                mvprintw(maxY-2, 0, "[main/DEBUG]: selector is: (%d, %d)  ", selectorX, selectorY);
                break;
                case KEY_F(1):
                    endwin();
                    exit(0);
                case 10: // ASCII code of newline
                case 13: // ASCII code of carriage return (kinda like a newline)
                switch(selectorX)
                {
                    case 1:
                        // first row of buttons
                        switch(selectorY)
                        {
                            case 1:
                            break;
                            case 2:
                            break;
                            case 3:
                            break;
                            default:
                            break;
                        }
                        break;
                    case 2:
                        // second row of buttons
                        switch(selectorY)
                        {
                            case 1:
                            break;
                            case 2:
                            break;
                            case 3:
                            refresh();
                            StartGameSession(5);
                            break;
                            default:
                            break;
                        }
                        break;
                    default:
                    break;
                }
               default:
                    break;
            }
        }

        // Refresh the buttons to show which one is selected
        if (selectorX == 1 && selectorY == 1)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwprintw(mainWindow[8], 0, 20, "     Choose at random.. Spooky!     ");
                mvwaddch(mainWindow[2], 1, v, randTopicBtn[1][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[3], 1, v, topic1Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, topic2Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, topic3Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[6], 1, v, topic4Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[7], 1, v, topic5Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
            }
        } else if (selectorX == 1 && selectorY == 2)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwprintw(mainWindow[8], 0, 20, "    Select \"Meats and butchers\"?    ");
                mvwaddch(mainWindow[2], 1, v, randTopicBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[3], 1, v, topic1Btn[1][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, topic2Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, topic3Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[6], 1, v, topic4Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[7], 1, v, topic5Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
            }
        } else if (selectorX == 1 && selectorY == 3)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwprintw(mainWindow[8], 0, 20, "     Select \"Cities of Canada\"?     ");
                mvwaddch(mainWindow[2], 1, v, randTopicBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[3], 1, v, topic1Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, topic2Btn[1][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, topic3Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[6], 1, v, topic4Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[7], 1, v, topic5Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
            }
        } else if (selectorX == 2 && selectorY == 1)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwprintw(mainWindow[8], 0, 20, "  Select \"Social Media Platforms\"?  ");
                mvwaddch(mainWindow[2], 1, v, randTopicBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[3], 1, v, topic1Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, topic2Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, topic3Btn[1][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[6], 1, v, topic4Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[7], 1, v, topic5Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
            }
        } else if (selectorX == 2 && selectorY == 2)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwprintw(mainWindow[8], 0, 20, "         Select \"Elements\"?         ");
                mvwaddch(mainWindow[2], 1, v, randTopicBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[3], 1, v, topic1Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, topic2Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, topic3Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[6], 1, v, topic4Btn[1][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[7], 1, v, topic5Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
            }
        } else if (selectorX == 2 && selectorY == 3)
        {
            for (int v = 0; v < 15; v++)
            {
                mvwprintw(mainWindow[8], 0, 20, "       Select  \"Web Browser\"?       ");
                mvwaddch(mainWindow[2], 1, v, randTopicBtn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[3], 1, v, topic1Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[4], 1, v, topic2Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[5], 1, v, topic3Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[6], 1, v, topic4Btn[2][v] | COLOR_PAIR(40) | A_BOLD);
                mvwaddch(mainWindow[7], 1, v, topic5Btn[1][v] | COLOR_PAIR(40) | A_BOLD);
            }
        }
        update_panels();
        doupdate();
    }
}

void StartGameSession(int topic) {
    // Immediately check which topic we are to select
    switch(topic)
    {
        case 0:
        // Random option, in this case randomize the topic
        srand(time(NULL));
        int randomizedTopic = 1 + (rand() % 5); // number can only be between 1-5
        SetTopic(randomizedTopic);
        break;
        case 1:
        // Set the topic to Butchery questions
        SetTopic(1);
        break;
        case 2:
        // Set the topic to Cities of Canada questions
        SetTopic(2);
        break;
        case 3:
        // Set the topic to Social Media Platform questions
        SetTopic(3);
        break;
        case 4:
        // Set the topic to Elements of the earth questions
        SetTopic(4);
        break;
        case 5:
        // Set the topic to Web Browser questions
        SetTopic(5);
        break;
        default:
        // Exit the game if there is an invalid topic
        endwin();
        printf("[main/ERROR]: Invalid topic %d selected", topic);
        exit(-1);
    }
    // Destroy the topic selector's windows
    for (int i = 8; i >= 0; i--)
    {
        del_panel(mainPanel[i]); DestroyWin(mainWindow[i]);
    }

    // Create the session Window
    sessionWindow[0] = CreateNewWinBoxed(30, 80, (maxY / 2) - 15, (maxX - 80) / 2);
    sessionPanel[0] = new_panel(sessionWindow[0]);

    // Flash the screen as we show the topic chosen and start the game
    for (int i = 24; i > 0; i--)
    {
        int d = i;
        if (i == 0) { d = 38; }
        wbkgd(sessionWindow[0], COLOR_PAIR(d));
        update_panels(); doupdate();
    
        // Calculate a smooth flash
        int ms = 50;
        if (i == 0) {ms = 5; }
        msleep(ms);
    }
    wbkgd(sessionWindow[0], COLOR_PAIR(38));
    update_panels(); doupdate();

    // wait and then show a window with the selected topic
    msleep(1000);
    sessionWindow[9] = CreateNewWinBoxed(5, 30, (maxY / 2) - 2, (maxX - 30) / 2);
    sessionPanel[9] = new_panel(sessionWindow[9]);
    mvwprintw(sessionWindow[9], 2, 9, "CHOSEN TOPIC");
    playTackSound();
    update_panels(); doupdate();

    // wait in suspense and then show the selected topic
    msleep(1000);
    switch(topic)
    {
        case 0: mvwprintw(sessionWindow[9], 2, 4, "RANDOM: One of 5 topics!"); break;
        case 1: mvwprintw(sessionWindow[9], 2, 2, "BUTCHERY: meats and animals!"); break;
        case 2: mvwprintw(sessionWindow[9], 2, 7, "CITIES OF CANADA"); break;
        case 3: mvwprintw(sessionWindow[9], 2, 5, "SOCIAL MEDIA PLATFORMS"); break;
        case 4: mvwprintw(sessionWindow[9], 2, 5, "ELEMENTS OF THE EARTH!"); break;
        case 5: mvwprintw(sessionWindow[9], 2, 9, "WEB BROWSERS"); break;
    }
    playTackSound();
    update_panels(); doupdate();

    // Then flash the screen again and start the questions session
    msleep(2000);
    del_panel(sessionPanel[9]); DestroyWin(sessionWindow[9]);
    for (int i = 24; i > 0; i--)
    {
        int d = i;
        if (i == 0) { d = 38; }
        wbkgd(sessionWindow[0], COLOR_PAIR(d));
        update_panels(); doupdate();
    
        // Calculate a smooth flash
        int ms = 50;
        if (i == 0) {ms = 5; }
        msleep(ms);
    }
    wbkgd(sessionWindow[0], COLOR_PAIR(38));

    // Set the score counter
    int sessionScore = 0, currentSessionAnswer;
    // The questions loop begins here
    for (int i = 0; i < 15; i++)
    {
        // Create necessary windows for the question
        sessionWindow[1] = CreateNewWin(7,  72, (maxY / 2) - 14, (maxX - 72) / 2); // title
        sessionWindow[2] = CreateNewWinBoxed(16, 76, (maxY / 2) - 2, (maxX - 76) / 2); // questions container
        sessionWindow[3] = CreateNewWin(2, 72, (maxY / 2) + 1, (maxX - 72) / 2); // question container
        sessionWindow[4] = CreateNewWin(1, 25, (maxY / 2) + 6, (maxX - 50) / 2); // answer (1) container
        sessionWindow[5] = CreateNewWin(1, 25, (maxY / 2) + 10, (maxX - 50) / 2); // answer (1) container
        sessionWindow[6] = CreateNewWin(1, 25, (maxY / 2) + 6, (maxX + 20) / 2); // answer (1) container
        sessionWindow[7] = CreateNewWin(1, 25, (maxY / 2) + 10, (maxX + 20) / 2); // answer (1) container
        sessionWindow[8] = CreateNewWinBoxed(3, 8, (maxY / 2) - 2, (maxX + 60) / 2); // Score counter
        sessionWindow[9] = CreateNewWinBoxed(3, 13, (maxY / 2) - 3, (maxX - 12) / 2); // question num container
        sessionPanel[1] = new_panel(sessionWindow[1]);
        sessionPanel[2] = new_panel(sessionWindow[2]);
        sessionPanel[3] = new_panel(sessionWindow[3]);
        sessionPanel[4] = new_panel(sessionWindow[4]);
        sessionPanel[5] = new_panel(sessionWindow[5]);
        sessionPanel[6] = new_panel(sessionWindow[6]);
        sessionPanel[7] = new_panel(sessionWindow[7]);
        sessionPanel[8] = new_panel(sessionWindow[8]);
        sessionPanel[9] = new_panel(sessionWindow[9]);
        for (int d = 1; d <= 9; d++) { wbkgd(sessionWindow[d], COLOR_PAIR(38)); }

        msleep(10);
        // Set the current question and answer
        char *currentSessionQuestion =   sessionQuestions[i];
        currentSessionAnswer = sessionCorrectAnswer[i];

        // Strings of the title text, ascii art strings
        char titleText_row0[72] = " _____     _       _          ___                    _      _           ";
        char titleText_row1[72] = "|_   _| __(_)_   _(_) __ _   / _ \\__   _____ _ __ __| |_ __(_)_   _____ ";
        char titleText_row2[72] = "  | || '__| \\ \\ / / |/ _` | | | | \\ \\ / / _ \\ '__/ _` | '__| \\ \\ / / _ \\";
        char titleText_row3[72] = "  | || |  | |\\ V /| | (_| | | |_| |\\ V /  __/ | | (_| | |  | |\\ V /  __/";
        char titleText_row4[72] = "  |_||_|  |_| \\_/ |_|\\__,_|  \\___/  \\_/ \\___|_|  \\__,_|_|  |_| \\_/ \\___|";
        char titleText_row6[72] = "             Test your knowledge up to the absolute limits!             ";


        // display title, copied and modified from main menu due to lack of time
        for (int l = 0; l < 72; l++) { mvwaddch(mainWindow[1], 0, l, titleText_row0[l] | A_BOLD | COLOR_PAIR(39) ); }
        for (int l = 0; l < 72; l++) { mvwaddch(mainWindow[1], 1, l, titleText_row1[l] | A_BOLD | COLOR_PAIR(39) ); }
        for (int l = 0; l < 72; l++) { mvwaddch(mainWindow[1], 2, l, titleText_row2[l] | A_BOLD | COLOR_PAIR(39) ); }
        for (int l = 0; l < 72; l++) { mvwaddch(mainWindow[1], 3, l, titleText_row3[l] | A_BOLD | COLOR_PAIR(39) ); }
        for (int l = 0; l < 72; l++) { mvwaddch(mainWindow[1], 4, l, titleText_row4[l] | A_BOLD | COLOR_PAIR(39) ); }
        for (int l = 0; l < 72; l++) { mvwaddch(mainWindow[1], 6, l, titleText_row6[l] | A_BOLD | COLOR_PAIR(39) ); }
        // Show the question number, show score
        mvwprintw(sessionWindow[9], 1, 1, "QUESTION %d", i+1);
        mvwprintw(sessionWindow[8], 1, 2, "%d/15", sessionScore);
        playTackSound(); update_panels(); doupdate();
        msleep(50);

        // Show the question in the question container 
        
        // Allocate space for the extracted question
        char* wrappedSessionQuestion = (char*)malloc(101);
        if (wrappedSessionQuestion) {
            // copy the specified string and then place it in the const char* for use with wraptxtw()
            strncpy(wrappedSessionQuestion, currentSessionQuestion, 100);
            wrappedSessionQuestion[100] = '\0';
            const char* displayedSessionQuestion = wrappedSessionQuestion;

            // display wrapped question text
            wraptxtw(sessionWindow[3], displayedSessionQuestion, 72);

            // Free allocated memory
            free(wrappedSessionQuestion);

        } else {
            endwin();
            printf("[main/ERROR]: Memory allocation failure.\n");
            exit(-1);
        }

        // Show all possible answers
        for (int u = 0; u < 4;  u++) { mvwprintw(sessionWindow[u+4], 0, 0, "(%d) ", u+1); }
        for (int v = 0; v < 25; v++) { mvwaddch(sessionWindow[4], 0, 4 + v, sessionQuestions[i][v+100]); }
        for (int v = 0; v < 25; v++) { mvwaddch(sessionWindow[5], 0, 4 + v, sessionQuestions[i][v+125]); }
        for (int v = 0; v < 25; v++) { mvwaddch(sessionWindow[6], 0, 4 + v, sessionQuestions[i][v+150]); }
        for (int v = 0; v < 25; v++) { mvwaddch(sessionWindow[7], 0, 4 + v, sessionQuestions[i][v+175]); }

        update_panels(); doupdate();

        // The menu keybinds and logic for responsive UI
        int isInputBlocked, ch, selector = 1;
        isInputBlocked = IsInputBlocked();
        int loopCheck = 0;
        do 
        {
        
            msleep(25);

            isInputBlocked = IsInputBlocked();
            if (isInputBlocked == 0)
            {
                mvprintw(maxY-1, 0, "[main/DEBUG]: lastkeypress: %u  \n", ch);
                switch (ch) {
                case '1':
                case '2':
                case '3':
                case '4':
                sessionAnswers[i] = ch;
                mvprintw(10, 0, "sessionAnswers = %d, ch = %d", sessionAnswers[i], ch);
                loopCheck = 1;
                break;
                case KEY_F(1):
                    endwin();
                    exit(0);
                
                default:
                    break;
                }
            }
        } while((ch = getch()) != 49 && ch != 50 && ch != 51 && ch != 52);

        for (int l = 9; l > 0; l--) { del_panel(sessionPanel[l]); DestroyWin(sessionWindow[l]); }
        mvprintw(2, 1, "DEBUG: exited getch loop");
        msleep(1000);
        sessionWindow[1] = CreateNewWinBoxed(5, 30, (maxY / 2) - 2, (maxX - 30) / 2);
        sessionPanel[1] = new_panel(sessionWindow[1]);
        if (sessionCorrectAnswer[i] == sessionAnswers[i])
        {
            mvprintw(1, 1, "DEBUG: correct answer");
            refresh();
            mvwprintw(sessionWindow[1], 2, 11, "CORRECT!");
            playCorrectSound();
            update_panels(); doupdate();
            sessionScore++;
            getch();
        } else if (sessionAnswers[i] != currentSessionAnswer)
        {
            mvprintw(0, 0, "DEBUG: incorrect answer, sessionCorrectAnswer[i] = %d", sessionCorrectAnswer[i]);
            refresh();
            getch();
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

// Print text wrapped cleanly
void wraptxtw(WINDOW* win, const char* input, int maxWidth) {
    char* copy = strdup(input); // Create a copy to avoid modifying the original
    char* word = strtok(copy, " ");
    char line[200] = ""; // Initialize an empty line buffer

    while (word != NULL) {
        if (strlen(line) + strlen(word) + 1 <= maxWidth) {
            // Word fits within the line length limit
            strcat(line, word);
            strcat(line, " ");
        } else {
            // Start a new line
            mvwprintw(win, 0, 1, "%s", line); // Print the line in the specified window
            strcpy(line, word);
            strcat(line, " ");
        }
        word = strtok(NULL, " ");
    }

    // Print the last line
    mvwprintw(win, 1, 1, "%s", line);

    free(copy); // Clean up
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

