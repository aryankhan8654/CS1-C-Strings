#include <stdio.h>
#include <math.h>
#include <string.h>

#include "gameFunctions.h"

void initializeBlankString(int size, char *s)
{

  for (int i = 0; i < size; i++)
  {

    s[i] = '_';
  }
}

void printWithSpaces(char *s)
{

  int size = (strlen(s) + (strlen(s) - 1)) + 1;

  char new_str[size];

  new_str[size - 1] = '\0';

  for (int i = 0; i < (size - 1); i++)
  {

    if (i % 2 != 0)
    {

      new_str[i] = ' ';
    }

    else
    {

      new_str[i] = *s;
      s++;
    }
  }

  printf("%s", new_str);
}

int revealGuessedLetter(const char *str_1, char *str_2, char ch)
{

  int count = 0;

  while (*str_1 != '\0')
  {

    if (*str_1 == ch)
    {

      *str_2 = ch;
      count++;
    }

    str_1++;
    str_2++;
  }

  if (count == 0)
  {

    return 0;
  }

  return 1;
}

int checkGuess(char *str_1, char *str_2)
{

  int check = strcmp(str_1, str_2);

  if (check == 0)
  {

    return 1;
  }

  return 0;
}

void startGame(char word[25])
{
  int won = 0;              // Flag to see if the user has won yet
  int numBadGuesses = 0;    // Counter to end the game on a lose condition
  int possibleBadGuesses;   // Total number of bad guesses allowed
  int charRevealed;         // Flag to see if the user guessed a good letter
  char guess;               // The user's guess
  char revealedLetters[25]; // What the user has revealed so far

  // Initializes the guessing array to all underscores
  initializeBlankString(strlen(word), revealedLetters);
  clearScreen();

  // Gets the total number of chances
  printf(
      "Please enter the total number of incorrect guesses you would like to be "
      "able to make: ");
  scanf("%d", &possibleBadGuesses);
  printWithSpaces(revealedLetters);

  // Runs the game loop until the number of tries are exhausted or the word is
  // found
  while (numBadGuesses <= possibleBadGuesses && !won)
  {
    printf("Enter a letter to guess: ");
    scanf(" %c", &guess);

    // Updates the revealed letters and checks to see if the user won
    charRevealed = revealGuessedLetter(word, revealedLetters, guess);
    won = checkGuess(word, revealedLetters);

    // Increments bad guesses if the last guess was a miss
    if (!charRevealed)
    {
      numBadGuesses++;
    }

    // Outputs game information to the user
    drawHorse(numBadGuesses, possibleBadGuesses);
    printWithSpaces(revealedLetters);
  }

  if (won)
    printf("Congratulations!  You correctly guessed the word %s\n", word);
  else
    printf("You've run out of guesses.  The correct word was %s\n", word);
}

// Draws part of the horse pending on how many guesses have been made so far
// Horse grabbed from: https://www.asciiart.eu/animals/horses
// And no, I don't know why there's an entire site dedicated to virtualhorses =/
void drawHorse(int guessedSoFar, int allowedGuesses)
{
  // The horse!  Duh!
  char *horsey[29] = {"   Y8baadP\"\"\"\"\"\"\"\"Yba,_",
                      "aaadP\"'             `\"\"Yb,",
                      "`Y8(                    `\"Yb,",
                      "  `Y,                      `Yba,",
                      "    Y,  (O)                   `Yba,",
                      "    `Y,                          \"\"Yba,________,,aaddddbbbaa,,____,aa,_",
                      "     `Y,       ,aa                   `\"\"\"\"\"\"\"\"\"\"''          ``\"\"\"\"''  \"Y,",
                      "       Y,      d'8                                                \"Ya   `Y,",
                      "       `b      8 8                                                  `Y,   Y,",
                      "        Ya o  ,8 8                                                    b   `b",
                      "         Yb,_,dP 8                                                    Y    8",
                      "          `\"\"\"\"  Y                                                    8    8",
                      "                 I,                                                   8    8",
                      "                 `b                                                   P    [",
                      "                  `b                                                 d'    [",
                      "                   d                                                ,P     [",
                      "                 ,d'    ,PY,         ,P\"YaaaaaaP\"Ybaaa,,_           d'     [",
                      "                d\"    ,P\"  Y,        d'           8'  `\"\"db,       d'      8",
                      "               d'   ,P\"    `Y,       8            I,     d'\"b,     8a      P",
                      "              d(    (       `Y,      P            `b    ,P  `Y,    8`Ya___d'",
                      "              \"Y,   \"b,      `Y,    ,I             8    d'   `8    8  `\"\"\"'",
                      "                \"Y,   \"b,  __ `8,   d'            ,8   ,P     8    8",
                      "                  \"Y,   \"bd88b `b   8             I'   d'     Y,   8",
                      "                    \"Y,    888b 8   8             8   ,P      `b   8",
                      "                      \"Ya,,d888b8   P            d'  ,P'       8   Y,",
                      "                         `\"\"\"\",d\"  ,I        ,adPb__aP'        Y   `b",
                      "                           ,a8P,__aP'       d888888P'         ,d    8",
                      "                          d8888888'         88888888       ,d888bbaaP",
                      "                          88888888                         88888888'"};

  clearScreen();

  // Determines how much of the horse to print and prints it
  double ratio = (double)guessedSoFar / (double)allowedGuesses;
  int linesToDraw = floor(ratio * 28);
  linesToDraw = linesToDraw <= 29 ? linesToDraw : 29;

  int i;
  for (i = 29 - linesToDraw; i < 29; i++)
  {
    printf("%s\n", horsey[i]);
  }
}

void clearScreen()
{
  // Some UNIX hackary to clear the terminal.  Makes this not portable to some
  // systems,
  // but should work fine on CSE
  printf("\033[2J");
  printf("\033[0;0f");
  printf("\n"); // print a new line for the sake of those on different systems
}