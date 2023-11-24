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
void ForkAndDetatch(char *fileName);

// Function Macro prototypes
void playThudSound();       // Used in intro sequence
void playRevealSound();     // Used for the intro sound that reveals the main menu

void PlayAudio(char *fileName)
{
    // Create a command string with the fileName
    char command[256];
    sprintf(command, "vlc --quiet --intf dummy --play-and-exit %s &> /dev/null", fileName);

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


// these are placeholders for now
void playThudSound() {
    ForkAndDetach("./audio/thud.wav");
}

void playRevealSound() {
    ForkAndDetach("./audio/reveal.wav");
}


