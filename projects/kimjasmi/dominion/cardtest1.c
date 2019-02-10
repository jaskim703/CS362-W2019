/******************************************
* Author: Jasmine Kim
* Date: 2-6-19
* Assignment: cardtest1.c tests the adventurer
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
    int i;
    int false = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int cardDrawn1;
    int cardDrawn2;
    int finalCount = 0;
    int originalCount = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    
    printf("TESTING adventurer_card():\n");
    
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
    testG.handCount[thisPlayer]++;
    if(G.handCount[thisPlayer]+ 1 == testG.handCount[thisPlayer])
    {
        printf("Test passed. The Adventurer card has been drawn.\n");
    }
    else
    {
        printf("Test failed. The Adventurer card has not been drawn.\n");
        false = 1;
    }
    
    cardEffect(adventurer, 0, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);
    
    for(i=0; i < testG.handCount[thisPlayer]; i++)
    {
        cardDrawn1 = testG.hand[thisPlayer][i];
        if(cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold)
        {
            finalCount++;
        }
    }
    
    for(i=0; i < G.handCount[thisPlayer]; i++)
    {
        cardDrawn2 = G.hand[thisPlayer][i];
        if(cardDrawn2 == copper || cardDrawn2 == silver || cardDrawn2 == gold)
        {
            originalCount++;
        }
    }
    
    if((finalCount - originalCount) > 0 || (finalCount - originalCount) < 3)
    {
        printf("Test passed! %d treasure cards were drawn!\n", (finalCount-originalCount));
    }
    else{
        printf("Test failed. Not enough or too many treasure cards drawn.\n");
        false = 1;
    }
    
    if (G.handCount[thisPlayer] < testG.handCount[thisPlayer])
    {
        printf("Test passed! Cards were added to the hand.\n");
    }
    else
    {
        printf("Test failed. Cards were not added to the hand.\n");
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