#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define NUM_CHARS 3864794

int checkLetter(char letter, char *word, char *printedWord);
void printLine(char *word);
void printHangman(int numberLimbs);
void trim(char *word);

void trim(char *word)
{
  int i = strlen(word);
  while (i >= 0 && isalpha(word[i]) == 0)
  {
    word[i] = '\0';
    i--;
  }
}
void printLine(char *word)
{
  int i;
  for (i = 0; word[i] != '\0'; i++)
  {
    printf("%c ", word[i]);
  }
  printf("\n");
}

void printHangman(int numberLimbs)
{
  /*
  The hanged man looks like this 
  First the head is added, then the neck, then the arms, then the 
  torso, then the legs
  ______
  |    |
  |    O
  |   _|_
  |  / | \
  |   _|_
  |  /   \
  |

  */
  if (numberLimbs == 0)
  {
    return;
  }
  else
  {
    printf("\n______\n|    |\n");
    printf("|    ");

    if (numberLimbs > 0)
    {
      printf("O");
    }

    printf("\n|   ");

    if (numberLimbs > 1)
    {
      printf("_|_");
    }

    printf("\n|  ");

    if (numberLimbs > 2)
    {
      printf("/ | \\");
    }

    printf("\n|   ");

    if (numberLimbs > 3)
    {
      printf("_|_");
    }

    printf("\n|  ");

    if (numberLimbs > 4)
    {
      printf("/   \\");
    }

    printf("\n|__________\n");
  }
}

int checkLetter(char letter, char *word, char *printedWord)
{
  int i;
  int guessedLetters = 0;

  for (i = 0; word[i] != '\0'; i++)
  {
    if (toupper(word[i]) == toupper(letter) && printedWord[i] != letter)
    {
      printedWord[i] = letter;
      guessedLetters++;
    }
  }
  return guessedLetters;
}

int main(void) {
  char gameWord[100];
  FILE *wordList = fopen("words_alpha.txt", "r");
  char letter;
  int i, random;
  
  srand(time(NULL));
  random = ((rand() * NUM_CHARS) % NUM_CHARS);
  if (random > NUM_CHARS - 13)
  {
    random -= 13;
  }
  fseek(wordList, random, SEEK_SET);

  fgets(gameWord, 100, wordList);
  fgets(gameWord, 100, wordList);

  trim(gameWord);
  
  char *printedLine = malloc((strlen(gameWord) + 1) * sizeof(char));
  for (i = 0; gameWord[i] != '\0'; i++)
  {
    printedLine[i] = '_';
  }
  
  int wrongGuesses = 0;
  int rightGuesses = 0;
  int x;
  printLine(printedLine);

  while (1)
  {
    printf("\n\nEnter a letter.\n");
    scanf(" %c", &letter);

    x = rightGuesses;
    rightGuesses+= checkLetter(letter, gameWord, printedLine);
    if (rightGuesses - x == 0)
    {
      printf("Incorrect!\n");
      wrongGuesses++;
    }
    printf("\n");
    
    printLine(printedLine);
    printHangman(wrongGuesses);
    if (wrongGuesses == 5 || wrongGuesses == strlen(gameWord))
    {
      printf("Game over. The word was %s.\n", gameWord);
      break;
    }
    if (rightGuesses == strlen(gameWord))
    {
      printf("You won! Congrats\n");
      break;
    }
  }
  free(printedLine);
  fclose(wordList);
  return 0;
}