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
        system("clear");
    #endif
    createDeck(deck);
    dealCards(jog, ai, deck, &nc);
    ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
    time_t t;
    srand((unsigned)time(&t));
    //escolhe a sorte qual jogardor vai começar
    int play = rand() % 2;
    play = 1;
    char mov[3];
    char x[3];
    int r = 1;
    while (r && lives != 0 && (contC(jog) != 0 || contC(ai) != 0)){
        if (play){
            gotoxy(0, 18);
            printf("                                                 ");
            gotoxy(0, 18);
            printf("Escolha a opção:");
            gotoxy(0, 19);
            printf("                                                 ");
            gotoxy(0, 19);
            printf("1 - Dar dica");
            gotoxy(0, 20);
            printf("                                                 ");
            gotoxy(0, 20);
            printf("2 - Jogar carta");
            gotoxy(0, 21);
            printf("                                                 ");
            gotoxy(0, 21);
            printf("3 - Descartar carta");
            gotoxy(0, 22);
            printf("                                                 ");
            gotoxy(0, 22);
            printf("0 - Sair");
            gotoxy(0, 23);
            printf("                                                 ");
            gotoxy(0, 23);
            printf("-> ");
            
            scanf("%s", mov);
            while (getchar()!='\n');
            if (strlen(mov) == 1){
                switch (mov[0]){
                    case '1':{
                        if (tips > 0){
                            gotoxy(0, 18);
                            printf("                                                 ");
                            gotoxy(0, 18);
                            printf("Deseja indicar uma cor ou um numero?");
                            gotoxy(0, 19);
                            printf("                                                 ");
                            gotoxy(0, 19);
                            printf("1 - Numero");
                            gotoxy(0, 20);
                            printf("                                                 ");
                            gotoxy(0, 20);
                            printf("2 - Cor");
                            gotoxy(0, 21);
                            printf("                                                 ");
                            gotoxy(0, 21);
                            printf("0 - Voltar para tras");
                            gotoxy(0, 22);
                            printf("                                                 ");
                            gotoxy(0, 22);
                            printf("-> ");
                            gotoxy(0, 23);
                            printf("                                                 ");
                            gotoxy(0, 24);
                            printf("                                                                                                  ");
                            
                            gotoxy(4, 22);
                            scanf("%s", x);
                            while (getchar()!='\n');
                            while ((strlen(x) > 1) || (x[0] < '0' || x[0] > '2')){
                                gotoxy(0, 18);
                                printf("                                                 ");
                                gotoxy(0, 18);
                                printf("Esse valor nao existe!!!");
                                gotoxy(0, 19);
                                printf("                                                 ");
                                gotoxy(0, 19);
                                printf("Deseja indicar uma cor ou um numero?");
                                gotoxy(0, 20);
                                printf("                                                 ");
                                gotoxy(0, 20);
                                printf("1 - Numero");
                                gotoxy(0, 21);
                                printf("                                                 ");
                                gotoxy(0, 21);
                                printf("2 - Cor");
                                gotoxy(0, 22);
                                printf("                                                 ");
                                gotoxy(0, 22);
                                printf("0 - Voltar para tras");
                                gotoxy(0, 23);
                                printf("                                                 ");
                                gotoxy(0, 23);
                                printf("-> ");
                                scanf("%s", x);
                                while (getchar()!='\n');
                            }

                            if(strlen(x) == 1){
                                if (x[0] == '1'){
                                    if(selNum(ai, play))
                                        tips--;
                                    ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
                                }
                                else if (x[0] == '2'){
                                    if(selCor(ai, play))
                                        tips--;
                                    ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
                                }
                            }
                        }
                        else{
                            gotoxy(0, 24);
                            printf("                                                                                                  ");
                            gotoxy(0, 24);
                            printf("Você não tem dicas para dar!!!");
                        }
                        break;
                    }
                    case '2':{
                        //do some code
                        ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
                        break;
                    }
                    case '3':{
                        if(tips < 8){
                            gotoxy(0, 18);
                            printf("                                                 ");
                            gotoxy(0, 18);
                            printf("Qual e a carta que deseja descartar?(1 - 5)");
                            gotoxy(0, 19);
                            printf("                                                 ");
                            gotoxy(0, 19);
                            printf("0 - Voltar para o menu");
                            gotoxy(0, 20);
                            printf("                                                 ");
                            gotoxy(0, 20);
                            printf("-> ");
                            gotoxy(0, 21);
                            printf("                                                 ");
                            gotoxy(0, 22);
                            printf("                                                 ");
                            gotoxy(0, 23);
                            printf("                                                 ");
                            gotoxy(0, 24);
                            printf("                                                                                                  ");
                            gotoxy(4, 20);
                            scanf("%s", x);
                            while ((strlen(x) > 1) || (x[0] < '0' || x[0] > '5')){
                                gotoxy(0, 18);
                                printf("                                                 ");
                                gotoxy(0, 18);
                                printf("A carta que escolheu não existe!!!!");
                                gotoxy(0, 19);
                                printf("                                                 ");
                                gotoxy(0, 19);
                                printf("Qual e a carta que deseja descartar?(1 - 5)");
                                gotoxy(0, 20);
                                printf("                                                 ");
                                gotoxy(0, 20);
                                printf("0 - Voltar para o menu");
                                gotoxy(0, 21);
                                printf("                                                 ");
                                gotoxy(0, 21);
                                printf("-> ");
                                gotoxy(0, 22);
                                printf("                                                 ");
                                gotoxy(0, 23);
                                printf("                                                 ");
                                gotoxy(4, 21);
                                scanf("%s", x);
                            }

                            if ((x[0] != '0')){
                                gototrash(trash, grCard(jog, ((int)(x[0]))-49), nt++);
                                if (nc > 0){
                                    pickCard(jog, grCa(deck, nc--));
                                }
                                tips++;
                                play = 0;
                                ShowCardAI(deck, trash, ai, jog, pi, lives, tips, nc, nt, np);
                            }
                        }
                        else{
                            gotoxy(0, 24);
                            printf("                                                                                                  ");
                            gotoxy(0, 24);
                            printf("Você não pode descartar cartas!!! Tem de ter menos de 8 dicas para poder descartar uma carta.");
                        }
                        break;
                    }
                    case '0':
                        r = 0;
                        break;
                    default:
                        gotoxy(0, 24);
                        printf("                                                                                                  ");
                        gotoxy(0, 24);
                        printf("A opção que escolheu não existe!!!");
                        break;
                }
            }
            else{
                gotoxy(0, 24);
                printf("                                                                                                  ");
                gotoxy(0, 24);
                printf("A opção que escolheu não existe!!!");
            }
        }
        else{
            play = 1;
        }
    }
    return;
}

void tutorial(){
    FILE *regras;
    if(!(regras = fopen("Regras.txt","r")))
        printf("Erro ao abrir o ficheiro");
    else{
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            system("cls");
        #else
            system("clear");
        #endif
        char *ch = malloc(200);
        size_t t = 200;
        while(getline(&ch, &t, regras) != -1){
            printf("%s",ch);
        }
        printf("\n\nInsira qualquer tecla para continuar...");
        while(getchar() != '\n');
    }
    return;
}

void credits(int w, int h){
    gotoxy((w/2) - 20,1);
    printf("                         _  ___            Produzido por:\n");
    gotoxy((w/2) - 20,2);
    printf("%lc__%lc  %lc__%lc  %lc%lc %lc  %lc__%lc  |_)  %lc              Tiago Morais 71395\n", 0x2502, 0x2502,  0x2571, 0x2572, 0x2502, 0x2572, 0x2502, 0x2571, 0x2572, 0x2502);
    gotoxy((w/2) - 20,3);
    printf("%lc  %lc %lc    %lc %lc %lc%lc %lc    %lc |_) _%lc_             Tomas Silva 70680\n", 0x2502, 0x2502, 0x2571, 0x2572, 0x2502, 0x2572, 0x2502, 0x2571, 0x2572, 0x2502);
    return;
}

void main(){

    char no[20];
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

    int run = 1;
    char c;

    setlocale(LC_ALL, "");

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
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
        gotoxy((w/2) - 13,4);
        printf("            ");
        gotoxy((w/2) - 13,4);
        printf("1 - New Game");
        gotoxy((w/2) - 13,5);
        printf("            ");
        gotoxy((w/2) - 13,5);
        printf("2 - Tutorial");
        gotoxy((w/2) - 13,6);
        printf("            ");
        gotoxy((w/2) - 13,6);
        printf("0 - Sair");
        gotoxy((w/2) - 13,7);
        printf("            ");
        gotoxy((w/2) - 13,7);
        printf("-> ");
        scanf("%c", &c);
        while (getchar()!='\n');
        switch (c){
            case '1':
                gotoxy((w/2) - 25,4);
                printf("Digite o seu nome(no maximo 16 caracteres)\n");
                gotoxy((w/2) - 13,5);
                printf("            ");
                gotoxy((w/2) - 13,6);
                printf("            ");
                gotoxy((w/2) - 13,7);
                printf("            ");
                gotoxy((w/2) - 13,8);
                printf("                             ");
                gotoxy((w/2) - 13,5);
                printf("->");
                scanf("%[^\n]", no);//fazer while para não aceitar um nome vazio
                while (getchar()!='\n');
                int s = 0;
                while (strlen(no) > 16){
                    gotoxy((w/2) - 25,4);
                    printf("Digite o seu nome(no maximo 16 caracteres)\n");
                    gotoxy((w/2) - 13,5);
                    for (s = 0; s < strlen(no); s++){
                        printf(" ");
                        gotoxy((w/2) - 13 + s,5);
                    }
                    printf("            ");
                    gotoxy((w/2) - 13,6);
                    printf("            ");
                    gotoxy((w/2) - 25,6);
                    printf("O nome deve conter no maximo 5 caracteres\n");
                    gotoxy((w/2) - 13,7);
                    printf("            ");
                    gotoxy((w/2) - 13,8);
                    printf("                             ");
                    gotoxy((w/2) - 13,5);
                    printf("->");
                    scanf("%[^\n]", no);
                    while (getchar()!='\n');
                }
                
                ai = newPlayer("Gervásio");//Cria a AI
                jog = newPlayer(no);//Cria a estrutura jogador
                deck = newDeck();//Cria um array deck
                trash = newDeck();//Cria uma array trash
                pilha = newPilha();//Cria um array para armazenar as cartas jogadas para a mesa
                newGame(deck, trash, ai, jog, pilha, lives, tips, nc, nt, np);//Função do jogo
                /* Apaga as variaveis da memoria */
                free(deck);
                free(trash);
                freeP(ai);
                freeP(jog);
                freePi(pilha);
                /* --------------------------- */
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                    system("cls");
                #else
                    system("clear");
                #endif
                break;
            case '2':
                tutorial();
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                    system("cls");
                #else
                    system("clear");
                #endif
                break;
            case '0':
                run = 0;
                break;
            default:
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                    system("cls");
                #else
                    system("clear");
                #endif
                gotoxy((w/2) - 13,8);
                printf("Nao existe essa opcao!!!\n");
        }
    }
}