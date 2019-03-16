/******************************************
* Author: Jasmine Kim
* Date: 2-6-19
* Assignment: cardtest3.c tests the village
* card
********************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int false = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    printf("TESTING village_card():\n");

    //initialize the game
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    //Test to make sure the card is in the hand
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = village;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! The Village card has been drawn.\n");
    else
    {
        printf("Test failed. The Village card has not been drawn.\n");
        false = 1;
    }

    //Calling the village_card to be played to test
    cardEffect(village, 0, 0, 0, &testG,
            testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    //Tests for 1 card drawn
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! The current player has drawn a new card.\n");
    else
    {
        printf("Test failed. The current player has not drawn a new card.\n");
        false = 1;
    }

    //Tests for adding 2 actions 
    if (G.numActions + 2 == testG.numActions)
    {
        printf("Test passed! The current player has +2 actions.\n");
    }
    else
    {
        printf("Test failed. The current player did not get +2 actions.\n");
        false = 1;
    }
 
    //If all tests pass, will say passed. If any test fails, the program will ask user to review.
    if(false==0)
    {
        printf("Congrats! Tests passed!\n\n");
    }
    else
    {
        printf("Tests failed. Please review.\n\n");
    }
    return 0;
}
