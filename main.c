#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
#define gotoxy(x,y) printf("\033[%d;%dH", (y) , (x))

void newGame(Deck deck, Deck trash, Player ai, Player jog, Pilha pi, int lives, int tips, int nc, int nt, int np){
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
    srand((unsigned)time(&t));
    int play = rand() % 2;
    play = 1;
    int mov = 0;
    int r = 1;
    while (r && lives != 0 && (contC(jog) != 0 || contC(ai) != 0)){
        if (play)
        {
            printf("Escolha a opção:\n1 - Dar dica\n2 - Jogar carta\n3 - Descartar carta\n0 - Sair\n-> ");
            scanf("%d", &mov);
            switch (mov)
            {
            case 1:
                printf("Deseja indicar uma cor ou um numero?\n1 - Numero\n2 - Cor\n0 - Voltar para tras\n-> ");
                scanf("%d", &mov);
                while (mov >= 0 && mov <= 2)
                {
                    if (mov == 1)
                    {
                        selNum(ai, play);
                        break;
                    }
                    else if (mov == 2)
                    {
                        selCor(ai, play);
                        break;
                    }
                    else if (mov == 0)
                    {
                        break;
                    }
                    else
                    {
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
        else
        {
            play = 1;
        }
    }
    return;
}

void tutorial(){
    
    return;
}

void credits(int w, int h){
    setlocale(LC_ALL, "");
    gotoxy((w/2) - 20,1);
    printf("                         _  ___            Produzido por:\n");
    gotoxy((w/2) - 20,2);
    printf("%lc__%lc  %lc__%lc  %lc%lc %lc  %lc__%lc  |_)  %lc              Tiago Morais 71395\n", 0x2502, 0x2502,  0x2571, 0x2572, 0x2502, 0x2572, 0x2502, 0x2571, 0x2572, 0x2502);
    gotoxy((w/2) - 20,3);
    printf("%lc  %lc %lc    %lc %lc %lc%lc %lc    %lc |_) _%lc_             Tomas Silva 70680\n", 0x2502, 0x2502, 0x2571, 0x2572, 0x2502, 0x2572, 0x2502, 0x2571, 0x2572, 0x2502);
    return;
}

void main(){

    char no[128];
    Deck deck = NULL;
    Deck trash = NULL;
    Player ai = NULL;
    Player jog = NULL;
    Pilha pilha = NULL;
    int lives = 3;
    int tips = 8;
    int nc = 50;
    int nt = 0;
    int np = 0;
    int h, w;

    int c, d, run = 1;

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        //system("cls");
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        row = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        w = csbi.dwSize.X;
    //senao e linux/mac
    #else
        system("clear");
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        w = size.ws_col;
        h = size.ws_row;
    #endif

    while (run){
        credits(w, h);
        printf("\n\n");
        gotoxy((w/2) - 13,4);
        printf("1 - New Game");
        printf("\n");
        gotoxy((w/2) - 13,5);
        printf("2 - Tutorial");
        printf("\n");
        gotoxy((w/2) - 13,6);
        printf("0 - Sair");
        printf("\n");
        gotoxy((w/2) - 13,7);
        printf("-> ");
        scanf("%d", &c);
        getchar();
        switch (c)
        {
        case 1:
            gotoxy((w/2) - 25,4);
            printf("Digite o seu nome(no maximo 100 caracteres)\n");
            gotoxy((w/2) - 13,5);
            printf("            ");
            gotoxy((w/2) - 13,6);
            printf("           ");
            gotoxy((w/2) - 13,7);
            printf("           ");
            gotoxy((w/2) - 13,5);
            printf("->");
            scanf("%[^\n]", no);
            ai = newPlayer("Gervásio");
            jog = newPlayer(no);
            deck = newDeck();
            trash = newDeck();
            pilha = newPilha();
            newGame(deck, trash, ai, jog, pilha, lives, tips, nc, nt, np);
            free(deck);
            free(trash);
            freeP(ai);
            freeP(jog);
            freePi(pilha);
            system("clear");
            break;
        case 2:
            tutorial();
            break;
        case 0:
            run = 0;
            break;
        default:
            system("clear");
            printf("Nao existe essa opcao!!!\n");
        }
    }
}
