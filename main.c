#include <stdio.h>
#include <stdlib.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h>
#endif
#include <string.h>
#include <time.h>
#include "Card.h"
#include "player.h"
#include "ShowCard.h"

void newGame(Deck deck, Deck trash, Player ai, Player jog, Card *pi, int lives, int tips, int nc, int nt, int np){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
    #else
        //system("clear");
    #endif
    createDeck(deck);
    dealCards(jog, ai, deck, &nc);
    printCp(jog);
    printCp(ai);
    ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
    time_t t;
    srand((unsigned) time(&t));
    int play = rand() % 2;
    play = 1;
    int mov = 0;
    int r = 1;
    while(r && lives != 0 && (contC(jog) != 0 || contC(ai) != 0)){
        if(play){
            printf("Escolha a opção:\n1 - Dar dica\n2 - Jogar carta\n3 - Descartar carta\n0 - Sair\n-> ");
            scanf("%d", &mov);
            switch (mov){
                case 1:
                    printf("Deseja indicar uma cor ou um numero?\n1 - Numero\n2 - Cor\n0 - Voltar para tras\n-> ");
                    scanf("%d", &mov);
                    while (mov >= 0 && mov <= 2){
                        if(mov == 1){
                            selNum(ai, play);
                            break;
                        }
                        else if(mov == 2){
                            selCor(ai, play);
                            break;
                        }
                        else if(mov == 0){
                            break;
                        }
                        else{
                            printf("Esse valor nao existe!!!");
                        }
                        printf("Deseja indicar uma cor ou um numero?\n1 - Numero\n2 - Cor\n0 - Voltar para tras\n-> ");
                        scanf("%d", &mov);
                    }
                    ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
                    break;
                case 2:
                    //do some code
                    ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
                    break;
                case 3:
                    //do some code
                    ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
                    break;
                case 0:
                    r = 0;
                    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                        //system("cls");
                    //senao e linux/mac
                    #else
                        //system("clear");
                    #endif
                    break;
                default:
                    break;
            }
            play = 0;
        }
        else{
            play = 1;
        }
    }
    return;
}

void tutorial(){
    return;
}

void credits(){
    return;
}

void main(){
    
    char no[128];
    Deck deck = NULL;
    Deck trash = NULL;
    Player ai = NULL;
    Player jog = NULL;
    Card pilha[25];
    int lives = 3;
    int tips = 8;
    int nc = 50;
    int nt = 0;
    int np = 0;

    int c, d, run = 1;

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
    #else
        //system("clear");
    #endif
    
    while(run){
        printf("1 - New Game\n2 - Tutorial\n3 - Credits\n0 - Sair\n-> ");
        scanf("%d", &c);
        getchar();
        switch(c){
            case 1:
                printf("Digite o seu nome(no maximo 100 caracteres)\n->");
                scanf("%[^\n]", no);
                ai = newPlayer("Gervásio");
                jog = newPlayer(no);
                deck = newDeck();
                trash = newDeck();
                newPilha(pilha);
                newGame(deck, trash, ai, jog, pilha, lives, tips, nc, nt, np);
                free(deck);
                free(trash);
                freeP(ai);
                freeP(jog);
                freePi(pilha);
                break;
            case 2:
                tutorial();
                break;
            case 3:
                credits();
                break;
            case 0:
                run = 0;
                break;
            default: printf("Nao existe essa opcao!!!\n");
        }
    }
}
