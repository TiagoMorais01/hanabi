typedef struct card* Card;
typedef struct deck* Deck;

Card newCard();
Card copyCard(Card, int);
Card getCa(Deck, int);
Deck newDeck();
int checkNum(char, int[], int);
int checkChar(char, char[], int);
int getCnum(Card);
int getCpos(Card);
int getCvc(Card);
int getCvn(Card);
char getCc(Card);
void setAllVisCC(Card);
void setAllVisNC(Card);
void DeckNull(Deck, int);
void shuffleDeck(Card*, int);
void createDeck(Deck);
void ConsCard(int, Card, char, int);
void giveTipN(Card*, int);
void giveTipC(Card*, char);
void printCards(Deck);
void gototrash(Deck, Deck, Card, int, int);
void swapT(Card *, Card *);
int partitionT(Card *, int , int );
void sortTrash(Deck , int , int );
void sortPilha(Card *, int , int );
void freePi(Card *);
void newPilha(Card *);
