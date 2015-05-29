
#define HEART   0
#define DIAMOND 1
#define CLUB    2
#define SPADE   3

class cDeck
{
	public:
		char cards[52];

		cDeck();

		void print();
		void shuffle();
};