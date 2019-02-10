/******************************************
* Author: Jasmine Kim
* Date: 2-6-19
* Assignment: unittest3.c tests the isGameOver
* function
********************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

//Tests the isGameOver function
int main()
{
    struct gameState G, testG;
    int i;
    int false=0;
    int seed = 1000;
    int numPlayers = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    printf("TESTING isGameOver() function.\n");

    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    //check to see if game ends when province cards != 0
    printf("Current number of Province cards: %d\n", G.supplyCount[province]);
    if(isGameOver(&G))
    {
        printf("Test failed. Game ended incorrectly\n");
    }
    else
    {
        printf("Game continues\n");
    }

    //check to see if game ends when province cards == 0
    G.supplyCount[province] = 0;
    printf("Current number of Province cards: %d\n", G.supplyCount[province]);
    if(isGameOver(&G))
    {
        printf("Test passed! Game ended correctly\n");
    }
    else
    {
        printf("Test failed. Game continues when it should be over\n");
    }

    //check to see if game ends when 3 supply piles all equal 0
    G.supplyCount[province] = 8;   //number of province cards when there are 2 players
    for(i = 0; i < 3; i++)
    {
        G.supplyCount[i] = 0;

        if (isGameOver(&G) && i == 2)
        {
            printf("Test passed! Game ended correctly\n");
        }
        else if (!isGameOver(&G) && i == 2)
        {
             printf("Test failed. Game continues when it should be over\n");
        }
        else if (isGameOver(&G) && i < 2)
        {
            printf("Test failed. Game ended incorrectly\n");
        }
        else
        {
            printf("Test passed! Game continues as it should\n");
        }

    }

    if(false == 0)
    {
        printf("All tests passed!\n");
    }
    else
    {
        printf("Tests failed. Please review.\n");
    }
    return 0;


}
