#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Card.h"

struct card{
    int num;
    char color;
    int visibleC;//cor visivel
    int visibleN;//numero visivel
    int pos;
};

struct deck {
    Card deck[50];
};

Card newCard(){
    return (Card) malloc(sizeof(struct card));
}

Card copyCard(Card c, int i){
    c->pos = i;
    return c;
}

Card getCa(Deck d, int nc){
    return d->deck[nc-1];
}

Deck newDeck(){
    int i = 0;
    Deck d = (Deck) malloc(sizeof(struct deck) * 1);
    for(i = 0; i < 50; i++) {
        d->deck[i] = NULL;
    }
    return d;
}

int checkNum(int val, int arr[], int n){
    int i = 0;
    int v = 1;
    for (i = 0; i < n; i++){
        if(val == arr[i]){
            v = 0;
            break;
        }
    }
    return v;
}

int checkChar(char c, char arr[], int n){
    int i = 0;
    int v = 1;
    for (i = 0; i < n; i++){
        if(c == arr[i]){
            v = 0;
            break;
        }
    }
    return v;
}

int getCnum(Card c){
    return c->num;
}

int getCpos(Card c){
    return c->pos;
}

int getCvc(Card c){
    return c->visibleC;
}

int getCvn(Card c){
    return c->visibleN;
}

char getCc(Card c){
    return c->color;
}

void setAllVisCC(Card c){
    c->visibleC = 1;
}

void setAllVisNC(Card c){
    c->visibleN = 1;
}

void DeckNull(Deck d, int nc){
    d->deck[nc-1] = NULL;
}

void ConsCard(int n, Card ca, char c, int posN) {
    ca->num = n;
    ca->color = c;
    ca->pos = posN;
    ca->visibleC = 0;
    ca->visibleN = 0;
}

void shuffleDeck(Card *cardN, int n){
    if (n > 1) {
        time_t t;
        srand((unsigned) time(&t));
        size_t i = 0;
        for (i = 0; i < n - 1; i++) {
            //RAND_MAX e dividido por o numero de cartas menos a posicao do array + 1
            //somo a posicao do array ao rand() e depois divido pelo comentario acima
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            Card t = cardN[j];
            cardN[j] = cardN[i];
            cardN[i] = t;
        }
    }
}


void createDeck(Deck d){
    int i = 0, j = 0, num = 1;
    //ciclo para inserir as cartas no array cores/numeros
    for(j = 0; j < 5; j++){
        for(i = 0; i < 10 ; i++){
            d->deck[i+j*10] = newCard();
            if(num == 1){
                if(i/2+1 != 1)
                    ConsCard(i/2+(i%2), d->deck[i+j*10], 'B', i+j*10);
                else
                    ConsCard(i/2+1, d->deck[i+j*10], 'B', i+j*10);
            }
            else if(num == 2){
                if(i/2+1 != 1)
                    ConsCard((i/2)+(i%2), d->deck[i+j*10], 'R', i+j*10);
                else
                    ConsCard(i/2+1, d->deck[i+j*10], 'R', i+j*10);
            }
            else if(num == 3){
                if(i/2+1 != 1)
                    ConsCard(i/2+(i%2), d->deck[i+j*10], 'G', i+j*10);
                else
                    ConsCard(i/2+1, d->deck[i+j*10], 'G', i+j*10);
            }
            else if(num == 4){
                if(i/2+1 != 1)
                    ConsCard(i/2+(i%2), d->deck[i+j*10], 'Y', i+j*10);
                else
                    ConsCard(i/2+1, d->deck[i+j*10], 'Y', i+j*10);
            }
            else{
                if(i/2+1 != 1)
                    ConsCard(i/2+(i%2), d->deck[i+j*10], 'W', i+j*10);
                else
                    ConsCard(i/2+1, d->deck[i+j*10], 'W', i+j*10);
            }
        }
        num++;
    }
    //Função que baralha o Deck
    shuffleDeck(d->deck, 50);
}

void giveTipN(Card *cards, int val){
    int i = 0;
    for (i = 0; i < 5; i++){
        if(cards[i]->num == val){
            cards[i]->visibleN = 1;
        }
    }
}

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

void gototrash(Deck d, Deck t, Card c, int n, int nc) {
    c->pos = n;
    d->deck[nc-1] = NULL;
    t->deck[n] = c;
}

void swapT(Card *xp, Card *yp){
    Card temp = *xp;
    *xp = *yp;
    *yp = temp;
}

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

void sortTrash(Deck t, int low, int nt){
    if (low < nt){
        /* pi is partitioning index, arr[pi] is now
        at right place */
        int pi = partitionT(t->deck, low, nt);

        sortTrash(t, low, pi - 1);  // Before pi
        sortTrash(t, pi + 1, nt); // After pi
    }
}
