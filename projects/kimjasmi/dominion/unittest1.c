/******************************************
* Author: Jasmine Kim
* Date: 2-6-19
* Assignment: unittest1.c tests the whoseTurn
* function
********************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "assert.h"

//Tests the whoseTurn function
int main()
{
    struct gameState G;
    int i;
    int false=0;
    int x=0;


    printf("TESTING whoseTurn() function.\n");

    for(i = 0; i < 5; i++)
    {
        G.whoseTurn = x;

        if(whoseTurn(&G) == x)
        {
            printf("Test # %d passed!\n", i+1);
        }
        else
        {
            printf("Test # %d failed. Expected: %d   Actual: %d\n", i+1, x, whoseTurn(&G));
            false = 1;
        }
        x++;
    }

    if(false == 0)
    {
        printf("All tests passed!\n");
    }
    else
    {
        printf("Test(s) failed. Try again");
    }

    return 0;
}
