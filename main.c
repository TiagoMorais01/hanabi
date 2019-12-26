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

void saveGame(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, int lives, int tips, int nc, int nt, int np){
    FILE *salvar;
    if ((salvar = fopen("save.ha","w")) != NULL){
        system("clear");
        fprintf(salvar, "Gervásio\n%d\n", getNCP(ai));
        int i = 0;
        for(i = 0; i < getNCP(ai); i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCard(ai, i)), getCc(getCard(ai, i)), getCpos(getCard(ai, i)), getCvn(getCard(ai, i)), getCvc(getCard(ai, i)));
        }

        fprintf(salvar, "%s%d\n", getnome(jog), getNCP(jog));
        
        for(i = 0; i < getNCP(jog); i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCard(jog, i)), getCc(getCard(jog, i)), getCpos(getCard(jog, i)), getCvn(getCard(jog, i)), getCvc(getCard(jog, i)));
        }
        
        fprintf(salvar, "%d\n", nc);
        
        for(i = 1; i <= nc ; i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCa(deckM, i)), getCc(getCa(deckM, i)), getCpos(getCa(deckM, i)), getCvn(getCa(deckM, i)), getCvc(getCa(deckM, i)));
        }
        
        fprintf(salvar, "%d\n", np);

        for(i = 0; i < np ; i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCpilha(pi, i)), getCc(getCpilha(pi, i)), getCpos(getCpilha(pi, i)), getCvn(getCpilha(pi, i)), getCvc(getCpilha(pi, i)));
        }

        fprintf(salvar, "%d\n", nt);

        for(i = 0; i < nt ; i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCa(trash, i)), getCc(getCa(trash, i)), getCpos(getCa(trash, i)), getCvn(getCa(trash, i)), getCvc(getCa(trash, i)));
        }

        fprintf(salvar, "%d\n", lives);
        fprintf(salvar, "%d", tips);
    }
    fclose(salvar);
}

void loadGame(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, int *lives, int *tips, int *nc, int *nt, int *np){
    FILE *load;
    if((load = fopen("save.ha", "r")) != NULL){
        char nome[20];
        int i = 0;
        int k = 0;
        int num = 0;
        int pos = 0;
        int vc = 0;
        int vn = 0;
        char c;
        
        fscanf(load, "%s", nome);
        
        ai = newPlayer(nome);
        
        fscanf(load, "%d", &k);

        setNCplayer(ai, k);

        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            printf("NUM: %d C: %c POS: %d VN: %d VC: %d\n\n", num, c, pos, vn, vc);
            ConsCard(getCard(ai, i), num, c, pos, vn, vc);
        }

        fscanf(load, "%s", nome);
        
        jog = newPlayer(nome);
        
        fscanf(load, "%d", &k);

        setNCplayer(jog, k);

        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            ConsCard(getCard(jog, i), num, c, pos, vn, vc);
        }

        fscanf(load, "%d", &k);

        (*nc) = k;

        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            ConsCard(getCa(deckM, i), num, c, pos, vn, vc);
        }

        fscanf(load, "%d", &k);

        (*np) = k;

        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            ConsCard(getCpilha(pi, i), num, c, pos, vn, vc);
        }

        fscanf(load, "%d", &k);

        (*nt) = k;

        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            ConsCard(getCa(trash, i), num, c, pos, vn, vc);
        }

        fscanf(load, "%d\n%d", lives, tips);
    }
    fclose(load);
}

//Função main do jogo onde ocorre a gestão do jogo
void newGame(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, int lives, int tips, int nc, int nt, int np){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
    #else
        system("clear");
    #endif
    createDeck(deckM);//Função que preenche o Deck
    dealCards(jog, ai, deckM, &nc);//Função que distribui as cartas pelos jogadores
    ShowCardAI(deckM, trash, ai, jog, pi, lives, tips, nc, nt, np);//Função que imprime a mesa do jogo
    time_t t;
    srand((unsigned)time(&t));
    int play = rand() % 2;//Escolhe a sorte qual jogardor vai começar
    char mov;
    char x;
    int r = 1;
    int ultimasJ = 0;
    //Main loop que faz decorrer o jogo
    while ((r || ultimasJ) && lives != 0){
        
        if (nc == 0 && r == 1){
            /* code */
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
                            if(selNum(ai, play))
                                tips--;
                            ShowCardAI(deckM, trash, ai, jog, pi, lives, tips, nc, nt, np);
                        }
                        else if (x == '2'){
                            if(selCor(ai, play))//Dá a dica de uma cor
                                tips--;
                            ShowCardAI(deckM, trash, ai, jog, pi, lives, tips, nc, nt, np);
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
                            setCpilha(pi, grCard(jog, ((int)x)-49), np++, &tips);
                            lessCardsP(jog);
                            if (nc > 0){
                                pickCard(jog, grCa(deckM, nc--));//Função que pega uma carta do deck e atribui ao jogador
                                plusCardsP(jog);
                            }
                            if(getNCP(jog) < 5){
                                pushToLeft(jog);
                            }
                            play = 0;//Passa a vez para a AI
                            sortPilha(pi, 0, np - 1);//Função para ordenar a pilha
                        }
                        else{
                            gototrash(trash, grCard(jog, ((int)x)-49), nt++);//Função que passa a carta para o descarte
                            lessCardsP(jog);
                            if (nc > 0){
                                pickCard(jog, grCa(deckM, nc--));//Função que pega uma carta do deck e atribui ao jogador
                                plusCardsP(jog);
                            }
                            if(getNCP(jog) < 5){
                                pushToLeft(jog);
                            }
                            lives--;
                            play = 0;//Passa a vez para a AI
                        }
                        ShowCardAI(deckM, trash, ai, jog, pi, lives, tips, nc, nt, np);
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
                            gototrash(trash, grCard(jog, ((int)x)-49), nt++);//Função que passa a carta para o descarte
                            lessCardsP(jog);
                            if (nc > 0){
                                pickCard(jog, grCa(deckM, nc--));//Função que pega uma carta do deck e atribui ao jogador
                                plusCardsP(jog);
                            }
                            if(getNCP(jog) < 5){
                                pushToLeft(jog);
                            }
                            tips++;
                            play = 0;//Passa a vez para a AI
                            ShowCardAI(deckM, trash, ai, jog, pi, lives, tips, nc, nt, np);
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
                    while (x != 'S' && x != 's' && x != 'N' && x != '0'){
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
                        saveGame(deckM, trash, ai, jog, pi, lives, tips, nc, nt, np);
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
            play = 1;
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
    int lives = 3;
    int tips = 8;
    int nc = 50;
    int nt = 0;
    int np = 0;
	int h = 0;
	int w = 0;

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
        printf("            ");
        gotoxy((w/2) - 13,4);
        printf("1 - New Game");
        gotoxy((w/2) - 13,5);
        printf("            ");
        gotoxy((w/2) - 13,5);
        printf("2 - Load Game");
        gotoxy((w/2) - 13,6);
        printf("            ");
        gotoxy((w/2) - 13,6);
        printf("3 - Tutorial");
        gotoxy((w/2) - 13,7);
        printf("            ");
        gotoxy((w/2) - 13,7);
        printf("0 - Sair");
        gotoxy((w/2) - 13,8);
        printf("            ");
        gotoxy((w/2) - 13,8);
        printf("-> ");
        c = getchar();
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
                fgets(no, sizeof(no), stdin);
                //Ver se o nome é maior que 16 caracteres
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
                    gotoxy((w/2) - 13,7);
                    printf("            ");
                    gotoxy((w/2) - 13,8);
                    printf("                             ");
                    gotoxy((w/2) - 13,5);
                    printf("->");
                    fgets(no, sizeof(no), stdin);
                }
                ai = newPlayer("Gervásio");//Cria a AI
                jog = newPlayer(no);//Cria a estrutura jogador
                deckM = newDeck();//Inicia um array deck
                trash = newDeck();//Inicia um array trash
                pilha = newPilha();//Inicia um array para armazenar as cartas jogadas para a mesa
                newGame(deckM, trash, ai, jog, pilha, lives, tips, nc, nt, np);//Função do jogo
                /* Apaga as variaveis da memoria */
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
            case '2':
                if (fopen("save.ha", "r")){
                    deckM = newDeck();//Inicia um array deck
                    trash = newDeck();//Inicia um array trash
                    pilha = newPilha();//Inicia um array para armazenar as cartas jogadas para a mesa
                    loadGame(deckM, trash, ai, jog, pilha, &lives, &tips, &nc, &nt, &np);
                    free(deckM);
                    free(trash);
                    freeP(ai);
                    freeP(jog);
                    freePi(pilha);
                }
                else{
                    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                    system("cls");
                    #else
                        system("clear");
                    #endif
                    gotoxy((w/2) - 13,8);
                    printf("Nao existe essa opcao!!!\n");
                }
                break;
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
                gotoxy((w/2) - 13,8);
                printf("Nao existe essa opcao!!!\n");
        }
    }
}