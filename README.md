# Trivia Overdrive
Trivia Overdrive is a fun and simple terminal-based trivia game intended for my final project of the Microprocessors I course. It also utilizes ncurses for UI, as an extra fun attempt at UI/UX eye-candy and a personal challenge for bettering my skills. Due to some weird issues with attempting to include the PDcurses libraries on our Windows 11 lab computers, I opted to write this on Linux and potentially set up a github workflow to build the application automatically and perhaps have it compile a Windows-compatible version.

## TODO:
The following are my goals with this project, as for what I can achieve by the submission date or beyond.
- [ ] Write the core functionality: the main functions that allow me to track scores, hold the questions, etc.
- [ ] Write the curses UI: the primary UI of the project
- [ ] Automatically port to Windows: As explained above, we were technically required to build these applications on Windows to streamline the grading process, however it has evidently not been super possible to do. This is likely to be a github workflow.


## The key requirements of the project
The project was subjected to several requirements as to allow for streamlined grading guidelines by the professor. Such requirements were (but not limited to):
* Utilizing arrays for storing the questions;
* Randomizing the array index to present a different question each time;
* Ensuring that input types align with the specifications (strings, integers, etc);
* Implementing sound effects using WAV files for various stages (game start, right/wrong answers, score display, ambient music, etc);
* Offering an option to quit the game or continue for more questions during gameplay;
* Implementing a score counter to track progress

## The point of this project being open-source
I'm a huge proponent of free and open source software, regardless of how bad or stellar the quality of my work is. I know that my work may help someone with a similar idea or is just generally trying to learn C on their own, which is why I decided to license it under the MIT license. I would suggest as courtesy to also have your derivative projects be open source, but since I understand that some projects may not be allowed that luxury, you have that freedom as a result of the chosen license.

The following is a copy of the license, which can also be found under the LICENSE file:



**Copyright (c) 2023 Lexi Charron**

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
