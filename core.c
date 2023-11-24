// Core functionality of the game, such as the questions and answers
// @license MIT
// @author Lexi Charron

// declare the required variables for question, answer and score tracking
int score = 0;

// When the topic is chosen, the questions, possible answers and correct answer are written to these
char chosenQuestions[][200];
char chosenAnswers[][200];
char chosenCorrectAnswer[][200];


// Topics must be 10-15 questions each
char butcherQuestions[][200] =
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
}
char butcherAnswers[][200] =
{
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" },
    { "", "", "", "" }
}

char butcherCorrectAnswer[][200] =
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
}

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
    swap(array1, i, j);
    swap(array2, i, j);
  }
}

// A function to print a two-dimensional array of strings
void print_array(char (*array)[200], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    printf("%s\n", array[i]);
  }
}