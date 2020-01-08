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
#include "Log.h"
#include "ShowCard.h"
#include "AI.h"
#include "Save.h"
#define gotoxy(x,y) printf("\033[%d;%dH", (y) , (x))

//Função main do jogo onde ocorre a gestão do jogo
void init(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, Log log[], int lives, int tips, int nc, int nt, int np, int play, int ultimasJ){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
    #else
        system("clear");
    #endif
    ShowCardAI(deckM, trash, ai, jog, pi, log, lives, tips, nc, nt, np);//Função que imprime a mesa do jogo
    char mov;
    char x;
    int r = 1;
    int selnum = 0;
    int selcor = 0;
    char aux[10];
    Card auxC = NULL;
    if (ultimasJ){
        r = 0;
    }
    else{
        r = 1;
    }
    //Main loop que faz decorrer o jogo
    while ((r || ultimasJ) && lives != 0){
        
        if ((nc == 0 && r == 1) || (nc == 0 && r == 0)){
            if (r != 0){    
                if (getExp(log, 0)[0] == 'C'){
                    ultimasJ = play ? 3 : 2;
                }
                else if(getExp(log, 0)[0] == 'P'){
                    ultimasJ = play ? 2 : 3;
                }
                r = 0;
            }
            else{
                (ultimasJ > 0) ? ultimasJ-- : 0;
            }
        }
        
        if (play){//Vez do jogador
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
            mov = getchar();
            while (getchar() != '\n');
            
            switch (mov){
                case '1':{//Dar dica
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
                        x = getchar();
                        while (getchar() != '\n');
                        while (x < '0' || x > '2'){
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
                            x = getchar();
                            while (getchar()!='\n');
                        }

                        if (x == '1'){//Dá a dica de um numero
                            selnum = 0;
                            if((selnum = selNum(ai, play))){
                                tips--;
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'P';
                                strcat(aux, "-D-");
                                aux[4] = (char)selnum + 48;
                                insertLog(log, aux);
                                play = 0;
                            }
                            selnum = 0;
                            ShowCardAI(deckM, trash, ai, jog, pi, log, lives, tips, nc, nt, np);
                        }
                        else if (x == '2'){
                            selcor = 0;
                            if((selcor = selCor(ai, play))){//Dá a dica de uma cor
                                tips--;
                                memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                                aux[0] = 'P';
                                strcat(aux, "-D-");
                                aux[4] = (char)selcor + 48;
                                insertLog(log, aux);
                                play = 0;
                            }
                            selcor = 0;
                            ShowCardAI(deckM, trash, ai, jog, pi, log, lives, tips, nc, nt, np);
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
                case '2':{//Jogar uma carta
                    gotoxy(0, 18);
                    printf("                                                 ");
                    gotoxy(0, 18);
                    printf("Qual e a carta que deseja jogar?(1 - %d)", getNCP(jog));
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
                    x = getchar();
                    while (getchar()!='\n');
                    while (x < '0' || x > (char) 48 + getNCP(jog)){
                        gotoxy(0, 18);
                        printf("                                                 ");
                        gotoxy(0, 18);
                        printf("A carta que escolheu não existe!!!!");
                        gotoxy(0, 19);
                        printf("                                                 ");
                        gotoxy(0, 19);
                        printf("Qual e a carta que deseja jogar?(1 - %d)", getNCP(jog));
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
                        x = getchar();
                        while (getchar()!='\n');
                    }
                    if (x != '0'){
                        if(playCard(pi, jog, ((int)x)-49, np)){
                            auxC = grCard(jog, ((int)x)-49);
                            setCpilha(pi, auxC, np++);
                            setCpos(getCpilha(pi, (np - 1)), (np - 1));
                            if (getCnum(getCpilha(pi, (np - 1))) == 5 && tips < 8)
                                tips++;
                            lessCardsP(jog);
                            if (nc > 0){
                                pickCard(jog, grCa(deckM, nc--));//Função que pega uma carta do deck e atribui ao jogador
                                plusCardsP(jog);
                            }
                            if(getNCP(jog) < 5){
                                pushToLeft(jog);
                            }
                            memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                            aux[0] = 'P';
                            strcat(aux, "-J-");
                            aux[4] = (char) getCnum(auxC) + 48;
                            aux[5] = getCc(auxC);
                            insertLog(log, aux);
                            auxC = NULL;
                            play = 0;//Passa a vez para a AI
                            sortPilha(pi, 0, np - 1);//Função para ordenar a pilha
                        }
                        else{
                            auxC = grCard(jog, ((int)x)-49);
                            gototrash(trash, auxC, nt++);//Função que passa a carta para o descarte
                            lessCardsP(jog);
                            if (nc > 0){
                                pickCard(jog, grCa(deckM, nc--));//Função que pega uma carta do deck e atribui ao jogador
                                plusCardsP(jog);
                            }
                            if(getNCP(jog) < 5){
                                pushToLeft(jog);
                            }
                            memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                            aux[0] = 'P';
                            strcat(aux, "-J-T-");
                            aux[6] = (char) getCnum(auxC) + 48;
                            aux[7] = getCc(auxC);
                            insertLog(log, aux);
                            auxC = NULL;
                            sortTrash(trash, 0, nt - 1);
                            lives--;
                            play = 0;//Passa a vez para a AI
                        }
                        ShowCardAI(deckM, trash, ai, jog, pi, log, lives, tips, nc, nt, np);
                    }
                    break;
                }
                case '3':{//Descartar uma carta
                    if(tips < 8){
                        gotoxy(0, 18);
                        printf("                                                 ");
                        gotoxy(0, 18);
                        printf("Qual e a carta que deseja descartar?(1 - %d)", getNCP(jog));
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
                        x = getchar();
                        while (getchar()!='\n');
                        while (x < '0' || x > (char) 48 + getNCP(jog)){
                            gotoxy(0, 18);
                            printf("                                                 ");
                            gotoxy(0, 18);
                            printf("A carta que escolheu não existe!!!!");
                            gotoxy(0, 19);
                            printf("                                                 ");
                            gotoxy(0, 19);
                            printf("Qual e a carta que deseja descartar?(1 - %d)", getNCP(jog));
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
                            x = getchar();
                            while (getchar()!='\n');
                        }

                        if ((x != '0')){
                            auxC = grCard(jog, ((int)x)-49);
                            gototrash(trash, auxC, nt++);//Função que passa a carta para o descarte
                            lessCardsP(jog);
                            if (nc > 0){
                                pickCard(jog, grCa(deckM, nc--));//Função que pega uma carta do deck e atribui ao jogador
                                plusCardsP(jog);
                            }
                            if(getNCP(jog) < 5){
                                pushToLeft(jog);
                            }
                            tips++;
                            memset(aux, '\0', 10);//Coloca '\0' da posição zero até 10 posições a frente
                            aux[0] = 'P';
                            strcat(aux, "-T-");
                            aux[4] = (char) getCnum(auxC) + 48;
                            aux[5] = getCc(auxC);
                            insertLog(log, aux);
                            auxC = NULL;
                            sortTrash(trash, 0, nt - 1);
                            play = 0;//Passa a vez para a AI
                            ShowCardAI(deckM, trash, ai, jog, pi, log, lives, tips, nc, nt, np);
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
                case '0'://Sai do jogo e volta para o menu inicial
                    gotoxy(0, 18);
                    printf("                                                 ");
                    gotoxy(0, 18);
                    printf("Deseja salvar a partida?");
                    gotoxy(0, 19);
                    printf("                                                 ");
                    gotoxy(0, 19);
                    printf("S - SIM");
                    gotoxy(0, 20);
                    printf("                                                 ");
                    gotoxy(0, 20);
                    printf("N - NÃO");
                    gotoxy(0, 21);
                    printf("                                                 ");
                    gotoxy(0, 21);
                    printf("0 - Voltar para o menu");
                    gotoxy(0, 22);
                    printf("                                                 ");
                    gotoxy(0, 22);
                    printf("-> ");
                    gotoxy(0, 23);
                    printf("                                                 ");
                    gotoxy(4, 22);
                    x = getchar();
                    while (getchar()!='\n');
                    while (x != 'S' && x != 's' && x != 'N' && x != 'n' && x != '0'){
                        gotoxy(0, 18);
                        printf("                                                 ");
                        gotoxy(0, 18);
                        printf("Essa opção não existe!!!!");
                        gotoxy(0, 19);
                        printf("                                                 ");
                        gotoxy(0, 19);
                        printf("Deseja salvar a partida?");
                        gotoxy(0, 20);
                        printf("                                                 ");
                        gotoxy(0, 20);
                        printf("S - SIM");
                        gotoxy(0, 21);
                        printf("                                                 ");
                        gotoxy(0, 21);
                        printf("N - NÃO");
                        gotoxy(0, 22);
                        printf("                                                 ");
                        gotoxy(0, 22);
                        printf("0 - Voltar para o menu");
                        gotoxy(0, 23);
                        printf("                                                 ");
                        gotoxy(0, 23);
                        printf("-> ");
                        gotoxy(4, 23);
                        x = getchar();
                        while (getchar()!='\n');
                    }

                    if (x == 'S' || x == 's'){
                        r = 0;
                        saveGame(deckM, trash, ai, jog, pi, lives, tips, nc, nt, np, ultimasJ);
                        exportLog(log);
                    }
                    else if (x == 'N' || x == 'n'){
                        r = 0;
                    }
                    
                    break;
                default:
                    gotoxy(0, 24);
                    printf("                                                                                                  ");
                    gotoxy(0, 24);
                    printf("A opção que escolheu não existe!!!");
                    break;
            }
        }
        else{//Vez da AI
            PlayAI(deckM, trash, ai, jog, pi, log, lives, &tips, &nc, &nt, &np);
            ShowCardAI(deckM, trash, ai, jog, pi, log, lives, tips, nc, nt, np);
            play = 1;
        }
    }

    if (r == 0 && ultimasJ == 0 && nc == 0){
        FILE* f;
        if ((f = fopen("save.ha", "r")) != NULL){
            //delete the file
            fclose(f);
        }
        if ((f = fopen("save.log", "r")) != NULL){
            //delete the file
            fclose(f);
        }

    }
    

    return;
}

//Função com as regras e como se joga
void tutorial(){
    FILE *regras;
    if(!(regras = (fopen("Regras.txt", "r"))))
        perror("Erro");
    else{
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            system("cls");
        #else
            system("clear");
        #endif
        char ch;
        while((ch = getc(regras)) != EOF){
            printf("%c",ch);
        }
        printf("\n\nInsira qualquer tecla para continuar...");
        while(getchar() != '\n');
    }
    return;
}

//Função para o creditos
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
    Deck deckM = NULL;
    Deck trash = NULL;
    Player ai = NULL;
    Player jog = NULL;
    Pilha pilha = NULL;
    Log *log = NULL;
    int lives = 0;
    int tips = 0;
    int nc = 0;
    int nt = 0;
    int np = 0;
    int play = 0;
	int h = 0;
	int w = 0;
    time_t t;
    int ultimasJ = 0;

    int run = 1;
    char c;

    setlocale(LC_ALL, "");

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int row = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
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
        printf("                             ");
        gotoxy((w/2) - 13,4);
        printf("1 - New Game");
        gotoxy((w/2) - 13,5);
        printf("                             ");
        gotoxy((w/2) - 13,5);
        printf("2 - Load Game");
        gotoxy((w/2) - 13,6);
        printf("                             ");
        gotoxy((w/2) - 13,6);
        printf("3 - Tutorial");
        gotoxy((w/2) - 13,7);
        printf("                             ");
        gotoxy((w/2) - 13,7);
        printf("0 - Sair");
        gotoxy((w/2) - 13,8);
        printf("                             ");
        gotoxy((w/2) - 13,8);
        printf("-> ");
        c = getchar();
        while (getchar()!='\n');
        switch (c){
            case '1':
                gotoxy((w/2) - 25,4);
                printf("Digite o seu nome(entre 3 a 16 caracteres)\n");
                gotoxy((w/2) - 13,5);
                printf("                             ");
                gotoxy((w/2) - 13,6);
                printf("                             ");
                gotoxy((w/2) - 13,7);
                printf("                             ");
                gotoxy((w/2) - 13,8);
                printf("                             ");
                gotoxy((w/2) - 13,5);
                printf("->");
                fscanf(stdin, "%s", no);
                while (getchar() != '\n');
                //Ver se o nome é maior que 16 caracteres
                int s = 0;
                while (strlen(no) < 3 || strlen(no) > 16){
                    gotoxy((w/2) - 25,4);
                    printf("Digite o seu nome(entre 3 a 16 caracteres)\n");
                    gotoxy((w/2) - 13,5);
                    for (s = 0; s < strlen(no); s++){
                        printf(" ");
                        gotoxy((w/2) - 13 + s,5);
                    }
                    printf("                             ");
                    gotoxy((w/2) - 13,6);
                    printf("                             ");
                    gotoxy((w/2) - 13,7);
                    printf("                             ");
                    gotoxy((w/2) - 13,8);
                    printf("                             ");
                    gotoxy((w/2) - 13,5);
                    printf("->");
                    fscanf(stdin, "%s", no);
                    while (getchar() != '\n');
                }
                ai = newPlayer("Gervásio");//Cria a AI
                jog = newPlayer(no);//Cria a estrutura jogador
                deckM = newDeck();//Inicia um array deck
                trash = newDeck();//Inicia um array trash
                pilha = newPilha();//Inicia um array para armazenar as cartas jogadas para a mesa
                log = newLog();//Inicia um array para armazenar as jogadas dos jogadores
                lives = 3;
                tips = 8;
                nc = 50;
                nt = 0;
                np = 0;
                ultimasJ = 0;
                srand((unsigned)time(&t));
                play = rand() % 2;//Escolhe a sorte qual jogardor vai começar
                createDeck(deckM);//Função que preenche o Deck
                dealCards(jog, ai, deckM, &nc);//Função que distribui as cartas pelos jogadores
                init(deckM, trash, ai, jog, pilha, log, lives, tips, nc, nt, np, play, ultimasJ);//Função do jogo
                /* Apaga as variaveis da memoria */
                lives = 3;
                tips = 8;
                nc = 50;
                nt = 0;
                np = 0;
                free(deckM);
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
                case '2':{
                    FILE *f, *f2;
                    if ((f = fopen("save.ha", "r")) != NULL && (f2 = fopen("save.log", "r")) != NULL){
                        ai = newPlayer("");//Cria a AI
                        jog = newPlayer("");//Cria a estrutura jogador
                        deckM = newDeck();//Inicia um array deck
                        trash = newDeck();//Inicia um array trash
                        pilha = newPilha();//Inicia um array para armazenar as cartas jogadas para a mesa
                        log = newLog();//Inicia um array para armazenar as jogadas dos jogadores
                        fclose(f);
                        fclose(f2);
                        loadGame(deckM, trash, ai, jog, pilha, &lives, &tips, &nc, &nt, &np, &ultimasJ);
                        loadLog(log);
                        play = 1;
                        init(deckM, trash, ai, jog, pilha, log, lives, tips, nc, nt, np, play, ultimasJ);
                        free(deckM);
                        free(trash);
                        freeP(ai);
                        freeP(jog);
                        freePi(pilha);
                        lives = 3;
                        tips = 8;
                        nc = 50;
                        nt = 0;
                        np = 0;
                        ultimasJ = 0;
                        /* ------------------------- */
                        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                            system("cls");
                        #else
                            system("clear");
                        #endif
                    }
                    else{
                        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                        system("cls");
                        #else
                            system("clear");
                        #endif
                        gotoxy((w/2) - 13,9);
                        printf("Não existe um jogo gravado!!!\n");
                    }
                    break;
                }
            case '3':
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
                gotoxy((w/2) - 13,9);
                printf("Nao existe essa opcao!!!\n");
        }
    }
}