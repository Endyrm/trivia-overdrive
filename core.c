// Core functionality of the game, such as the questions and answers
// @license MIT
// @author Lexi Charron

// declare the required variables for question, answer and score tracking
int score = 0;

// When the topic is chosen, the questions, possible answers and correct answer are written to these
char sessionQuestions[][200];
char sessionAnswers[][200];
char sessionCorrectAnswer[][200];


// FORMAT for topicQuestions[][200]
// -> [0]   to [99] : Question string
// -> [100] to [124]: Answer 1 string
// -> [125] to [149]: Answer 2 string
// -> [150] to [174]: Answer 3 string
// -> [175] to [199]: answer 4 string

// Butchery questions
char butcherQuestions[][200] =
{
    { "Which of the following boneless steaks can be found on a T-Bone?                                    Strip steak              Ribeye steak             Round steak              Sirloin steak            " },
    { "Which of the following is the most tender steak of them all?                                        Ribsteak                 Tenderloin steak         Minute steak             T-Bone steak             " },
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

char butcherAnswers[][200] =
{
    { "1" },
    { "2" },
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


// Cities of Canada questions
char citiesOfCanadaQuestions[][200] =
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

char citiesOfCanadaAnswers[][200] =
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
char socialMediaPlatformQuestions[][200] =
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

char socialMediaPlatformAnswers[][200] =
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
char elementQuestions[][200] =
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

char elementAnswers[][200] =
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
char webBrowserQuestions[][200] =
{
    { "What was Mozilla Firefox's initial release name?                                                    Firefox                  Netscape                 Phoenix                  Lynx                     " },
    { "Which of the following is a command-line Web Browser?                                               Internet Explorer        Lynx                     Camino                   Chromium                 " },
    { "What is the market share of Chrome worldwide?                                                       20%%                      63%%                      91%%                      49%%                      " },
    { "In 2023, which of these Web browsers use the Gecko browser engine?                                  Chrome                   Edge                     Opera                    Firefox                  " },
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

char webBrowserAnswers[][200] =
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



// A function to swap two strings
void Swap(char (*array)[200], int i, int j) {
    char temp[200];
    strcpy(temp, array[i]);
    strcpy(array[i], array[j]);
    strcpy(array[j], temp);
}

// A function to shuffle a two-dimensional array and another array in the same way
void Shuffle(char (*array1)[200], char (*array2)[200], int rows, int cols) {
    // Initialize the random number generator
    srand(time(NULL));

    // Loop through the array from the last element to the second element
    for (int i = rows * cols - 1; i > 0; i--) {
        // Pick a random element from the remaining part of the array
        int j = rand() % (i + 1);

        // Swap the current element with the random element in both arrays
        Swap(array1, i, j);
        Swap(array2, i, j);
      }
}

// A function to print a two-dimensional array of strings
void print_array(char (*array)[200], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    printf("%s\n", array[i]);
  }
}