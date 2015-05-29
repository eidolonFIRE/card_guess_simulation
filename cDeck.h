
#define NONE    0
#define HEART   1
#define SPADE   2
#define DIAMOND 3
#define CLUB    4

class cDeck
{
	public:
		char cards[52];

		cDeck();

		void printDeck();
		void shuffle();
		char flipCard();
};