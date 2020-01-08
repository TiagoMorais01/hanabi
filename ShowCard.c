#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h>
#endif
#include "Card.h"
#include "player.h"
#include "Log.h"
#include "ShowCard.h"
#define gotoxy(x,y) printf("\033[%d;%dH", (y) , (x))

//Função para definir uma cor para as letras imprimidas
void setColor(char c){
    switch (c){
        case 'B':
            printf("\033[0;34m");
            break;
        case 'G':
            printf("\033[0;32m");
            break;
        case 'Y':
            printf("\033[0;33m");
            break;
        case 'R':
            printf("\033[0;31m");
            break;
        case 'W':
            printf("\033[0m");
            break;
        default:
            printf("\033[0m");
            break;
    }
}

//Função para verificar se o jogador tem ou não a cor visivel para imprimir na respetiva cor a carta
void selColor(Player p, int n){
    if(getCvc(getCard(p, n))){
        setColor(getCc(getCard(p, n)));
    }
    else{
        setColor('W');
    }
}

//Função para desenhar uma carta
void drawCard(int x, int y, int val){
    gotoxy(x, y);
    printf("%lc%lc%lc%lc%lc%lc%lc", 0x256D, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x256E);
    gotoxy(x, y+1);

    if(val != 0){
        if(val - 9 > 0){
            printf("%lc  ", 0x2502); 
            printf("%d %lc", val, 0x2502);
        }
        else{
            printf("%lc  ",0x2502);
            printf("%d", val);
            printf("  %lc", 0x2502);
        }
    }
    else{
        printf("%lc     %lc", 0x2502, 0x2502);
    }

    gotoxy(x, y+2);
    printf("%lc     %lc", 0x2502, 0x2502);

    gotoxy(x, y+3);
    printf("%lc%lc%lc%lc%lc%lc%lc\n", 0x2570, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x256F);

}

//Função para desenhar uma carta tracejada para quando não tiver nenhuma carta na pilha
void drawCardI(int x, int y, int val, int w){
    gotoxy(x, y);
    printf("%lc%lc%lc%lc%lc%lc%lc", 0x256D, 0x2504, 0x2504, 0x2504, 0x2504, 0x2504, 0x256E);
    gotoxy(x, y+1);

    if(val != 0){
        if(val - 9 > 0){
            printf("%lc  ", 0x2506); 
            printf("%d %lc", val, 0x2506);
        }
        else{
            printf("%lc  ",0x2506);
            printf("%d", val);
            printf("  %lc", 0x2506);
        }
    }
    else{
        (w) ? printf("%lc  0  %lc", 0x2506, 0x2506) : printf("%lc     %lc", 0x2506, 0x2506);
    }

    gotoxy(x, y+2);
    printf("%lc     %lc", 0x2506, 0x2506);

    gotoxy(x, y+3);
    printf("%lc%lc%lc%lc%lc%lc%lc\n", 0x2570, 0x2504, 0x2504, 0x2504, 0x2504, 0x2504, 0x256F);
}

//Função para desenhar uma carta para o jogador(desenha so meia carta)
void drawCardP(int x, int y, int val){

    gotoxy(x, y);
    printf("%lc%lc%lc%lc%lc%lc%lc", 0x256D, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x256E);
    gotoxy(x, y+1);

    if(val != 0){
        if(val - 9 > 0){
            printf("%lc  ", 0x2502); 
            printf("%d %lc", val, 0x2502);
        }
        else{
            printf("%lc  ",0x2502);
            printf("%d", val);
            printf("  %lc", 0x2502);
        }
    }
    else{
        printf("%lc     %lc", 0x2502, 0x2502);
    }
}

//Função para desenhar uma carta para o trash(Desenha so meia carta e com o numero mais inclinado para a esquerda)
void drawTrash(int x, int y, Card c){
    gotoxy(x, y);
    printf("%lc%lc%lc%lc%lc%lc%lc", 0x256D, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x256E);
    gotoxy(x, y+1);
    printf("%lc %d   %lc", 0x2502, getCnum(c), 0x2502);
    gotoxy(x, y+2);    
}

void adjustString(int w, int *k, char *exp){
    int i = 0;
    int j = (w -((w/2)+6*2+8) + 1);
    gotoxy((w/2)+6*2+8, 5 + (*k) * 2);
    if (strlen(exp) > 41){
        for (i = 0; i < j; i++){
            printf("%c", exp[i]);
        }
        gotoxy((w/2)+6*2+8, 13 + (*k) * 2);
        (*k)++;
        char aux[strlen(exp) - 41];
        memset(aux, '\0', strlen(exp) - 41);
        memcpy(aux, &exp[41], strlen(exp) - 41);
        aux[strlen(exp) - 41] = '\0';
        adjustString(w, k, aux);
    }
    else{
        printf("%s", exp);
    }
}

//Função responsável por desenhar a mesa de jogo(obtem: O Deck, a lixeira, o jogador e a ai, a pilha, o numero de vidas, as dicas, o numero de cartas no dekc, na lixeira e na pilha)
void ShowCardAI(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, Log log[], int lives, int tips , int nc, int nt, int np){

    int w, h;
    int col,row;
    int i = 0;
    //Vê se é windows para obter o tamanho da janelas das librarias corretas
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        row = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        w = csbi.dwSize.X;
        //col = csbi.srWindow.Right - csbi.srWindow.Left + 1; 
        //row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    //senao e linux/mac
    #else
        system("clear");
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        w = size.ws_col;
        h = size.ws_row;
        //xdotool windowsize $WINDOW_ID_GOES_HERE $WIDTH $HEIGHT
    #endif

    int tamNai = tamNpl(ai);
    int tamNjog = tamNpl(jog);
    
    //Desenhar uma carta para o Deck
    if(nc > 0)
        drawCard(0,1,nc);
    else
        drawCardI(0, 1, 0, 1);
    
    //Escrever o nome da AI
    gotoxy((w/2) + (tamNai/2)-11,3);
    printf("%s", getnome(ai));

    //Imprimir o numero de dicas e vida
    gotoxy((w/5 - 15), 2);
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        printf("Dicas: %d", tips);
    #else
        if(tips != 0){
            setColor('Y');
            printf("%lc", 0x1D25);
            for(i = 1;i < tips; i++)
                printf(" %lc", 0x1D25);
        }
    #endif

    gotoxy((w/5-15),3);
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        printf("Vidas: %d", lives);
    #else
        setColor('R');
        printf("%lc", 0x2665);
        for(i = 1;i < lives; i++)
            printf(" %lc", 0x2665);
    #endif

    setColor('W');
    
    //Mão Gervásio(AI)
    for (i = 0; i < getNCP(ai); i++){
        setColor(getCc(getCard(ai, i)));
        gotoxy((w/2)-6*2+i*8-10, 4);
        printf("%d",getCvc(getCard(ai, i)));
        drawCard((w/2)-6*2+i*8-10, 5, getCnum(getCard(ai, i)));
    }
    
    //Jogo(Pilha)
    int ac = 0;
    int coresI[5] = {0, 0, 0, 0 ,0};
    char cores[6] = {'B','G','R','W','Y'};
    int maior = 0;
    i = 0;
    int j = 0;

    //Imprimir as cartas por ordem de cor de numero
    //setAllVisNP(jog);
    //setAllVisCP(jog);
    
    while(i <= np){
        if(i < np){
            if (getCpilha(pi, i) != NULL){
                if(cores[ac] == getCc(getCpilha(pi, i))){
                    if (getCnum(getCpilha(pi, i)) > maior){
                        maior = getCnum(getCpilha(pi, i));
                    }
                    i++;
                }
                else{
                    if (maior != 0){
                        setColor(cores[ac]);
                        drawCard((w/2)-6*2+ac*8-10, 9, maior);
                        coresI[ac] = 1;
                        maior = 0;
                    }
                    else{
                        setColor(cores[ac]);
                        drawCardI((w/2)-6*2+ac*8-10, 9, 0, 0);
                    }
                    ac++;
                }
            }
            else{
                setColor(cores[ac]);
                drawCardI((w/2)-6*2+ac*8-10, 9, 0, 0);
            }
        }
        else{
            setColor(cores[ac]);
            drawCard((w/2)-6*2+ac*8-10, 9, maior);
            coresI[ac] = 1;
            i++;
        }
    }
    
    for (i = 0; i < 5; i++){
        if (coresI[i] == 0){
            setColor(cores[i]);
            drawCardI((w/2)-6*2+i*8-10, 9, 0, 0);
        }
    }

    //Jogadas
    setColor('W');
    char *tmpLog[3];
    for (i = 0; i < 3; i++){
        tmpLog[i] = (char*) malloc(200);
    }
    int nTmpLog = 0;
    int k = 0;
    nTmpLog = getLastThree(log, jog, ai, tmpLog);
    for (i = 0, k = 0; i < nTmpLog; i++, k++){
        if(strlen(tmpLog[i]) < (w -((w/2)+6*2+7)+1)){
            gotoxy((w/2)+6*2+8, 5 + k * 2);//length 42
            printf("%s", tmpLog[i]);
        }
        else{
            adjustString(w, &k, tmpLog[i]);
        }
    }

    //Função para ordenar a lixeira(trash) por onde de cor e crescente
    char p;
    int l = 0, m = 0;
    k = 0;
    //Imprime a lixeira(trash)
    for(i = 0 ; i < nt ; i++, l++){
        Card c = getCa(trash, i+1);
        
        if (i == 0){
            p = getCc(c);
        }
        else if(p != getCc(c)){
            k++;
            l = 0;
            m++;
            p = getCc(c);
        }

        
        if(c != NULL){
            setColor(getCc(c));
            drawTrash(l*3+1, 4+k*3+1-m, c);
        }
        else
            break;
    }

    //Mão player
    for (i = 0; i < getNCP(jog); i++){
        if (getCard(jog, 0) != NULL){
            selColor(jog, i);
            if(getCvn(getCard(jog, i))){//Um if para verificar se o numero da carta está visível para imprimir ou não
                drawCardP((w/2)-6*2+i*8-10, 13, getCnum(getCard(jog, i)));
            }
            else{
                drawCardP((w/2)-6*2+i*8-10, 13, 0);
            }
        }
    }

    //Atribui a cor branca e imprime as posições de cada respetiva carta
    setColor('W');
    gotoxy((w/2)-6*2-11,15);
    for (i = 0; i < getNCP(jog); i++){
        printf("   (%d)  ", i+1);
    }
    printf("\n");
    
    if(tamNjog > 4){
        gotoxy((w/2)+7-(tamNjog/2)-10, 17);
        printf("%s", getnome(jog));
    }
    else{
        gotoxy((w/2)+6-10, 17);
        printf("%s", getnome(jog));
    }
    printf("\n");
    return;
}
