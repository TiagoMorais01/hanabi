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
void PlayAI(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, Log log[], int *lives, int *tips, int *nc, int *nt, int *np){
    Card RCards[5];
    int infoCartas = checkInfo(ai, RCards);
    int infoJog = checkInfoJog(jog);
    int posCarta = 0;
    char aux[10];
    Card c = NULL;
    if (infoCartas){
        int i = 0;
        int posRC = 0;
        Card auxC = NULL;
        int flag = 1;
        int PCards[5] = {0, 0, 0, 0, 0};
        getTopCpilha(pi, PCards, (*np));
        //Saber qual e o numero base da pilha(menor carta igual em todas as cores na pilha)
        int base = 0;
        if (PCards[0] >= 4 && PCards[1] >= 4 && PCards[2] >= 4 && PCards[3] >= 4 && PCards[4] >= 4){
            base = 4;
        }
        else if (PCards[0] >= 3 && PCards[1] >= 3 && PCards[2] >= 3 && PCards[3] >= 3 && PCards[4] >= 3){
            base = 3;
        }
        else if (PCards[0] >= 2 && PCards[1] >= 2 && PCards[2] >= 2 && PCards[3] >= 2 && PCards[4] >= 2){
            base = 2;
        }
        else if (PCards[0] >= 1 && PCards[1] >= 1 && PCards[2] >= 1 && PCards[3] >= 1 && PCards[4] >= 1){
            base = 1;
        }
        else{
            base = 0;
        }
        
        //verificar se tem cartas jogaveis
        for (i = 0; i < infoCartas && flag; i++){
            c = getCard(jog, i);
            if (c != NULL){
                switch (getCc(c)){
                    case 'B':{
                        posRC = 0;
                        break;
                    }
                    case 'G':{
                        posRC = 1;
                        break;
                    }
                    case 'R':{
                        posRC = 2;
                    }
                    case 'W':{
                        posRC = 3;
                    }
                    case 'Y':{
                        posRC = 4;
                    }
                }
                if (getCvc(c) == 1){
                    if (getCvn(c) == 1){
                        if (PCards[posRC] + 1 == getCnum(c)){
                            if(playCard(pi, ai, getCpos(c), (*np))){
                                auxC = grCard(ai, getCpos(c));
                                setCpilha(pi, auxC, (*np)++);
                                setCpos(getCpilha(pi, ((*np) - 1)), ((*np) - 1));
                                if (getCnum(getCpilha(pi, ((*np) - 1))) == 5 && (*tips) < 8)
                                    (*tips)++;
                                lessCardsP(ai);
                                if ((*nc) > 0){
                                    pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                                    plusCardsP(ai);
                                }
                                if(getNCP(ai) < 5){
                                    pushToLeft(ai);
                                }
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-J-");
                                aux[4] = (char) getCnum(auxC) + 48;
                                aux[5] = getCc(auxC);
                                insertLog(log, aux);
                                auxC = NULL;
                                sortPilha(pi, 0, np - 1);//Função para ordenar a pilha
                            }
                            else{
                                auxC = grCard(ai, getCpos(c));
                                gototrash(trash, auxC, (*nt)++);//Função que passa a carta para o descarte
                                lessCardsP(ai);
                                if ((*nc) > 0){
                                    pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                                    plusCardsP(ai);
                                }
                                if(getNCP(ai) < 5){
                                    pushToLeft(ai);
                                }
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-J-T-");
                                aux[6] = (char) getCnum(auxC) + 48;
                                aux[7] = getCc(auxC);
                                insertLog(log, aux);
                                auxC = NULL;
                                sortTrash(trash, 0, (*nt) - 1);
                                (*lives)--;
                            }
                            flag = 0;
                        }
                        else if(base > getCnum(c) || PCards[posRC] + 1 > getCnum(c)){
                            if ((*tips) < 8){
                                auxC = grCard(ai, getCpos(c));
                                gototrash(trash, auxC, (*nt)++);//Função que passa a carta para o descarte
                                lessCardsP(ai);
                                if ((*nc) > 0){
                                    pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                                    plusCardsP(ai);
                                }
                                if(getNCP(ai) < 5){
                                    pushToLeft(ai);
                                }
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-T-");
                                aux[4] = (char) getCnum(auxC) + 48;
                                aux[5] = getCc(auxC);
                                insertLog(log, aux);
                                auxC = NULL;
                                sortTrash(trash, 0, (*nt) - 1);
                                flag = 0;
                            }
                        }
                    }
                    else{
                        if ((*tips) < 8){
                            if (PCards[posRC] == 5){
                                auxC = grCard(ai, getCpos(c));
                                gototrash(trash, auxC, (*nt)++);//Função que passa a carta para o descarte
                                lessCardsP(ai);
                                if ((*nc) > 0){
                                    pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                                    plusCardsP(ai);
                                }
                                if(getNCP(ai) < 5){
                                    pushToLeft(ai);
                                }
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-T-");
                                aux[4] = (char) getCnum(auxC) + 48;
                                aux[5] = getCc(auxC);
                                insertLog(log, aux);
                                auxC = NULL;
                                sortTrash(trash, 0, (*nt) - 1);
                            }
                        }
                    }
                }
                else{
                    if (getCvn(c) == 1){
                        if(base > getCnum(c)){
                            if ((*tips) < 8){
                                auxC = grCard(ai, getCpos(c));
                                gototrash(trash, auxC, (*nt)++);//Função que passa a carta para o descarte
                                lessCardsP(ai);
                                if ((*nc) > 0){
                                    pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                                    plusCardsP(ai);
                                }
                                if(getNCP(ai) < 5){
                                    pushToLeft(ai);
                                }
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'C';
                                strcat(aux, "-T-");
                                aux[4] = (char) getCnum(auxC) + 48;
                                aux[5] = getCc(auxC);
                                insertLog(log, aux);
                                auxC = NULL;
                                sortTrash(trash, 0, (*nt) - 1);
                                flag = 0;
                            }
                        }
                    }
                }
            }
        }
        
        if(flag){
            if ((*tips) > 0){
                darDica(deckM, trash, pi, jog, log, lives, tips, (*nc), (*nt), (*np));
            }
            else{
                posCarta = rand() % 5;
                auxC = grCard(ai, posCarta);
                gototrash(trash, auxC, (*nt)++);//Função que passa a carta para o descarte
                lessCardsP(ai);
                if ((*nc) > 0){
                    pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                    plusCardsP(ai);
                }
                if(getNCP(ai) < 5){
                    pushToLeft(ai);
                }
                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                aux[0] = 'C';
                strcat(aux, "-T-");
                aux[4] = (char) getCnum(auxC) + 48;
                aux[5] = getCc(auxC);
                insertLog(log, aux);
                auxC = NULL;
                sortTrash(trash, 0, (*nt) - 1);
            }
        }
    }
    else{
        if((*tips) > 0){
            darDica(deckM, trash, pi, jog, log, lives, tips, (*nc), (*nt), (*np));
        }
        else{
            posCarta = rand() % 5;
            c = getCard(ai, posCarta);
            gototrash(trash, c, posCarta);
            lessCardsP(ai);
            if ((*nc) > 0){
                pickCard(ai, grCa(deckM, (*nc)--));//Função que pega uma carta do deck e atribui ao jogador
                plusCardsP(ai);
            }
            if(getNCP(ai) < 5){
                pushToLeft(ai);
            }
            memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
            aux[0] = 'C';
            strcat(aux, "-T-");
            aux[4] = (char) getCnum(c) + 48;
            aux[5] = getCc(c);
            insertLog(log, aux);
            c = NULL;
            sortTrash(trash, 0, (*nt) - 1);
            (*tips)++;
        }
    }
}