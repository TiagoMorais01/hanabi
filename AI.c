#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Card.h"
#include "player.h"
#include "Log.h"
#include "AI.h"

//vê se o ai tem alguma informação das suas cartas
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

//funcção para dar uma dica
void darDica(Deck deckM, Deck trash, Pilha pi, Player jog){

}

//Função que faz a AI jogar
void PlayAI(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, Log log[], int lives, int *tips, int *nc, int *nt, int *np){
    Card RCards[5];
    int infoCartas = checkInfo(ai, RCards);
    int infoJog = checkInfoJog(jog);
    int posCarta = 0;
    if (infoCartas){
        //ver a jogado do Jog se foi uma jogada direta ou indireta
        if ((*tips) < 8){//jogar, dar dica ou descartar
            
        }
        else{
            if (infoJog){
                /* code */
            }
            else{
                //ver se tenho algum 5 e se tem dicas. Se não tiver dicas jogar o 5 senão dar uma dica ao Jog
            }
            /*
            jogar
            ou
            dar dica
            */
        }
        
    }
    else{
        if((*tips) > 0){
            darDica(deckM, trash, pi, jog);
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