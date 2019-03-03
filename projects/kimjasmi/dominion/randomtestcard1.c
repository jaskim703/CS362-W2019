/**************************************
*Author: Jasmine Kim
*Date: 2-22-19
*Assignment: Testing the smithy card
*****************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define ITERATIONS 150000

int main()
{
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    int false;
    int deckSize;
    int handSize;
    int handPos;
    int prevDeck;
    int afterDeck;
    int prevHand;
    int afterHand;
    int discardBefore;
    int discardAfter;
    int i;
    int deckFail = 0;
    int handFail = 0;
    //int discardFail = 0;
    int testPassed = 0;

    srand(time(NULL));
    for(i=0; i < ITERATIONS; i++)
    {
        initializeGame(numPlayers, k, seed, &G);
        deckSize = rand() % (MAX_DECK + 1);
        handSize = rand() % (deckSize + 1);

        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;

        handPos = G.hand[currentPlayer][G.handCount[currentPlayer] - 1];
        prevDeck = G.deckCount[0];
        prevHand = G.handCount[0];
        discardBefore = G.playedCardCount;

         cardEffect(smithy, 0, 0, 0, &G,
            G.hand[currentPlayer][G.handCount[currentPlayer]-1], 0);

        afterDeck = G.deckCount[0];
        afterHand = G.handCount[0];
        discardAfter = G.playedCardCount;

        false = 0;


        if(afterHand != (prevHand + 2)){
            printf("Test fail - number of cards drawn incorrect\n");
            handFail++;
            false = 1;
        }

        if(afterDeck != (prevDeck - 3)){
            printf("Test fail - number of cards taken from deck incorrect \n");
            deckFail++;
            false = 1;
        }

     //   if(discardAfter != (discardBefore + 1)){
     //       printf("Test fail - Smithy card not disposed of properly\n");
     //       discardFail++;
     //       false = 1;
     //   }

        if(false == 0){
            printf("All tests have passed!\n");
            testPassed++;
        }

    }

    printf("\n");
    printf("Number of Tests Passed: %d\n", testPassed);
    printf("Number of Cards Drawn Failed: %d\n", handFail);
  //  printf("Number of failed Smithy Card discards: %d\n\n", discardFail);

    return 0;
}
