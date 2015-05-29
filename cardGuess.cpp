#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string.h>

#include "cDeck.h"

using namespace std;

unsigned int histo[52];


void zeroHisto()
{
	for (int t = 0; t < 52; t++)
	{
		histo[t] = 0;
	}
}

int histoGetMaxValue()
{
	int retval = 1;
	for (int t = 0; t < 52; t++)
	{
		if (histo[t] > retval) retval = histo[t];
	}
	return retval;
}


void printHisto()
{
	int height = 20;
	int scale = histoGetMaxValue();
	//printf("\x1b[<0>;<0>f");
	system("cls");
	for (int y = height; y > 0; y--)
	{
		for (int x = 0; x < 52; x++)
		{
			if (histo[x] >= y * scale / height)
				printf("\xDB");
			else
				printf(" ");
		}
		printf("\n");
	}

	for (int x = 0; x < 52; x++) printf("-");
	printf("\n");
}


int randWeighted(int cc[4])
{
	int sum = cc[0] + cc[1] + cc[2] + cc[3];
	if (sum == 0) sum = 1;
	int randVal = rand()%(sum);

	if (randVal < cc[0]) return 0;
	else if (randVal >= cc[0] && randVal < cc[0]+cc[1]) return 1;
	else if (randVal >= cc[0]+cc[1] && randVal < cc[0]+cc[1]+cc[2]) return 2;
	else if (randVal >= cc[0]+cc[1]+cc[2]) return 3;
}



int main(int argc, char **argv)
{	

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
	system("pause");






	cDeck deck;


	//=====================================================
	//    Blind
	//
	//-----------------------------------------------------
	zeroHisto();
	for (int runs = 0; runs < 100000; runs++)
	{
		deck.shuffle();
		int correct = 0;
		for (int t = 0; t < 52; t++)
		{
			int guess = rand()%4;
			if (guess == deck.cards[t]) correct++;
		}
		histo[correct]++;
	}
	
	printHisto();
	printf("Blind:\n");
	system("pause");
	


	//=====================================================
	//    Basic card counting
	//
	//-----------------------------------------------------
	zeroHisto();
		
	for (int runs = 0; runs < 10000; runs++)
	{
		deck.shuffle();
		int correct = 0;
		int cc[4] = {13,13,13,13};

		for (int t = 0; t < 52; t++)
		{
			int guess = randWeighted(cc);
			if (guess == deck.cards[t]) correct++;
			cc[deck.cards[t]]--;
		}
		histo[correct]++;
	}
	
	printHisto();
	printf("Basic Counting:\n");
	system("pause");


	//=====================================================
	//    Depreciating history
	//
	//-----------------------------------------------------
	zeroHisto();
		
	for (int runs = 0; runs < 10000; runs++)
	{
		deck.shuffle();
		int correct = 0;
		int cc[4] = {1,1,1,1};

		for (int t = 0; t < 52; t++)
		{
			int guess = randWeighted(cc);
			if (guess == deck.cards[t]) correct++;
			cc[0]++;
			cc[1]++;
			cc[2]++;
			cc[3]++;
			cc[deck.cards[t]] = 0;
		}
		histo[correct]++;
	}
	
	printHisto();
	printf("Depreciating History:\n");
	system("pause");


	//=====================================================
	//    Basic card counting + Depreciating history
	//
	//-----------------------------------------------------
	zeroHisto();
	for (int runs = 0; runs < 10000; runs++)
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
			if (guess == deck.cards[t]) correct++;
			cc[0]++;
			cc[1]++;
			cc[2]++;
			cc[3]++;
			cc[deck.cards[t]] = 0;
			cc2[deck.cards[t]]--;
		}
		histo[correct]++;
	}
	
	printHisto();
	printf("Basic card counting + Depreciating history:\n");
	system("pause");




}