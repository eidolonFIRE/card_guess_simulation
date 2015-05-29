#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string.h>

#include "cDeck.h"

using namespace std;

cDeck::cDeck()
{
	// init deck
	for (int t = 0; t < 52; t++) cards[t] = (t / 13);
}

void cDeck::print()
{
	for (int t = 0; t < 52; t++) printf("%c", cards[t] + 1);
	printf("\n");
}

void cDeck::shuffle()
{
	for (int t = 0; t < 4; t++)
	{
		bool done = false;
		int aa = 0, bb = 26, ii = 0;
		char temp[52];
		while (!done)
		{
			if (rand()%2 == 0)
			{
				if (aa < 26)
				{
					temp[ii] = cards[aa];
					ii++;
					aa++;
				}
			}
			else
			{
				if (bb < 52)
				{
					temp[ii] = cards[bb];
					ii++;
					bb++;
				}
			}
			if (ii >= 52) done = true;
		}
		memcpy(cards, temp, 52 * sizeof(char));
	}
}

