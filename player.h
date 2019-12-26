typedef struct player* Player;//Criar uma variavel global para que a estrutura jogador possa ser reconhecida

Player newPlayer(char *);
Card getCard(Player, int);
Card grCard(Player, int);
int tamNpl(Player);
int selNum(Player, int);
int selCor(Player, int);
int getNCP(Player);
int partition (int*, int, int);
char *getnome(Player);
void lessCardsP(Player);
void plusCardsP(Player);
void swapN(int *, int *);
int playCard(Pilha, Player, int, int);
void pushToLeft(Player);
void setAllVisCP(Player);
void setAllVisNP(Player);
void quickSort(int*, int, int);
void pickCard(Player, Card);
void dealCards(Player, Player, Deck, int *);
void printCp(Player);
void freeP(Player);