#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Card.h"
#include "player.h"
#include "Log.h"
#include "AI.h"

//vê se a AI tem alguma informação das suas cartas
int checkInfo(Player ai, Card Rcard []){
    int i = 0;
    int k = 0;
    for (i = 0; i < getNCP(ai); i++){
        if (getCvc(getCard(ai, i)) == 1 || getCvn(getCard(ai, i)) == 1){
            Rcard[k++] = getCard(ai, i);
        }
    }
    return k;
}

//Verificar se o jogador tem conhecimento de alguma das suas cartas
int checkInfoJog(Player jog){
    int i = 0;
    int n = getNCP(jog);
    for (i = 0; i < n; i++){
        if (getCvc(getCard(jog, i)) == 1 || getCvn(getCard(jog, i)) == 1) break;
    }
    return (i != n);
}

//função para dar uma dica
void darDica(Deck deckM, Deck trash, Pilha pi, Player jog, Log log[], int lives, int *tips, int nc, int nt, int np){
    int PCards[5] = {0, 0, 0, 0, 0};
    getTopCpilha(pi, PCards, np);
    int i = 0;
    int unica = 0;
    int flag = 1;
    char aux[10];
    Card c = NULL;

    for (i = 0; i < getNCP(jog) && flag; i++){
        c = getCard(jog, i);
        if (c != NULL){
            switch (getCc(c)){
                case 'B':{
                    if ((PCards[0] + 1 == getCnum(c)) && (getCvc(c) == 0 || getCvn(c) == 0)){
                        unica = cardsAlone(jog, getCnum(c), 'B');
                        if(unica == 3){
                            if (getCvc(c) == 1){
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NB1: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipC(getCards(jog), 'B');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'B';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 2){
                            if (getCvc(c) == 0){
                                giveTipC(getCards(jog), 'B');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'B';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NB1: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 1){
                            if (getCvn(c) == 1){
                                giveTipC(getCards(jog), 'B');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'B';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NB1: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else{
                            if (getCvc(c) == 0){
                                if (getCvn(c) == 0){
                                    int r =  rand() % 2;
                                    if (r){
                                        giveTipN(getCards(jog), getCnum(c));
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = (char)getCnum(c) + 48;
                                        printf("NB1: %d", (char)getCnum(c) + 48);
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                    else{
                                        giveTipC(getCards(jog), 'B');
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = 'B';
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                }
                                else{
                                    giveTipC(getCards(jog), 'B');
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = 'B';
                                    insertLog(log, aux);
                                    (*tips)--;
                                }
                                flag = 0;
                            }
                            else{
                                if (getCvn(c) == 0){
                                    giveTipN(getCards(jog), getCnum(c));
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = (char)getCnum(c) + 48;
                                    printf("NB1: %d", (char)getCnum(c) + 48);
                                    insertLog(log, aux);
                                    flag = 0;
                                    (*tips)--;
                                }
                            }
                        }
                    }
                    break;
                }
                case 'G':{
                    if ((PCards[1] + 1 == getCnum(c)) && (getCvc(c) == 0 || getCvn(c) == 0)){
                        unica = cardsAlone(jog, getCnum(c), 'G');
                        if(unica == 3){
                            if (getCvc(c) == 1){
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NG3: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipC(getCards(jog), 'G');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'G';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 2){
                            if (getCvc(c) == 0){
                                giveTipC(getCards(jog), 'G');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'G';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NG2: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 1){
                            if (getCvn(c) == 1){
                                giveTipC(getCards(jog), 'G');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'G';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NG1: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else{
                            if (getCvc(c) == 0){
                                if (getCvn(c) == 0){
                                    int r =  rand() % 2;
                                    if (r){
                                        giveTipN(getCards(jog), getCnum(c));
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = (char)getCnum(c) + 48;
                                        printf("NG: %d", (char)getCnum(c) + 48);
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                    else{
                                        giveTipC(getCards(jog), 'G');
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = 'G';
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                }
                                else{
                                    giveTipC(getCards(jog), 'G');
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = 'G';
                                    insertLog(log, aux);
                                    (*tips)--;
                                }
                                flag = 0;
                            }
                            else{
                                if (getCvn(c) == 0){
                                    giveTipN(getCards(jog), getCnum(c));
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = (char)getCnum(c) + 48;
                                    printf("NG: %d", (char)getCnum(c) + 48);
                                    insertLog(log, aux);
                                    flag = 0;
                                    (*tips)--;
                                }
                            }
                        }
                    }
                    break;
                }
                case 'R':{
                    if ((PCards[2] + 1 == getCnum(c)) && (getCvc(c) == 0 || getCvn(c) == 0)){
                        unica = cardsAlone(jog, getCnum(c), 'R');
                        if(unica == 3){
                            if (getCvc(c) == 1){
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NR3: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipC(getCards(jog), 'R');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'R';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 2){
                            if (getCvc(c) == 0){
                                giveTipC(getCards(jog), 'R');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'R';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NR2: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 1){
                            if (getCvn(c) == 1){
                                giveTipC(getCards(jog), 'R');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'R';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NR1: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else{
                            if (getCvc(c) == 0){
                                if (getCvn(c) == 0){
                                    int r =  rand() % 2;
                                    if (r){
                                        giveTipN(getCards(jog), getCnum(c));
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = (char)getCnum(c) + 48;
                                        printf("NR: %d", (char)getCnum(c) + 48);
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                    else{
                                        giveTipC(getCards(jog), 'R');
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = 'R';
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                }
                                else{
                                    giveTipC(getCards(jog), 'R');
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = 'R';
                                    insertLog(log, aux);
                                    (*tips)--;
                                }
                                flag = 0;
                            }
                            else{
                                if (getCvn(c) == 0){
                                    giveTipN(getCards(jog), getCnum(c));
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = (char)getCnum(c) + 48;
                                    printf("NR: %d", (char)getCnum(c) + 48);
                                    insertLog(log, aux);
                                    flag = 0;
                                    (*tips)--;
                                }
                            }
                        }
                    }
                    break;
                }
                case 'W':{
                    if ((PCards[3] + 1 == getCnum(c)) && (getCvc(c) == 0 || getCvn(c) == 0)){
                        unica = cardsAlone(jog, getCnum(c), 'W');
                        if(unica == 3){
                            if (getCvc(c) == 1){
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                printf("NW3: %d", (char)getCnum(c) + 48);
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipC(getCards(jog), 'W');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'W';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 2){
                            if (getCvc(c) == 0){
                                giveTipC(getCards(jog), 'W');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'W';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 1){
                            if (getCvn(c) == 1){
                                giveTipC(getCards(jog), 'W');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'W';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else{
                            if (getCvc(c) == 0){
                                if (getCvn(c) == 0){
                                    int r =  rand() % 2;
                                    if (r){
                                        giveTipN(getCards(jog), getCnum(c));
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = (char)getCnum(c) + 48;
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                    else{
                                        giveTipC(getCards(jog), 'W');
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = 'W';
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                }
                                else{
                                    giveTipC(getCards(jog), 'W');
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = 'W';
                                    insertLog(log, aux);
                                    (*tips)--;
                                }
                                flag = 0;
                            }
                            else{
                                if (getCvn(c) == 0){
                                    giveTipN(getCards(jog), getCnum(c));
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = (char)getCnum(c) + 48;
                                    insertLog(log, aux);
                                    flag = 0;
                                    (*tips)--;
                                }
                            }
                        }
                    }
                    break;
                }
                case 'Y':{
                    if ((PCards[4] + 1 == getCnum(c)) && (getCvc(c) == 0 || getCvn(c) == 0)){
                        unica = cardsAlone(jog, getCnum(c), 'Y');
                        if(unica == 3){
                            if (getCvc(c) == 1){
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipC(getCards(jog), 'Y');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'Y';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 2){
                            if (getCvc(c) == 0){
                                giveTipC(getCards(jog), 'Y');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'Y';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else if (unica == 1){
                            if (getCvn(c) == 1){
                                giveTipC(getCards(jog), 'Y');
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = 'Y';
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            else{
                                giveTipN(getCards(jog), getCnum(c));
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-D-");
                                aux[4] = (char)getCnum(c) + 48;
                                insertLog(log, aux);
                                (*tips)--;
                            }
                            flag = 0;
                        }
                        else{
                            if (getCvc(c) == 0){
                                if (getCvn(c) == 0){
                                    int r =  rand() % 2;
                                    if (r){
                                        giveTipN(getCards(jog), getCnum(c));
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = (char)getCnum(c) + 48;
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                    else{
                                        giveTipC(getCards(jog), 'Y');
                                        memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                        aux[0] = 'C';
                                        strcat(aux, "-D-");
                                        aux[4] = 'Y';
                                        insertLog(log, aux);
                                        (*tips)--;
                                    }
                                }
                                else{
                                    giveTipC(getCards(jog), 'Y');
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = 'Y';
                                    insertLog(log, aux);
                                    (*tips)--;
                                }
                                flag = 0;
                            }
                            else{
                                if (getCvn(c) == 0){
                                    giveTipN(getCards(jog), getCnum(c));
                                    memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                    aux[0] = 'C';
                                    strcat(aux, "-D-");
                                    aux[4] = (char)getCnum(c) + 48;
                                    insertLog(log, aux);
                                    flag = 0;
                                    (*tips)--;
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    c = NULL;
    
    if (flag){
        int lPos = getLowerCard(jog);
        if (lPos != -1){
            c = getCard(jog, lPos);
            if (c != NULL){
                giveTipN(getCards(jog), getCnum(c));
                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                aux[0] = 'C';
                strcat(aux, "-D-");
                aux[4] = (char)getCnum(c) + 48;
                insertLog(log, aux);
                (*tips)--;
            }
        }
        else{
            int vColors[5] = {0, 0, 0, 0, 0};
            for (i = 0; i < getNCP(jog); i++){
                c = getCard(jog, i);
                if (c != NULL){
                    if (getCvc(c) == 1){
                        switch (getCc(c)){
                            case 'B':{
                                vColors[0] = 1;
                                break;
                            }
                            case 'G':{
                                vColors[1] = 1;
                                break;
                            }
                            case 'R':{
                                vColors[2] = 1;
                                break;
                            }
                            case 'W':{
                                vColors[3] = 1;
                                break;
                            }
                            case 'Y':{
                                vColors[4] = 1;
                                break;
                            }
                        }
                    }
                }
            }

            if (vColors[0] == 0){
                giveTipC(getCards(jog), 'B');
                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                aux[0] = 'C';
                strcat(aux, "-D-");
                aux[4] = 'B';
                insertLog(log, aux);
                (*tips)--;
            }
            else if (vColors[1] == 0){
                giveTipC(getCards(jog), 'G');
                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                aux[0] = 'C';
                strcat(aux, "-D-");
                aux[4] = 'G';
                insertLog(log, aux);
                (*tips)--;
            }
            else if (vColors[2] == 0){
                giveTipC(getCards(jog), 'R');
                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                aux[0] = 'C';
                strcat(aux, "-D-");
                aux[4] = 'R';
                insertLog(log, aux);
                (*tips)--;
            }
            else if (vColors[3] == 0){
                giveTipC(getCards(jog), 'W');
                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                aux[0] = 'C';
                strcat(aux, "-D-");
                aux[4] = 'W';
                insertLog(log, aux);
                (*tips)--;
            }
            else if (vColors[4] == 0){
                giveTipC(getCards(jog), 'Y');
                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                aux[0] = 'C';
                strcat(aux, "-D-");
                aux[4] = 'Y';
                insertLog(log, aux);
                (*tips)--;
            }
        }
    }
}

//Função que faz a AI jogar
void PlayAI(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, Log log[], int lives, int *tips, int *nc, int *nt, int *np){
    Card RCards[5];
    int infoCartas = checkInfo(ai, RCards);
    int infoJog = checkInfoJog(jog);
    int posCarta = 0;
    if (infoCartas){
        //verificar se tem cartas jogaveis
        if ((*tips) > 0){
            darDica(deckM, trash, pi, jog, log, lives, tips, (*nc), (*nt), (*np));
        }
        else{//descartar
            //descartar a carta com maior conhecimento se possivel
            //senão descartar uma carta com uma dica
            //senão descartar uma carta aleatoria
        }
    }
    else{
        if((*tips) > 0){
            darDica(deckM, trash, pi, jog, log, lives, tips, (*nc), (*nt), (*np));
        }
        else{
            posCarta = rand() % 5;
            gototrash(trash, getCard(ai, posCarta), posCarta);
            lessCardsP(ai);
            if ((*nc) > 0){
                pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                plusCardsP(ai);
            }
            if(getNCP(ai) < 5){
                pushToLeft(ai);
            }
            (*tips)++;
        }
    }
    
}