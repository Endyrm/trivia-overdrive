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
    { "Which animal's meat is more prone to foodborne illnesses if not cooked correctly?                   Horse meat               Cow meat                 Chicken meat             Pork meat                3" },
    { "Which of the following roasts is especially recommended for a slow cooker?                          Loin roast               Plate roast              Tenderloin roast         Strip loin               2" },
    { "Which of the following chicken parts especially popular as a Superbowl meal tradition?              Chicken breasts          Chicken thighs           Chicken liver            Chicken wings            4" },
    { "Which of the following is the common name for Pork Loin steak?                                      Pork wings               Pork slabs               Pork chops               Pork blades              3" },
    { "How does grinding down meat affect its longevity before spoiling?                                   It makes it last longer  It doesn't do anything   It makes it last forever It ruins its longevity   4" },
    { "Which of the following are NOT common uses for ground meat?                                         Spaghetti sauce          Burger patties           Shepherd's pie           Meatloaf Sundae          4" },
    { "Which of the following steaks is praised for general tenderness and is recommended on the grill?    Sirloin steak            Ribsteak                 Round steak              French steak             2" },
    { "Which of the following boneless steaks can be found on a Ribsteak?                                  Ribeye steak             Tenderloin steak         Strip steak              French steak             1" },
    { "Which of the following pork parts is located in the leg?                                            Pork loin                Pork shanks              Pork tenderloin          Pork rib roast           2" },
    { "Which of the following chicken parts are used to make chicken fingers?                              Chicken breasts          Chicken tenderloin       Chicken thigh            Chicken leg              2" },
    { "Which of the following parts of a cow is where the brisket is located?                              In front of front shanks Beside the ribs          Above the round          Beside the rump          1" },
    { "Where is the T-Bone steak located in a cow?                                                         Short loin               Rib                      Brisket                  Chuck                    1" },
    { "Where is the Short loin located in a cow?                                                           Beside the round         Behind the ribs          Beside the shanks        Above the brisket        2" }
};


// Cities of Canada questions
char citiesOfCanadaQuestions[][201] =
{
    { "Which Canadian town has (currently) the most expensive bank-owned property in Canada?               Toronto                  Temiskaming Shores       Vancouver                North Bay                2" },
    { "Which is the largest city in Canada by population?                                                  Montreal                 Vancouver                Toronto                  Quebec City              3" },
    { "Which is the largest city of the province of Quebec by population?                                  Gatineau                 Montreal                 Quebec City              Saguenay                 2" },
    { "Which is the largest city of the province of Ontario by population?                                 Sudbury                  Ottawa                   Kingston                 Toronto                  4" },
    { "Which is the largest city of the province of Alberta by population?                                 Calgary                  Edmonton                 Red Deer                 Lethbridge               1" },
    { "Which is the largest city of the province of Nova Scotia by population?                             Halifax                  Dartmouth                Sydney                   Truro                    1" },
    { "Which is the largest city of the province of British Columbia by population?                        Victoria                 Kelowna                  Vancouver                Surrey                   3" },
    { "Which is the largest city of the province of Saskatchewan by population?                            Regina                   Saskatoon                Prince Albert            Moose Jaw                2" },
    { "Which is the largest city of the province of Manitoba by population?                                Brandon                  Winnipeg                 Thompson                 Portage la Prairie       2" },
    { "Which is the largest city of the province of Newfoundland and Labrador by population?               St. John's               Corner Brook             Mount Pearl              Labrador City            1" },
    { "Which city is the capital of Canada?                                                                Toronto                  Ottawa                   Montreal                 Vancouver                2" },
    { "Which city is the largest by area in Canada?                                                        Toronto                  Quebec City              Calgary                  Vancouver                3" },
    { "Which city is directly North of Ottawa?                                                             Gatineau                 Montreal                 North Bay                Thurso                   1" },
    { "Which city is known as \"one of Canada's greatest outdoor cities\"?                                   Thunder Bay              Thurso                   Petawawa                 Mattawa                  1" },
    { "Which of the following towns comprises the largest-by-population town in Temiskaming Shores city?   Haileybury               Mattawa                  Cobalt                   New Liskeard             4" }
};



// Social Media Platforms questions
char socialMediaPlatformQuestions[][201] =
{
    { "Which social media platform is used for video sharing?                                              Instagram                Twitter/X                Facebook                 Youtube                  4" },
    { "Which of the following platforms is currently owned by Elon Musk?                                   Youtube                  Twitter/X                Tumblr                   Facebook                 2" },
    { "What best describes Twitter/X as a platform?                                                        Microblogging app        Video sharing app        Crowdfunding app         Livestreaming app        1" },
    { "Which platform makes video, voice and text chat easy AND historically was marketed for gamers?      Skype                    Teamspeak                IRC                      Discord                  4" },
    { "Which platform allows you to create and share professional profiles, resumes and connections?       LinkedIn                 Google Meet              Skype                    Reddit                   1" },
    { "Which social media platform is regarded as an app for the older generation?                         Twitter/X                Youtube                  Instagram                Facebook                 4" },
    { "Which social media platform makes livestreaming trivial for most gamers?                            Youtube                  Kick                     Vimeo                    Twitch                   4" },
    { "Which social media app allows you to share messages and media fully encrypted?                      Signal                   Discord                  Zoom                     Messenger                1" },
    { "What was TikTok's original name before it was renamed?                                              TikTok Clock             Musical.ly               Reels                    Tumblr                   2" },
    { "Which social media platform dominated the internet as a short video sharing haven?                  Youtube                  Instagram                TikTok                   Twitter/X                3" },
    { "Why did Elon Musk rename Twitter to X?                                                              He likes X as a name     He was forced to         It's a strategic choice  Twitter sucks as a name  1" },
    { "Which platform owns Instagram?                                                                      Yahoo                    Alphabet/Google          Meta                     Spotify                  3" },
    { "What is Youtube and Google's parent company?                                                        Alphabet                 None                     Microsoft                Samsung                  1" },
    { "Which major social media company owns the Outlook email service?                                    None                     Yahoo                    Alphabet                 Microsoft                4" },
    { "Which major social media company owns the ProtonMail email service?                                 Yahoo                    None                     Microsoft                Alphabet                 2" }
};



// Elements of the earth questions
char elementQuestions[15][201] =
{
    { "What is the name of the element with the symbol H?                                                  Helium                   Hydrogen                 Hafnium                  Hassium                  2" },
    { "What is the name of the element with the symbol O?                                                  Osmium                   Oganesson                Oxygen                   Oxygenium                3" },
    { "What is the name of the element with the symbol C?                                                  Carbon                   Calcium                  Cobalt                   Cerium                   1" },
    { "What is the name of the element with the symbol N?                                                  Neon                     Nitrogen                 Niobiom                  Nobelium                 2" },
    { "What is the name of the element with the symbol F?                                                  Francium                 Fermium                  Flerovium                Fluorine                 4" },
    { "What is the name of the element with the symbol He?                                                 Hydrogen                 Hafnium                  Helium                   Hassium                  3" },
    { "What is the name of the element with the symbol Li?                                                 Lithium                  Livermorium              Lutetium                 Lanthanum                1" },
    { "What is the name of the element with the symbol Be?                                                 Boron                    Beryllium                Bohrium                  Berkelium                2" },
    { "What is the name of the element with the symbol B?                                                  Boron                    Beryllium                Berkelium                Bohrium                  1" },
    { "What is the name of the element with the symbol Ne?                                                 Nitrogen                 Niobium                  Neon                     Nobelium                 3" },
    { "What is the name of the element with the symbol Na?                                                 Neon                     Nihonium                 Neptunium                Sodium                   4" },
    { "What is the name of the element with the symbol Mg?                                                 Manganese                Magnesium                Meitnerium               Molybdenum               2" },
    { "What is the name of the element with the symbol Al?                                                 Americium                Astatine                 Aluminium                Argon                    3" },
    { "What is the name of the element with the symbol Si?                                                 Silver                   Silicon                  Scandium                 Selenium                 2" },
    { "What is the name of the element with the symbol Og                                                  Oganesson                Oxygen                   Osmium                   Oxygenium                1" }
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


// Shuffle an array with an unbiased sorting method
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
    }
}

void CopyArray(char (*source)[201], char (*destination)[201], int rows) {
    for (int i = 0; i < rows; i++) {
        strcpy(destination[i], source[i]);
    }
}





// Set the topic of the session trivia questions and answers based on the selected topic
void SetTopic(int topic) {
    refresh();
    // Use one of the topic arrays to calculate rows and cols used by the shuffle function
    // Due to the nature of the way we have the topic questions set, we use the following as our rows & cols calculator
    int rows = sizeof(webBrowserQuestions) / sizeof(webBrowserQuestions[0]);
    // Then we send off the chosen topic to the session arrays
    switch(topic)
    {
        case 1:
        CopyArray(butcherQuestions, sessionQuestions, rows);
        break;
        case 2:
        CopyArray(citiesOfCanadaQuestions, sessionQuestions, rows);
        break;
        case 3:
        CopyArray(socialMediaPlatformQuestions, sessionQuestions, rows);
        break;
        case 4:
        CopyArray(elementQuestions, sessionQuestions, rows);
        break;
        case 5:
        CopyArray(webBrowserQuestions, sessionQuestions, rows);
        
        break;
    }

    // Then send it off to the shuffle function
    Shuffle(sessionQuestions, rows);
}