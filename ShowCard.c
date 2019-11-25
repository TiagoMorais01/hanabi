#include <stdio.h>
#include <stdlib.h>
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
#include "ShowCard.h"
#define gotoxy(x,y) printf("\033[%d;%dH", (y) , (x))


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

void selColor(Player p, int n){
    if(getCvc(getCard(p, n))){
        setColor(getCc(getCard(p, n)));
    }
    else{
        setColor('W');
    }
}

void drawCard(int x, int y, int val){
    setlocale(LC_ALL, "");
    gotoxy(x, y);
    printf("%lc%lc%lc%lc%lc%lc%lc", 0x250C, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x2510);
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
    printf("%lc%lc%lc%lc%lc%lc%lc\n", 0x2514, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x2518);

}

void drawCardP(int x, int y, int val){

    gotoxy(x, y);
    printf("%lc%lc%lc%lc%lc%lc%lc", 0x250C, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x2510);
    gotoxy(x, y+1);
    printf("%lc     %lc", 0x2502, 0x2502);
    gotoxy(x, y+2);

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

void drawTrash(int x, int y, Card c){
    gotoxy(x, y);
    printf("%lc%lc%lc%lc%lc%lc%lc", 0x250C, 0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 0x2510);
    gotoxy(x, y+1);
    printf("%lc %d   %lc", 0x2502, getCnum(c), 0x2502);
    gotoxy(x, y+2);    
}

void ShowCardAI(Deck deck, Deck trash, Player ai, Player jog, int lives, int tips , int nc, int nt){

    int w, h;
    int col,row;
    int i = 0;
  
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

    //col = csbi.srWindow.Right - csbi.srWindow.Left + 1; 
    //row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int tamNai = tamNpl(ai);
    int tamNjog = tamNpl(jog);
    
    
    drawCard(0,1,nc);

    gotoxy((w/2) + (tamNai/2)-1,0);
    printf("%s", getnome(ai));
    if(tips != 0){
        gotoxy((w/5 - 15), 2);
        printf("%lc", 0x1F4A1);
        for(i = 1;i < tips; i++)
            printf(" %lc", 0x1F4A1);
    }
    
    gotoxy((w/5-15),3);
    printf("%lc", 0x2661);
    for(i = 1;i < lives; i++)
        printf(" %lc", 0x2661);

    //mao Gervásio
    setColor(getCc(getCard(ai, 0)));
    drawCard((w/2)-6*2, 2, getCnum(getCard(ai, 0)));
    setColor(getCc(getCard(ai, 1)));
    drawCard((w/2)-6+2, 2, getCnum(getCard(ai, 1)));
    setColor(getCc(getCard(ai, 2)));
    drawCard((w/2)+4, 2, getCnum(getCard(ai, 2)));
    setColor(getCc(getCard(ai, 3)));
    drawCard((w/2)+12, 2, getCnum(getCard(ai, 3)));
    setColor(getCc(getCard(ai, 4)));
    drawCard((w/2)+20, 2, getCnum(getCard(ai, 4)));

    //jogo
    setColor('B');
    drawCard((w/2)-6*2, 6, 0);
    setColor('G');
    drawCard((w/2)-6+2, 6, 0);
    setColor('R');
    drawCard((w/2)+4, 6, 0);
    setColor('W');
    drawCard((w/2)+12, 6, 0);
    setColor('Y');
    drawCard((w/2)+20, 6, 0);
    
    //setAllVisCP(jog);
    //setAllVisNP(jog);
    
    while (nt < 13){
        gototrash(deck, trash, getCa(deck, nt+1), nt++, nc--);
    }

    sortTrash(trash, 0, nt - 1);

    char p;
    int k = 0, l = 0, m = 0;

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


    //mao player
    selColor(jog, 0);
    if(getCvn(getCard(jog, 0))){
        drawCardP((w/2)-6*2, 10, getCnum(getCard(jog, 0)));
    }
    else{
        drawCardP((w/2)-6*2, 10, 0);
    }

    
    selColor(jog, 1);
    if(getCvn(getCard(jog, 1))){
        drawCardP((w/2)-6+2, 10, getCnum(getCard(jog, 1)));
    }
    else{
        drawCardP((w/2)-6+2, 10, 0);
    }
    
    selColor(jog, 2);
    if(getCvn(getCard(jog, 2))){
        drawCardP((w/2)+4, 10, getCnum(getCard(jog, 2)));
    }
    else{
        drawCardP((w/2)+4, 10, 0);
    }

    selColor(jog, 3);
    if(getCvn(getCard(jog, 3))){
        drawCardP((w/2)+12, 10, getCnum(getCard(ai, 3)));
    }
    else{
        drawCardP((w/2)+12, 10, 0);
    }

    selColor(jog, 4);
    if(getCvn(getCard(jog, 4))){
        drawCardP((w/2)+20, 10, getCnum(getCard(ai, 4)));
    }
    else{
        drawCardP((w/2)+20, 10, 0);
    }

    setColor('W');
    gotoxy((w/2)-6*2,14);
    printf("  (1)     (2)     (3)     (4)     (5)   \n");
    if(tamNjog > 4){
        gotoxy((w/2)+7-(tamNjog/2), 15);
        printf("%s", getnome(jog));
    }
    else{
        gotoxy((w/2)+6, 15);
        printf("%s", getnome(jog));
    }
    printf("\n");
    return;
}
