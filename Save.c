#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Card.h"
#include "player.h"
#include "Save.h"

//Função para guardar o jogo
void saveGame(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, int lives, int tips, int nc, int nt, int np, int ultimasJ){
    FILE *salvar;
    if ((salvar = fopen("save.ha","w")) != NULL){
        system("clear");
        fprintf(salvar, "Gervásio\n%d\n", getNCP(ai));
        int i = 0;
        for(i = 0; i < getNCP(ai); i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCard(ai, i)), getCc(getCard(ai, i)), getCpos(getCard(ai, i)), getCvn(getCard(ai, i)), getCvc(getCard(ai, i)));
        }

        fprintf(salvar, "%s\n%d\n", getnome(jog), getNCP(jog));
        
        for(i = 0; i < getNCP(jog); i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCard(jog, i)), getCc(getCard(jog, i)), getCpos(getCard(jog, i)), getCvn(getCard(jog, i)), getCvc(getCard(jog, i)));
        }
        
        fprintf(salvar, "%d\n", nc);
        
        // <= porque a função getCa e i-1
        for(i = 1; i <= nc ; i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCa(deckM, i)), getCc(getCa(deckM, i)), getCpos(getCa(deckM, i)), getCvn(getCa(deckM, i)), getCvc(getCa(deckM, i)));
        }
        
        fprintf(salvar, "%d\n", np);

        for(i = 0; i < np ; i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCpilha(pi, i)), getCc(getCpilha(pi, i)), getCpos(getCpilha(pi, i)), getCvn(getCpilha(pi, i)), getCvc(getCpilha(pi, i)));
        }

        fprintf(salvar, "%d\n", nt);
        
        // <= porque a função getCa e i-1
        for(i = 1; i <= nt ; i++){
            fprintf(salvar, "%d, %c, %d, %d, %d\n", getCnum(getCa(trash, i)), getCc(getCa(trash, i)), getCpos(getCa(trash, i)), getCvn(getCa(trash, i)), getCvc(getCa(trash, i)));
        }

        fprintf(salvar, "%d\n%d\n%d", lives, tips, ultimasJ);
    }
    fclose(salvar);
}

//Função para carregar um jogo
void loadGame(Deck deckM, Deck trash, Player ai, Player jog, Pilha pi, int *lives, int *tips, int *nc, int *nt, int *np, int *ultimasJ){
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
        Card crd = NULL;
        (*lives) = 3;
        (*tips) = 8;
        (*nc) = 40;
        (*nt) = 0;
        (*np) = 0;
        
        fscanf(load, "%s", nome);
        
        setNPlayer(ai, nome);
        
        fscanf(load, "%d", &k);

        setNCplayer(ai, k);

        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            crd = newCard();
            ConsCard(crd, num, c, pos, vn, vc);
            setCPlayer(ai, crd, i);
        }

        fscanf(load, "%s", nome);
        
        setNPlayer(jog, nome);
        
        fscanf(load, "%d", &k);
        
        setNCplayer(jog, k);
        
        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            crd = newCard();
            ConsCard(crd, num, c, pos, vn, vc);
            setCPlayer(jog, crd, i);
        }
        
        fscanf(load, "%d", &k);
        
        (*nc) = k;
        
        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            //printf("NUM: %d C: %c POS: %d VN: %d VC: %d I: %d\n\n", num, c, pos, vn, vc, i);
            crd = newCard();
            ConsCard(crd, num, c, pos, vn, vc);
            setCard(deckM, crd, i);
        }
        
        fscanf(load, "%d", &k);

        (*np) = k;
        
        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            crd = newCard();
            ConsCard(crd, num, c, pos, vn, vc);
            setCpilha(pi, crd, i);
        }
        
        fscanf(load, "%d", &k);

        (*nt) = k;
        
        for (i = 0; i < k; i++){
            fscanf(load, "%d, %c, %d, %d, %d", &num, &c, &pos, &vn, &vc);
            crd = newCard();
            ConsCard(crd, num, c, pos, vn, vc);
            setCard(trash, crd, i);
        }
        
        fscanf(load, "%d\n%d\n%d", lives, tips, ultimasJ);

        fclose(load);
    }    
}