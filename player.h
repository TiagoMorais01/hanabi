typedef struct player* Player;

Player newPlayer(char *);
Card getCard(Player, int);
int tamNpl(Player);
int contC(Player);
void swapN(int *, int *);
char *getnome(Player);
void freeP(Player);
void showCard();
void setAllVisCP(Player);
void setAllVisNP(Player);
int partition (int*, int, int);
void quickSort(int*, int, int);
void selNum(Player, int);
void selCor(Player, int);
void pickCard(Player, Card);
void dealCards(Player, Player, Deck, int *);
void printCp(Player);