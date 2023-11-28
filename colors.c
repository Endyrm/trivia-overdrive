// Set all color pairs to avoid issues, serves as documentation for all colors used in the program.
// @license MIT
// @author Lexi Charron

#include <ncurses.h>

void DefineColorPairs();

void DefineColorPairs() {
    // Note to everyone wanting to do things in their own way: \
       PLEASE just use https://www.ditig.com/256-colors-cheat-sheet \
       I swear, you will save so much time that I wasted wondering \
       why my custom colors just DIDN'T WORK. I felt so stupid when \
       I found out it was all based off of this and not actual 24-bit \
       color definitions. But anyway, enjoy this life lesson learnt \
       the hard way.

    // monochrome color pairs (note that 231 is WHITE and 0 is BLACK)
    init_pair(0, 231, 232);  // hsl(0,0%,3%)
    init_pair(1, 231, 233);  // hsl(0,0%,7%)
    init_pair(2, 231, 234);  // hsl(0,0%,10%)
    init_pair(3, 231, 235);
    init_pair(4, 231, 236);
    init_pair(5, 231, 237);
    init_pair(6, 231, 238);
    init_pair(7, 231, 239);
    init_pair(8, 231, 240);
    init_pair(9, 231, 241);
    init_pair(10, 231, 242);
    init_pair(11, 231, 243);
    init_pair(12, 232, 244);
    init_pair(13, 232, 245);
    init_pair(14, 232, 246);
    init_pair(15, 232, 247);
    init_pair(16, 232, 248);
    init_pair(17, 232, 249);
    init_pair(18, 232, 250);
    init_pair(19, 232, 251);
    init_pair(20, 232, 252);
    init_pair(21, 232, 253);
    init_pair(22, 232, 254);
    init_pair(23, 232, 255);
    init_pair(24, 232, 231);

    // for monochrome text fade
    init_pair(25, 231, 244);
    init_pair(26, 231, 245);
    init_pair(27, 231, 246);
    init_pair(28, 231, 247);
    init_pair(29, 231, 248);
    init_pair(30, 231, 249);
    init_pair(31, 231, 250);
    init_pair(32, 231, 251);
    init_pair(33, 231, 252);
    init_pair(34, 231, 253);
    init_pair(35, 231, 254);
    init_pair(36, 231, 255);
    init_pair(37, 231, 231);

    // workaround for a weird color profile issue
    init_pair(38, 231, 232);

    // color text
    init_pair(39, 141, 232); // MediumPurple1 on hsl(0,0%,3%)
    init_pair(40, 141, 189); // MediumPurple1 on LightSteelBlue1
    init_pair(41, 244, 232); // hsl(0,0%,50%) on hsl(0,0%,3%)

}