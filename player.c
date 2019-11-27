#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Card.h"
#include "player.h"

struct player{
    char nome[128];
    Card cards[5];
};

Player newPlayer(char *nomeN){
    Player p = (Player) malloc(sizeof(struct player));
    int i = 0;
    for(i = 0; i < 5; i++){
        p->cards[i] = NULL;
    }
    strcpy(p->nome, nomeN);
    return p;
}

Card getCard(Player p, int i){
    return p->cards[i];
}

int tamNpl(Player p){
    return strlen(p->nome);
}

int contC(Player p){
    int n = 0;
    int i = 0;
    for(i = 0; i < 5; i++){
        if(p->cards[i] != NULL)
            n++;
    }
    return n;
}

void swapN(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int partition (int *arr, int low, int high){
    // pivot (Element to be placed at right position)
    int pivot = arr[high];
 
    int i = (low - 1);  // Index of smaller element
    int j = 0;
    for (j = low; j <= high - 1; j++){
        // If current element is smaller than the pivot
        if (arr[j] <= pivot){
            i++;    // increment index of smaller element
            swapN(&arr[i], &arr[j]);
        }
    }
    swapN(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int *arr, int low, int high){
    if (low < high){
        /* pi is partitioning index, arr[pi] is now
        at right place */
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
}

char *getnome(Player p){
    return (p->nome);
}

void freeP(Player p){
    int i = 0;
    for(i = 0; i < 5; i++){
        if(p->cards != NULL)
            free(p->cards[i]);
    }
    free(p);
}

void showCard(){
    return;
}

void setAllVisCP(Player p){
    int i = 0;
    for (i = 0; i < 5; i++){
        setAllVisCC(p->cards[i]);
    }
}

void setAllVisNP(Player p){
    int i = 0;
    for (i = 0; i < 5; i++){
        setAllVisNC(p->cards[i]);
    }
}

void selNum(Player p, int play){
    int n = 0;
    int i = 0;
    int arr[5];
    int j = 0;
    char val = 0;
    for (i = 0; i < 5; i++){
        if(checkNum( ( (char) getCnum(p->cards[i])+48 ), arr, j ) || i == 0){
            arr[j] = getCnum(p->cards[i]);
            j++;
        }
    }

    quickSort(arr, 0, j-1);

    printf("Qual e o numero que quer indicar?\n");
    printf("Numero: %d", arr[0]);
    for (i = 1; i < j; i++){
        printf(" %d", arr[i]);
    }
    printf("\n0 - Voltar para o menu");
    printf("\n->");
    while (getchar()!='\n');
    scanf("%c", &val);

    while ((checkNum(val, arr, j))){
        
        printf("Esse numero não existe!!!\n");
        printf("Qual e o numero que quer indicar?\n");
        printf("Numero: %d", arr[0]);
        for (i = 1; i < j; i++){
            printf(" %d", arr[i]);
        }
        printf("\n0 - Voltar para o menu");
        printf("\n->");
        while (getchar()!='\n');
        scanf("%c", &val);
    }
    
    giveTipN(p->cards, ((int)val)-48);
}

void selCor(Player p, int play){
    int n = 0;
    int i = 0;
    char arr[5];
    int j = 0;
    char val;
    //armazena as letras das cores para nao ter letras repetidas
    for (i = 0; i < 5; i++){
        if(checkChar(getCc(p->cards[i]), arr, j) || i == 0){
            arr[j] = getCc(p->cards[i]);
            j++;
        }
    }

    //perguntar qual é a cor que o utilizador deseja indicar
    printf("Qual e o cor que quer indicar?\n");
    printf("Cor: %c", arr[0]);
    for (i = 1; i < j; i++){
        printf(" %c", arr[i]);
    }
    printf("\n0 - Voltar para o menu");
    printf("\n->");
    fflush(stdin);
    scanf("%s", &val);
    
    while (checkChar(val, arr, j)){
        printf("Essa cor não existe!!!\n");
        printf("Qual e o cor que quer indicar?\n");
        printf("Cor: %c", arr[0]);
        for (i = 1; i < j; i++){
            printf(" %c", arr[i]);
        }
        printf("\n0 - Voltar para o menu");
        printf("\n->");
        fflush(stdin);
        scanf("%s", &val);
    }

    giveTipC(p->cards, val);
}

void pickCard(Player p, Card cardN){
    int i;
    int pos = 0;
    
    for(i = 4; i > 0; i--){
        if(p->cards[i] == NULL){
            p->cards[i] = copyCard(p->cards[i - 1], i);
            p->cards[i - 1] = NULL;
        }
    }
    
    p->cards[0] = copyCard(cardN, 0); //pega numa carta do Deck
}

void dealCards(Player jog, Player ai, Deck d, int *nc){
    int i = 0;
    time_t t;
    srand((unsigned) time(&t));
    int n = rand() % 2;
    for (i = 0; i < 5; i++){
        if(n == 0){
            ai->cards[i] = copyCard(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            jog->cards[i] = copyCard(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            n = 1;
        }
        else{
            jog->cards[i] = copyCard(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            ai->cards[i] = copyCard(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            n = 0;
        }
    }
    
}

void printCp(Player p){
    int i = 0;
    printf("Player: %s\nCards:\n", p->nome);
    for (i = 0; i < 5; i++){
        printf("Card %d - C: %c N: %d P: %d VC: %d VN: %d\n", i+1, getCc(p->cards[i]), getCnum(p->cards[i]), getCpos(p->cards[i]), getCvc(p->cards[i]), getCvn(p->cards[i]));
    }
}
