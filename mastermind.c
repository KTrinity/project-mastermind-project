/**
 * mastermind
 * Itty-bitty mastermind type game.
 * 
 * OBJECT:
 *
 *   The object of the game is to guess what the computer has choosen.
 *
 *   The computer starts out by randomly selecting a number of symbols. Your job
 *   is to figure out what the symbols are. You have a limited number of 
 *   attempts, so there is some guidance. First, if you are correct in any of
 *   the guesses, you will be told so. You won't be told which peice is right,
 *   but your correct count will go up. Analysis of previous moves will allow
 *   you to make a judgement as to which one is right. Also, you will be told
 *   if you have choosen a correct type of symbol. Obviously if you have a 
 *   symbol in the correct location, you will have a correct symbol type.
 *
 * COPYRIGHT:
 *   Game idea, based on other games. 
 *   Code licenseed under the GNU GPL <http://www.gnu.org/licenses/gpl.txt>
 *   (c) 2004 Andrew Gwozdziewycz <gwozdzie@lucas.cis.temple.edu>
 *   
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_GUESSES 10
#define NUM_PEICES 4
#define NUM_COLORS 6 

static char things[] = {'+', '*' , '=', '&', '^', '%'};

static int number_correct = 0;
static int number_color = 0;

static char game[NUM_PEICES + 1];
static char guess[NUM_PEICES];

int get_guess(int n);
void do_check();
int count_color();
void generate_game(int n);

int
main(int argc, char **argv)
{
   int count = 0;

   generate_game(NUM_PEICES);    

   while (++count <= NUM_GUESSES) {
      if ((get_guess(NUM_PEICES)) != NUM_PEICES) {
        printf("Enter a valid guess next time!\nGame was %s\n", game);
        exit(1);
      }

      do_check();
      if (number_correct >= NUM_PEICES) {
        /* win */
        printf("\nYou win!\n");
        exit(1);
      }
      else {
        printf("\n%d Nope:\t%d correct \t%d color correct\n", 
                  count, number_correct, number_color);
      }
   }

   printf("\nSorry you lose!\nIt was %s\n", game);
   return 0;
}

void
generate_game(int n)
{
   int i;
   srandom(getpid());
   for (i = 0; i < n; i++) {
      game[i] = things[ random() % NUM_COLORS ];
   }
   game[++i] = '\0';
}

int
get_guess(int n)
{
   char a[256];
   int bc = 0, i, j, gi = 0;
   printf("Enter a guess of %d from the characters %s\n", NUM_PEICES, things);
   while ((bc < 256) && (a[bc] = getc(stdin)) && (a[bc] != '\n')) { bc++; }
   a[bc] = '\0';
   for (i = 0; i < bc && gi < NUM_PEICES; i++) {
      for (j = 0; j < NUM_COLORS; j++) {
         if (a[i] == things[j]) {
           guess[gi++] = a[i];
         }
      }   
   }
   return gi;
}

void 
do_check()
{
   int i;
   number_correct = 0;
   if (strcmp(guess,game) == 0) {
     number_correct = NUM_PEICES;
   }
   /* not an easy win right away */
   for (i = 0; i < NUM_PEICES; i++) {
      if (guess[i] == game[i]) {
        number_correct++;
      }
   }
   count_color();
}

int
count_color()
{
   char seen[NUM_PEICES+1];
   int si = 0;
   int i, r = 0;
   number_color = 0;
   for (i = 0; i < NUM_PEICES; i++) {
      seen[i] = 0; 
   }
   for (i = 0; i < NUM_PEICES; i++) {
      if (strchr(game, guess[i]) && !strchr(seen, guess[i])) {
        seen[si++] = guess[i];
        number_color++;
      }
   } 
   return r;
}
