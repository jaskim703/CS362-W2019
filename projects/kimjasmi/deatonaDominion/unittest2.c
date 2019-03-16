/******************************************
* Author: Jasmine Kim
* Date: 2-6-19
* Assignment: unittest2.c tests the updateCoins
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

//Tests the updateCoins function
int main()
{
    int i;
    int numTest = 1;
    int seed = 1000;
    int numPlayer = 2;
    int bonus;
    int false = 0;
    int maxBonus = 10;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int p, handCount;
    int maxHandCount = 5;

    //Fills the array with the corresponding coins
    for(i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf("TESTING updateCoins():\n");

    for(p = 0; p < numPlayer; p++)
    {
        for(handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for(bonus = 0; bonus <= maxBonus; bonus++)
            {
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);

                memset(&G, 23, sizeof(struct gameState));
                initializeGame(numPlayer, k, seed, &G);
                G.handCount[p] = handCount;

                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
		//Tests for count of copper coins
                if(G.coins == handCount * 1 + bonus)  //acts as our assert function
                {
                    printf("Test %d passed! G.coins = %d, expected: %d\n", numTest++, G.coins, handCount * 1 + bonus);
                }
                else
                {
                    printf("Test %d failed! G.coins = %d, expected: %d\n", numTest++, G.coins, handCount * 1 + bonus);
                    false = 1;
                }

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
		//Tests for count of silver coins
                if(G.coins == handCount * 2 + bonus)  //acts as our assert function
                {
                    printf("Test %d passed! G.coins = %d, expected: %d\n", numTest++, G.coins, handCount * 2 + bonus);
                }
                else
                {
                    printf("Test %d failed! G.coins = %d, expected: %d\n", numTest++, G.coins, handCount * 2 + bonus);
                    false = 1;
                }

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
		//Tests for count of gold coins
                if(G.coins == handCount * 3 + bonus)  //acts as our assert function
                {
                    printf("Test %d passed! G.coins = %d, expected: %d\n", numTest++, G.coins, handCount * 3 + bonus);
                }
                else
                {
                    printf("Test %d failed! G.coins = %d, expected: %d\n", numTest++, G.coins, handCount * 3 + bonus);
                    false = 1;
                }
            }
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
