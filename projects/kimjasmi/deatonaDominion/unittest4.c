/******************************************
* Author: Jasmine Kim
* Date: 2-6-19
* Assignment: unittest4.c tests the buyCard
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

//Tests the buyCard function
int main()
{
    struct gameState G;
    int false = 0;

     printf("TESTING buyCard() function.\n");

     //Set number of buys and coins
     G.numBuys = 2;
     G.coins = 2;
     printf("Test to see if enough coins\n");
     int x = buyCard(2, &G);
     if(x == -1)
     {
         printf("Test passed! Not enough coins\n");
     }
     else
     {
         printf("Test failed. Recheck number of coins\n");
         false = 1;
     }

     //Test to see if we can buy the card we want
     G.coins = 8;
     x = buyCard(2, &G);
     if (x == 0)
     {
         printf("Test passed! Card of choice can be bought\n");
     }
     else
     {
         printf("Test failed. Unable to purchase card\n");
         false = 1;
     }

     //Test for remaining number of buys
     x = buyCard(2, &G);
     if(x == -1)
     {
         printf("Test passed! No remaining buys\n");
     }
     else
     {
         printf("Test failed. There are buys remaining\n");
         false = 1;
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
