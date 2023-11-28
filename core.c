// Core functionality of the game, such as the questions and answers
// @license MIT
// @author Lexi Charron



// When the topic is chosen, the questions, user answers and correct answer are written to these
char sessionQuestions[][201] = { { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" } };
int sessionAnswers[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int sessionCorrectAnswer[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


// FORMAT for topicQuestions[][200]
// -> [0]   to [99] : Question string
// -> [100] to [124]: Answer 1 string
// -> [125] to [149]: Answer 2 string
// -> [150] to [174]: Answer 3 string
// -> [175] to [199]: answer 4 string
// ->          [200]: Answer character, translated into correct keypress

// Butchery questions
char butcherQuestions[][201] =
{
    { "Which of the following boneless steaks can be found on a T-Bone?                                    Strip steak              Ribeye steak             Round steak              Sirloin steak            1" },
    { "Which of the following is the most tender steak of them all?                                        Ribsteak                 Tenderloin steak         Minute steak             T-Bone steak             2" },
    { "Which animal's meat is more prone to foodborne illnesses if not cooked correctly?                   Horse meat               Cow meat                 Chicken meat             Pork meat                " },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" }
};


// Cities of Canada questions
char citiesOfCanadaQuestions[][201] =
{
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" }
};



// Social Media Platforms questions
char socialMediaPlatformQuestions[][201] =
{
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" }
};



// Elements of the earth questions
char elementQuestions[][201] =
{
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" },
    { "" }
};




// Web Browsers questions
char webBrowserQuestions[15][201] =
{
    { "What was Mozilla Firefox's initial release name?                                                    Firefox                  Netscape                 Phoenix                  Lynx                     3" }, // 51
    { "Which of the following is a command-line Web Browser?                                               Internet Explorer        Lynx                     Camino                   Chromium                 2" }, // 50
    { "What is the market share of Chrome worldwide in 2023?                                               20%                      63%                      91%                      49%                      2" }, // 50
    { "In 2023, which of these Web browsers use the Gecko browser engine?                                  Chrome                   Edge                     Opera                    Firefox                  4" }, // 52
    { "Which chromium-based browser is known for having an AI assistant integrated within it?              Brave                    Opera GX                 Edge                     Vivaldi                  3" }, // 51
    { "Which of the following takes advantage of the onion network, commonly known as the dark web?        Tor Browser              Torch                    Yandex Browser           Chrome                   1" }, // 49
    { "Which of the following is commonly marketed as a 'browser for gamers'?                              LibreWolf                Samsung Internet         Opera GX                 Vivaldi                  3" }, // 51
    { "Which browser is Tor Browser based off of?                                                          Firefox                  Internet Explorer        Chromium                 Netscape                 1" }, // 49
    { "In 1995, which browser was most popular worldwide?                                                  Chrome                   Opera                    Internet Explorer        Netscape                 4" }, // 52
    { "Which browser can be found on Apple devices by default?                                             Internet Explorer        Safari                   Camino                   Firefox                  2" }, // 50
    { "Which browser has the unique feature of having multiple layout engines?                             Lunascape                Netsurf                  Safari                   SeaMonkey                1" }, // 49
    { "Which of the following is NOT based on the Chromium Web Browser?                                    Opera                    Safari                   Kiwi Browser             Torch                    2" }, // 50
    { "Which of the following is an open source Web Browser?                                               Chrome                   Opera                    Lynx                     UC Browser               3" }, // 51
    { "Which of the following Web Browsers extends Security and Privacy and is based on Firefox?           UC Browser               Brave                    LibreWolf                Opera GX                 3" }, // 51
    { "When was the Chromium Web Browser initially released?                                               September 2008           December 1996            September 2013           January 2001             1" }  // 49
};


/*
// A function to swap two strings
void Swap(char (*array)[200], int i, int j) {
    mvprintw(12, 0, "swapping.. %d %d", i, j); refresh();
    char temp[15][200];
    strcpy(temp, array[i]);
    strcpy(array[i], array[j]);
    strcpy(array[j], temp);
}*/

void SwapChar(char (*array)[201], int i, int j) {
    int k = 0;
    while (array[i][k] != '\0' && array[j][k] != '\0') {
        char temp = array[i][k];
        array[i][k] = array[j][k];
        array[j][k] = temp;
        k++;
    }
}



// A function to shuffle a two-dimensional array and another array in the same way
void Shuffle(char (*array1)[201], int rows) {
    srand(time(0));

    for (int i = rows - 1; i > 0; i--) {
        int j = rand() % (i + 1);


        int k = 0;
        while (array1[i][k] != '\0' && array1[j][k] != '\0') {
        char temp = array1[i][k];
        array1[i][k] = array1[j][k];
        array1[j][k] = temp;
        k++;
        }

        //SwapChar(array1, i, j);
        //SwapInt(array2, i, j);
    }
}

void CopyArrayChar(char (*source)[201], char (*destination)[201], int rows) {
    for (int i = 0; i < rows; i++) {
        strcpy(destination[i], source[i]);
    }
}





// Set the topic of the session trivia questions and answers
void SetTopic(int topic) {
    refresh();
    // Use one of the topic arrays to calculate rows and cols used by the shuffle function
    // Due to the nature of the way we have the topic questions set, we use the following as our rows & cols calculator
    int rows = sizeof(webBrowserQuestions) / sizeof(webBrowserQuestions[0]);
    // Then we send off the chosen topic to the session arrays
    switch(topic)
    {
        case 1:
        CopyArrayChar(butcherQuestions, sessionQuestions, rows);
        break;
        case 2:
        CopyArrayChar(citiesOfCanadaQuestions, sessionQuestions, rows);
        break;
        case 3:
        CopyArrayChar(socialMediaPlatformQuestions, sessionQuestions, rows);
        break;
        case 4:
        CopyArrayChar(elementQuestions, sessionQuestions, rows);
        break;
        case 5:
        CopyArrayChar(webBrowserQuestions, sessionQuestions, rows);
        
        break;
    }

    // Then send it off to the shuffle function
    Shuffle(sessionQuestions, rows);
}