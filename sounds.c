// Sound utilities to initialize a child process and play the sounds through vlc lol
// @license MIT
// @author Lexi Charron


/*
    Alright, I have to explain something. Because of the fact that this program is built for linux,
    it has no access to Win32 API's such as PlaySound(). I had a lot of head scratching to do and
    I settled on using a library of my system which doubles as a commonly used video player app.

    Yes, I create a child process with ForkAndDetatch() every time the sound functions are called.
    Yes, ForkAndDetatch() does call PlayAudio(), and the reason for this complicated confusion is
    due to the fact that I absolutely needed sound to run asynchronously to avoid unnecessary delay
    with the animations this game runs via ncurses :)

    Enjoy the chaos!
*/

// Function prototypes
void PlayAudio(char *fileName);
void ForkAndDetach(char *fileName);

// Function Macro prototypes
void playThudSound();
void playRevealSound();     
void playPromptSound();
void playNavSound();
void playEnterSound();
void playTackSound();


void PlayAudio(char *fileName)
{
    // Create a command string with the fileName
    char command[256];
    sprintf(command, "vlc --quiet --intf dummy --gain=0.25 --play-and-exit %s &> /dev/null", fileName);
    
    // Play the audio via command execution
    system(command);
}


void ForkAndDetach(char *fileName)
{
    // Fork a child process
    pid_t pid = fork();

    // Check if the fork was successful
    if (pid < 0)
    {
        // Fork failed, print an error message and return
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        // Child process, detach from the parent process
        setsid();

        // Call the PlayAudio function to play the audio
        PlayAudio(fileName);

        // Exit the child process
        exit(0);
    }
    else
    {
        // Parent process, do nothing
        return;
    }
}


// The following are all macros for ForkAndDetatch(),
// it simplifies stuff by letting me config them directly here
// and calling them wherever I want in code.

// More information is found on each audio file in audio/README.md

void playThudSound() {
    ForkAndDetach("./audio/thud.wav");
}

void playRevealSound() {
    ForkAndDetach("./audio/reveal.wav");
}

void playPromptSound() {
    ForkAndDetach("./audio/prompt.wav");
}

void playNavSound() {
    ForkAndDetach("./audio/nav.wav");
}

void playEnterSound() {
    ForkAndDetach("./audio/enter.wav");
}

void playTackSound() {
    ForkAndDetach("./audio/tack.wav");
}

void playCorrectSound() {
    ForkAndDetach("./audio/correct.wav");
}

void playIncorrectSound() {
    ForkAndDetach("./audio/incorrect.wav");
}

void playGameWin1Sound() {
    ForkAndDetach("./audio/gameWin1.wav");
}

void playGameWin2Sound() {
    ForkAndDetach("./audio/gameWin2.wav");
}

void playGameLossSound() {
    ForkAndDetach("./audio/gameLoss.wav"); msleep(500);
    ForkAndDetach("./audio/gameLoss.wav"); msleep(500);
    ForkAndDetach("./audio/gameLoss.wav"); msleep(500);
    ForkAndDetach("./audio/gameLoss.wav"); msleep(500);
    ForkAndDetach("./audio/gameLoss.wav");
    
}

void playMenuTune() {
    ForkAndDetach("./audio/menuTune.wav");
}
