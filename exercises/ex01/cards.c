/*
A program designed for a user to count cards for Software Systems 2019.
Name: Prava
Source: Original code from Head First C (page 37)
*/

#include <stdio.h>
#include <stdlib.h>

/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/
void get_name (char *card_name)
{
  puts("Enter the card_name: ");
  scanf("%2s", card_name);
}

/* Gives the corresponding value based on the name of the card.

   Will return 0 if name not recognized.

   card_name: character array of length 3 where name is stored
*/
int get_value (char card_name[3])
{
  int val = 0;
  switch(card_name[0]) {
  case 'K':
  case 'Q':
  case 'J':
    val = 10;
    break;
  case 'A':
    val = 11;
    break;
  case 'X':
    val = 0;
    default:
      val = atoi(card_name);
      if ((val < 1) || (val > 10)) {
        puts("I don't understand that value!");
        val = 0;
      }
    }
  return val;
}

/* Increments or decrements the count based on card value.

   val: card value that is used as logic to update update count
   count: current card count
*/
int update_count (int val, int count)
{
  if ((val > 2) && (val < 7)) {
    count++;
  } else if (val == 10) {
    count--;
  }

  return count;
}

/* Main program function that displays the current card count.

   Takes in user input and evaluates card.
*/
int main()
{
  char card_name[3];
  int count = 0;
  int val;

  while (card_name[0]!='X') {
    get_name(card_name);

    val = 0;
    val = get_value(card_name);

    if (val == 0) {
      continue;
    }

    count = update_count(val,count);
    printf("Current count: %i\n", count);
  }
  return 0;
}
