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
    int card1;
    int card2;
    int endCount = 0;
    int startCount = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    
    printf("TESTING adventurer_card():\n");
    
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    
    //Tests that the player received the adventurer card
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
    
    //Tests for how many treasure cards are drawn
    for(i=0; i < testG.handCount[thisPlayer]; i++)
    {
        card1 = testG.hand[thisPlayer][i];
        if(card1 == copper || card1 == silver || card1 == gold)
        {
            endCount++;
        }
    }
    
    for(i=0; i < G.handCount[thisPlayer]; i++)
    {
        card2 = G.hand[thisPlayer][i];
        if(card2 == copper || card2 == silver || card2 == gold)
        {
            startCount++;
        }
    }
    
    //Test to make sure the correct amount of treasure cards were drawn
    if(((endCount - startCount) > 0) && ((endCount - startCount) < 3))
    {
        printf("Test passed! %d treasure cards were drawn!\n", (endCount-startCount));
    }
    else{
        printf("Test failed. %d treasure cards. Not enough or too many drawn.\n", (endCount-startCount));
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
        
    //Tests to make sure all tests pass. If not, the program asks user to review
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