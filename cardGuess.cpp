#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string.h>

#include "cDeck.h"

using namespace std;

unsigned int histo[52];
unsigned int histoTime[52];

void zeroHisto()
{
	for (int t = 0; t < 52; t++)
	{
		histo[t] = 0;
		histoTime[t] = 0;
	}
}

int histoGetMaxValue(unsigned int *data)
{
	int retval = 1;
	for (int t = 0; t < 52; t++)
	{
		if (data[t] > retval) retval = data[t];
	}
	return retval;
}

int histoGetMaxIndex(unsigned int *data)
{
	int max = histoGetMaxValue(data);
	for (int t = 51; t > 0; t--)
	{
		if (data[t] == max) return t;
	}
	return 0;
}

float histoGetMean(unsigned int *data)
{
	unsigned int sum, weighted;
	for (int t = 0; t < 52; t++)
	{
		weighted += data[t] * t;
		sum += data[t];
	}
	return (float)weighted / (float)sum;
}

void printHistoData(unsigned int *data)
{
	printf("Histo Data:\n");
	for (int t = 0; t < 52; t++) printf("\t%2d, %7d\n",t, data[t]);
}

void printHisto(int height, unsigned int *data)
{
	int scale = histoGetMaxValue(data);
	//printf("\033[0;0f"); 
	for (int x = 0; x < 52; x++) printf("-");
	printf("\n");
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < 52; x++)
		{
			if (data[x] <= int((float(y + 0.2)) * (float)scale / (float)height) || data[x] == 0)
				printf(" ");
			else
				printf("|");
		}
		printf("\n");
	}

	for (int x = 0; x < 52; x++) printf("-");
	printf("\n");
	printHistoData(data);
}



int randWeighted(int cc[4])
{
	int sum = cc[0] + cc[1] + cc[2] + cc[3];
	if (sum == 0)
	{
		return rand()%4;
	}
	int randVal = rand()%(sum);

	if (randVal < cc[0]) return 0;
	else if (randVal >= cc[0]       && randVal < cc[0]+cc[1]) return 1;
	else if (randVal >= cc[0]+cc[1] && randVal < cc[0]+cc[1]+cc[2]) return 2;
	else if (randVal >= cc[0]+cc[1]+cc[2]) return 3;
	return 0;
}



int main(int argc, char **argv)
{	
	int runsMax = 100000;
	system("clear");

	/*
	//=====================================================
	//    Test weighting
	//
	//-----------------------------------------------------
	zeroHisto();
	for (int runs = 0; runs < 10000; runs++)
	{
		int cc[4] = {0,1,2,3};
		histo[randWeighted(cc)]++;
	}
	for (int runs = 0; runs < 10000; runs++)
	{
		int cc[4] = {3,2,1,0};
		histo[randWeighted(cc)+4]++;
	}
	for (int runs = 0; runs < 10000; runs++)
	{
		int cc[4] = {0,0,0,0};
		histo[randWeighted(cc)+8]++;
	}
	for (int runs = 0; runs < 10000; runs++)
	{
		int cc[4] = {1,1,1,1};
		histo[randWeighted(cc)+12]++;
	}
	
	printHisto();
	printf("Weight Test:\n");
*/





	cDeck deck;


	//=====================================================
	//    Blind
	//
	//-----------------------------------------------------
	zeroHisto();
	for (int runs = 0; runs < runsMax; runs++)
	{
		deck.shuffle();
		int correct = 0;
		for (int t = 0; t < 52; t++)
		{
			int guess = rand()%4;
			if (guess == deck.cards[t])
			{
				correct++;
				histoTime[t]++;
			}
		}
		histo[correct]++;
	}
	
	printHisto(10, histo);
	printHisto(5, histoTime);
	printf("Blind: %.4f         \n", histoGetMean(histo));
	


	//=====================================================
	//    Basic card counting
	//
	//-----------------------------------------------------
	zeroHisto();
		
	for (int runs = 0; runs < runsMax; runs++)
	{
		deck.shuffle();
		int correct = 0;
		int cc[4] = {13,13,13,13};

		for (int t = 0; t < 52; t++)
		{
			int guess = randWeighted(cc);
			if (guess == deck.cards[t]) 
			{
				correct++;
				histoTime[t]++;
			}
			cc[deck.cards[t]]--;
		}
		histo[correct]++;
	}
	
	printHisto(10, histo);
	printHisto(5, histoTime);
	printf("Basic Counting: %.4f         \n", histoGetMean(histo));


	//=====================================================
	//    Depreciating history
	//
	//-----------------------------------------------------
	zeroHisto();
		
	for (int runs = 0; runs < runsMax; runs++)
	{
		deck.shuffle();
		int correct = 0;
		int cc[4] = {1,1,1,1};

		for (int t = 0; t < 52; t++)
		{
			int guess = randWeighted(cc);
			if (guess == deck.cards[t])
			{
				correct++;
				histoTime[t]++;
			}
			cc[0]++;
			cc[1]++;
			cc[2]++;
			cc[3]++;
			cc[deck.cards[t]] = 1;
		}
		histo[correct]++;
	}
	
	printHisto(10, histo);
	printHisto(5, histoTime);
	printf("Depreciating History: %.4f         \n", histoGetMean(histo));


	//=====================================================
	//    Basic card counting * Depreciating history
	//
	//-----------------------------------------------------
	zeroHisto();
	for (int runs = 0; runs < runsMax; runs++)
	{
		deck.shuffle();
		int correct = 0;
		int cc[4] = {1,1,1,1};
		int cc2[4] = {13,13,13,13};
		int ccF[4];

		for (int t = 0; t < 52; t++)
		{
			ccF[0] = cc[0] * cc2[0];
			ccF[1] = cc[1] * cc2[1];
			ccF[2] = cc[2] * cc2[2];
			ccF[3] = cc[3] * cc2[3];
			int guess = randWeighted(ccF);
			if (guess == deck.cards[t])
			{
				correct++;
				histoTime[t]++;
			}
			cc[0]++;
			cc[1]++;
			cc[2]++;
			cc[3]++;
			cc[deck.cards[t]] = 1;
			cc2[deck.cards[t]]--;
		}
		histo[correct]++;
	}
	
	printHisto(10, histo);
	printHisto(5, histoTime);
	printf("Basic card counting * Depreciating history: %.4f         \n", histoGetMean(histo));




}