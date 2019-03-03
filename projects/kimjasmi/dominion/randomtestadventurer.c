/**************************************
*Author: Jasmine Kim
*Date: 2-22-19
*Assignment: Testing the adventurer card
*****************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define ITERATIONS 100000

//random testing adventurer card
int main()
{
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
                
    int deckSize;
    int handSize;
    int i, j, q, m, x;
    int randomCard;
    int randQ;
    int treasureCount;
    int prevTreasureCount;
    int testPassed = 0;
    int drawTestFailed = 0;
    int discardTestFailed = 0;
    int handFailure;
    int discardCopper;
    int discardSilver;
    int discardGold;

    srand(time(NULL));
    for(i=0; i < ITERATIONS; i++)
    {
	//initialize the game 
        initializeGame(numPlayers, k, seed, &G);
        prevTreasureCount = 0;

	//randomize the size of the deck and the size of the hand 
        deckSize = rand() % (MAX_DECK + 1);
        handSize = rand() % (deckSize + 1);
        
	//set the deck count as deck size minus the hand size
        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
        
        for(j=0; j<numPlayers; j++)
        {
            for(q=0; q<G.deckCount[j]; q++)
            {
		//usually about 50 cards in a deck, so choose randomly from 50 to give card values
                randomCard = rand() % (50+1);
                randQ = rand() % (10);
                if(randomCard == 1)
                {
                    G.deck[j][q] = copper;
                }else if (randomCard == 2){
                    G.deck[j][q] = silver;
                }else if (randomCard == 3){
                    G.deck[j][q] = gold;
                }else{
                    G.deck[j][q] = k[randQ];
                }
            }
        }
        
	//counts the treasure cards before playing adventurer card
        for(m=0; m< G.handCount[currentPlayer]; m++)
        {
            if(G.hand[currentPlayer][m]==copper || G.hand[currentPlayer][m]==silver|| G.hand[currentPlayer][m]==gold)
            {
                prevTreasureCount++;
            }
        }
        
	cardEffect(adventurer, 0, 0, 0, &G, G.hand[currentPlayer][G.handCount[currentPlayer]-1], 0);        
        
        treasureCount = 0;
        
	//counts treasure cards after playing adventurer card
         for(m=0; m< G.handCount[currentPlayer]; m++)
        {
            if(G.hand[currentPlayer][m]==copper || G.hand[currentPlayer][m]==silver|| G.hand[currentPlayer][m]==gold)
            {
                treasureCount++;
            }
        }
        
        discardCopper = 0;
        discardSilver = 0;
        discardGold = 0;

        for(x = 0; x < G.discardCount[currentPlayer]; x++){
            if(G.discard[currentPlayer][x] == copper) {
                discardCopper++;
            } else if(G.discard[currentPlayer][x] == silver) {
                discardSilver++;
            } else if(G.discard[currentPlayer][x] == gold) {
                discardGold++;
            }
        }
	handFailure = discardCopper + discardSilver + discardGold;
        int false = 0;
        if(treasureCount > (prevTreasureCount + 2)){
            printf("Test fail - there are too many cards\n");
            drawTestFailed++;
            false = 1;
        }
        
        if( treasureCount < prevTreasureCount){
            printf("Test fail - cards in hand did not match\n");
            drawTestFailed++;
            false = 1;
        }
        if(discardCopper != 0){
            printf("Test fail - Copper discarded\n");
            discardTestFailed++;
            false = 1;
        }

        if(discardSilver != 0){
            printf("Test fail - Silver discarded\n");
            discardTestFailed++;
            false = 1;
        }

        if(discardGold != 0){
            printf("Test fail - Gold discarded\n");
            discardTestFailed++;
            false = 1;
        }

        if(false == 0){
            printf("All tests have passed! \n");
            testPassed++;
        }
   }
   
    printf("\n");
    printf("Number of Tests Passed: %d\n", testPassed);
    printf("Number of Cards Drawn Failed: %d\n", handFailure);
    
    return 0;
        
}