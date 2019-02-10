/******************************************
* Author: Jasmine Kim
* Date: 2-6-19
* Assignment: cardtest2.c tests the smithy
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
    int false = 0;
       int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    printf("TESTING smithy_card():\n");

    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! The Smithy card has been drawn.\n");
    else
    {
        printf("Test failed. The Smithy card has not been drawn.\n");
        false = 1;
    }


    cardEffect(smithy, 0, 0, 0, &testG,
            testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer])
        printf("Test passed! The current player has drawn 3 new cards.\n");
    else
    {
        printf("Test failed. The current player has not drawn 3 cards.\n");
        false = 1;
    }

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
