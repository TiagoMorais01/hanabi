typedef struct player* Player;//Criar uma variavel global para que a estrutura jogador possa ser reconhecida

Player newPlayer(char *);
Card getCard(Player, int);
Card grCard(Player, int);
int tamNpl(Player);
int contC(Player);
int selNum(Player, int);
int selCor(Player, int);
int partition (int*, int, int);
char *getnome(Player);
void swapN(int *, int *);
void freeP(Player);
void setAllVisCP(Player);
void setAllVisNP(Player);
void quickSort(int*, int, int);
void pickCard(Player, Card);
void dealCards(Player, Player, Deck, int *);
void printCp(Player);