typedef struct _card* Card;//Criar uma variavel global para que a estrutura card possa ser reconhecida
typedef struct _deck* Deck;//Criar uma variavel global para que a estrutura deck possa ser reconhecida
typedef struct _pilha* Pilha;//Criar uma variavel global para que a estrutura pilha possa ser reconhecida

Card newCard();
Card setCardpos(Card, int);
Card getCa(Deck, int);
Card grCa(Deck, int);
Card getCpilha(Pilha, int);
Deck newDeck();
Pilha newPilha();
int checkNum(char, int[], int);
int checkChar(char, char[], int);
int compareCardC(Card, Card);
int compareCardN(Card, Card);
int getCnum(Card);
int getCpos(Card);
int getCvc(Card);
int getCvn(Card);
char getCc(Card);
void setAllVisCC(Card);
void setAllVisNC(Card);
void setCpilha(Pilha, Card, int, int*);
void DeckNull(Deck, int);
void shuffleDeck(Card*, int);
void createDeck(Deck);
void ConsCard(int, Card, char, int);
void giveTipN(Card*, int);
void giveTipC(Card*, char);
void printCards(Deck);
void swapT(Card *, Card *);
int partitionT(Card *, int , int );
void sortTrash(Deck , int , int );
void sortPilha(Pilha , int , int );
void gototrash(Deck, Card, int);
void freePi(Pilha);