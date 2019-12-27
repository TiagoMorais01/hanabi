#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Card.h"

struct _card{
    int num;
    char color;
    int visibleC;//cor visivel
    int visibleN;//numero visivel
    int pos;//posição da carta onde se encontra atualmente
};

struct _deck {
    Card deck[50];
};

struct _pilha {
    Card pilha[25];
};

//Aloca memoria para cria uma nova carta
Card newCard(){
    return (Card) malloc(sizeof(struct _card));
}

//Define a posião da carta
Card setCardpos(Card c, int i){
    c->pos = i;
    return c;
}

//Função para obter uma carta do Deck(ou trash)
Card getCa(Deck d, int nc){
    return d->deck[nc-1];
}

//Função para obter e remover uma carta do Dekc(ou trash)
Card grCa(Deck d, int nc){
    Card aux = d->deck[nc - 1];
    d->deck[nc - 1] = NULL;
    return aux;
}

//Função para obter uma carta da pilha
Card getCpilha(Pilha p, int np){
    return p->pilha[np];
}

//Função para criar um novo Deck
Deck newDeck(){
    int i = 0;
    Deck d = (Deck) malloc(sizeof(struct _deck));
	if (d) {
		for (i = 0; i < 50; i++) {
			d->deck[i] = NULL;
		}
	}
    return d;
}

//Função para criar um novo Pilha
Pilha newPilha(){
    int i = 0;
    Pilha p = (Pilha) malloc(sizeof(struct _pilha));
	if (p) {
		for (i = 0; i < 25; i++) {
			p->pilha[i] = NULL;
		}
	}
    return p;
}

//Função para verificar se é um numero e se for ver se esse numero está dentro do array que tem os numeros das cartas disponiveis para dar a dica
int checkNum(char val, int arr[], int n){
    
    int v = 1;
    if (isdigit(val)){
        if (((int)val - 48) == 0 )
            v = 0;
        else{
            int i = 0;
            for (i = 0; i < n; i++){
                if(( (int)val - 48) == arr[i]){
                    v = 0;
                    break;
                }
            }
        }
    }
    else
        v = 1;
    
    return v;
}

//Função para verificar se é um carater e se for ver se esse caracter está dentro do array que tem os caracteres das cartas disponiveis para dar a dica
int checkChar(char c, char arr[], int n){
    int v = 1;
    if (isdigit(c) && (((int)c - 48) == 0))
        v = 0;
    else{
        int i = 0;
        for (i = 0; i < n; i++){
            if(c == arr[i]){
                v = 0;
                break;
            }
        }
    }
    return v;
}

//Compara duas cartas
int compareCardC(Card c1, Card c2){
    return (c1->color == c2->color) ? 1 : 0;
}

int compareCardN(Card c1, Card c2){
    return (c1->num + 1 == c2->num) ? 1 : 0;
}

//Funcção para obter o numero de uma carta
int getCnum(Card c){
    return c->num;
}

//Funcção para obter a posição de uma carta
int getCpos(Card c){
    return c->pos;
}

//Função para obter se a cor da carta é visível
int getCvc(Card c){
    return c->visibleC;
}

//Função para obter se o numero da carta é visível
int getCvn(Card c){
    return c->visibleN;
}

//Função para obter a cor de uma carta
char getCc(Card c){
    return c->color;
}

void setCpos(Card c, int i){
    c->pos = i;
}

//Atribuir uma carta a um deck(trash)
void setCard(Deck dt, Card c, int i){
    dt->deck[i] = c;
}

//Atribui uma carta à pilha
void setCpilha(Pilha pi, Card c, int i){
    pi->pilha[i] = c;
}

//Função para definir todas as cores visiveis das cartas
void setAllVisCC(Card c){
    c->visibleC = 1;
}

//Função para definir todos os numeros visiveis das cartas
void setAllVisNC(Card c){
    c->visibleN = 1;
}

//Função para por uma posição do Deck NULL 
void DeckNull(Deck d, int nc){
    d->deck[nc-1] = NULL;
}

//Função para atribuir valores a uma carta
void ConsCard(Card ca, int n, char c, int posN, int vn, int vc) {
    ca->num = n;
    ca->color = c;
    ca->pos = posN;
    ca->visibleC = vc;
    ca->visibleN = vn;
}

//Função para baralhar o Deck
void shuffleDeck(Card *cardN, int n){
    if (n > 1) {
        time_t t;
        srand((unsigned) time(&t));
        int i = 0;
		int j = 0;
		Card tc;
        for (i = 0; i < n - 1; i++) {
            //Divido o RAND_MAX pelo numero de cartas menos a posicao do array + 1
            //Somo a posicao do array ao rand() e depois divido pelo comentario acima
            j = i + rand() / (RAND_MAX / (n - i) + 1);
            tc = cardN[j];
            cardN[j] = cardN[i];
            cardN[i] = tc;
        }
    }
}

//Função atribuir as cartas ao Deck
void createDeck(Deck d){
    int i = 0, j = 0, num = 1;
    //ciclo para inserir as cartas no array cores/numeros
    for(j = 0; j < 5; j++){
        for(i = 0; i < 10 ; i++){
            d->deck[i+j*10] = newCard();
            if(num == 1){
                if(i/2+1 != 1)
                    ConsCard(d->deck[i+j*10], i/2+(i%2), 'B', i+j*10, 0, 0);
                else
                    ConsCard(d->deck[i+j*10], i/2+1, 'B', i+j*10, 0, 0);
            }
            else if(num == 2){
                if(i/2+1 != 1)
                    ConsCard(d->deck[i+j*10], (i/2)+(i%2), 'R', i+j*10, 0, 0);
                else
                    ConsCard(d->deck[i+j*10], i/2+1, 'R', i+j*10, 0, 0);
            }
            else if(num == 3){
                if(i/2+1 != 1)
                    ConsCard(d->deck[i+j*10], i/2+(i%2), 'G', i+j*10, 0, 0);
                else
                    ConsCard(d->deck[i+j*10], i/2+1, 'G', i+j*10, 0, 0);
            }
            else if(num == 4){
                if(i/2+1 != 1)
                    ConsCard(d->deck[i+j*10], i/2+(i%2), 'Y', i+j*10, 0, 0);
                else
                    ConsCard(d->deck[i+j*10], i/2+1, 'Y', i+j*10, 0, 0);
            }
            else{
                if(i/2+1 != 1)
                    ConsCard(d->deck[i+j*10], i/2+(i%2), 'W', i+j*10, 0, 0);
                else
                    ConsCard(d->deck[i+j*10], i/2+1, 'W', i+j*10, 0, 0);
            }
        }
        num++;
    }
    //Função que baralha o Deck
    shuffleDeck(d->deck, 50);
}

//Função para dar a dica de um numero
void giveTipN(Card *cards, int val){
    int i = 0;
    for (i = 0; i < 5; i++){
        if(cards[i]->num == val){
            cards[i]->visibleN = 1;
        }
    }
}

//Função para dar a dica de um caracter
void giveTipC(Card *cards, char val){
    int i = 0;
    for (i = 0; i < 5; i++){
        if(cards[i]->color == val){
            cards[i]->visibleC = 1;
        }
    }
}

//é só mesmo para vericar se ta tudo bem
void printCards(Deck d) {
    int i = 0;
    for (i = 0; i < 50; i++) {
        printf("NUM: %d - COR: %c - POS: %d\n", d->deck[i]->num, d->deck[i]->color, d->deck[i]->pos);
    }

}

//Função para trocar cartas
void swapT(Card *xp, Card *yp){
    Card temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//Função do quick sort modificado para estruturas do tipo cartas
int partitionT(Card *c, int low, int high){
    // pivot (Element to be placed at right position)
    char pivotC = c[high]->color;
    int pivotI = c[high]->num;
 
    int i = (low - 1);  // Index of smaller element
    int j = 0;
    for (j = low; j <= high - 1; j++){
        // If current element is smaller than the pivot
        if (c[j]->color < pivotC){
            i++;    // increment index of smaller element
            swapT(&c[i], &c[j]);
        }
        else if((c[j]->color == pivotC) && (c[j]->num <= pivotI)){
            i++;    // increment index of smaller element
            swapT(&c[i], &c[j]);
        }
        
    }
    swapT(&c[i + 1], &c[high]);
    return (i + 1);
}

//Função quick sort para ordenar o trash
void sortTrash(Deck t, int low, int nt){
    if (low < nt){
        /* pi is partitioning index, arr[pi] is now
        at right place */
        int pi = partitionT(t->deck, low, nt);

        sortTrash(t, low, pi - 1);  // Before pi
        sortTrash(t, pi + 1, nt); // After pi
    }
}

//Função quick sort para ordenar a pilha
void sortPilha(Pilha pilha, int low, int np){
    if (low < np){
        /* pi is partitioning index, arr[pi] is now
        at right place */
        int pi = partitionT(pilha->pilha, low, np);

        sortPilha(pilha, low, pi - 1);  // Before pi
        sortPilha(pilha, pi + 1, np); // After pi
    }
}

//Função para direcionar a carta para o trash
void gototrash(Deck t, Card c, int nt) {
    c = setCardpos(c, nt);
    t->deck[nt] = c;
}

//Função para libertar memoria do tipo pilha
void freePi(Pilha p){
    int i = 0;
    for(i = 0; i < 25; i++){
        if(p->pilha[i] != NULL)
            free(p->pilha[i]);
    }
    free(p);
}
