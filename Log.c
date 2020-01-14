#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Card.h"
#include "player.h"
#include "Log.h"
#define gotoxy(x,y) printf("\033[%d;%dH", (y) , (x))

//estrutura para guardar as jogadas
struct _Log{
    char exp[10];
};

//Iniciar a estrutura Log
Log* newLog(){
    Log *tmpL = (Log*) malloc(100 * sizeof(struct _Log));
    int i = 0;
    for (i = 0; i < 100; i++){
        tmpL[i] = NULL;
    }
    return tmpL;
}

//Retorna a jogada i
char* getExp(Log log[], int i){
    return log[i]->exp;
}

//Obter as três ultimas jogadas
int getLastThree(Log log[], Player p, Player ai, char *tmpLog[]){
    int i = 0;
    int j = 0;
    int k = 0;
    char aux[20];
    char aux2[5];
    for (;log[i] != NULL;i++);
    k = (i > 3) ? 3 : i;
    for (j = 0; (i - k + j) < i; j++){
        strcpy(aux, log[i - k + j]->exp);
        if (aux[0] == 'P'){
            if (aux[1] == '-' && aux[2] == 'D'){
                if (aux[3] == '-' && (aux[4] > '0' && aux[4] < '6')){
                    strcpy(tmpLog[j], "O jogador");
                    strcat(tmpLog[j], " indicou a(s) carta(s) com o número");
                    switch (aux[4]){
                        case '1':{
                            strcat(tmpLog[j], " 1.");
                            break;
                        }
                        case '2':{
                            strcat(tmpLog[j], " 2.");
                            break;
                        }
                        case '3':{
                            strcat(tmpLog[j], " 3.");
                            break;
                        }
                        case '4':{
                            strcat(tmpLog[j], " 4.");
                            break;
                        }
                        case '5':{
                            strcat(tmpLog[j], " 5.");
                            break;
                        }
                        default:
                            break;
                    }
                }
                else if(aux[3] == '-' && (aux[4] == 'B' || aux[4] == 'G' || aux[4] == 'R' || aux[4] == 'W' || aux[4] == 'Y')){
                    strcpy(tmpLog[j], "O jogador");
                    strcat(tmpLog[j], " indicou a(s) carta(s) com a cor");
                    switch (aux[4]){
                        case 'B':{
                            strcat(tmpLog[j], " azul.");
                            break;
                        }
                        case 'G':{
                            strcat(tmpLog[j], " verde.");
                            break;
                        }
                        case 'R':{
                            strcat(tmpLog[j], " vermelha.");
                            break;
                        }
                        case 'W':{
                            strcat(tmpLog[j], " branca.");
                            break;
                        }
                        case 'Y':{
                            strcat(tmpLog[j], " amarela.");
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            else if (aux[1] == '-' && aux[2] == 'T'){
                memset(aux2, '\0', 4);
                strcpy(tmpLog[j], "O jogador");
                strcat(tmpLog[j], " descartou a carta ");
                aux2[0] = aux[4];
                aux2[1] = '\0';
                strcat(tmpLog[j], aux2);
                switch (aux[5]){
                    case 'B':{
                        strcat(tmpLog[j], " azul.");
                        break;
                    }
                    case 'G':{
                        strcat(tmpLog[j], " verde.");
                        break;
                    }
                    case 'R':{
                        strcat(tmpLog[j], " vermelha.");
                        break;
                    }
                    case 'W':{
                        strcat(tmpLog[j], " branca.");
                        break;
                    }
                    case 'Y':{
                        strcat(tmpLog[j], " amarela.");
                        break;
                    }
                    default:
                        break;
                }
            }
            else if (aux[1] == '-' && aux[2] == 'J'){
                memset(aux2, '\0', 4);
                if (aux[3] == '-' && aux[4] == 'T'){
                    strcpy(tmpLog[j], "O jogador");
                    strcat(tmpLog[j], " jogou a carta ");
                    aux2[0] = aux[6];
                    aux2[1] = '\0';
                    strcat(tmpLog[j], aux2);
                    switch (aux[7]){
                        case 'B':{
                            strcat(tmpLog[j], " azul. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'G':{
                            strcat(tmpLog[j], " verde. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'R':{
                            strcat(tmpLog[j], " vermelha. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'W':{
                            strcat(tmpLog[j], " branca. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'Y':{
                            strcat(tmpLog[j], " amarela. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        default:
                            break;
                    }
                }
                else{
                    strcpy(tmpLog[j], "O jogador");
                    strcat(tmpLog[j], " jogou a carta ");
                    aux2[0] = aux[4];
                    aux2[1] = '\0';
                    strcat(tmpLog[j], aux2);
                    switch (aux[5]){
                        case 'B':{
                            strcat(tmpLog[j], " azul.");
                            break;
                        }
                        case 'G':{
                            strcat(tmpLog[j], " verde.");
                            break;
                        }
                        case 'R':{
                            strcat(tmpLog[j], " vermelha.");
                            break;
                        }
                        case 'W':{
                            strcat(tmpLog[j], " branca.");
                            break;
                        }
                        case 'Y':{
                            strcat(tmpLog[j], " amarela.");
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
        else if(aux[0] == 'C'){
            if (aux[1] == '-' && aux[2] == 'D'){
                if (aux[3] == '-' && (aux[4] > '0' && aux[4] < '6')){
                    strcpy(tmpLog[j], "O Gervásio");
                    strcat(tmpLog[j], " indicou a(s) carta(s) com o número");
                    switch (aux[4]){
                        case '1':{
                            strcat(tmpLog[j], " 1.");
                            break;
                        }
                        case '2':{
                            strcat(tmpLog[j], " 2.");
                            break;
                        }
                        case '3':{
                            strcat(tmpLog[j], " 3.");
                            break;
                        }
                        case '4':{
                            strcat(tmpLog[j], " 4.");
                            break;
                        }
                        case '5':{
                            strcat(tmpLog[j], " 5.");
                            break;
                        }
                        default:
                            break;
                    }
                }
                else if(aux[3] == '-' && (aux[4] == 'B' || aux[4] == 'G' || aux[4] == 'R' || aux[4] == 'W' || aux[4] == 'Y')){
                    strcpy(tmpLog[j], "O Gervásio");
                    strcat(tmpLog[j], " indicou a(s) carta(s) com a cor");
                    switch (aux[4]){
                        case 'B':{
                            strcat(tmpLog[j], " azul.");
                            break;
                        }
                        case 'G':{
                            strcat(tmpLog[j], " verde.");
                            break;
                        }
                        case 'R':{
                            strcat(tmpLog[j], " vermelha.");
                            break;
                        }
                        case 'W':{
                            strcat(tmpLog[j], " branca.");
                            break;
                        }
                        case 'Y':{
                            strcat(tmpLog[j], " amarela.");
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            else if (aux[1] == '-' && aux[2] == 'T'){
                memset(aux2, '\0', 4);
                strcpy(tmpLog[j], "O Gervásio");
                strcat(tmpLog[j], " descartou a carta ");
                aux2[0] = aux[4];
                aux2[1] = '\0';
                strcat(tmpLog[j], aux2);
                switch (aux[5]){
                    case 'B':{
                        strcat(tmpLog[j], " azul.");
                        break;
                    }
                    case 'G':{
                        strcat(tmpLog[j], " verde.");
                        break;
                    }
                    case 'R':{
                        strcat(tmpLog[j], " vermelha.");
                        break;
                    }
                    case 'W':{
                        strcat(tmpLog[j], " branca.");
                        break;
                    }
                    case 'Y':{
                        strcat(tmpLog[j], " amarela.");
                        break;
                    }
                    default:
                        break;
                }
            }
            else if (aux[1] == '-' && aux[2] == 'J'){
                memset(aux2, '\0', 4);
                if (aux[3] == '-' && aux[4] == 'T'){
                    strcpy(tmpLog[j], "O Gervásio");
                    strcat(tmpLog[j], " jogou a carta ");
                    aux2[0] = aux[6];
                    aux2[1] = '\0';
                    strcat(tmpLog[j], aux2);
                    switch (aux[7]){
                        case 'B':{
                            strcat(tmpLog[j], " azul. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'G':{
                            strcat(tmpLog[j], " verde. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'R':{
                            strcat(tmpLog[j], " vermelha. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'W':{
                            strcat(tmpLog[j], " branca. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        case 'Y':{
                            strcat(tmpLog[j], " amarela. Contudo foi descartada por não conbinar no monte.");
                            break;
                        }
                        default:
                            break;
                    }
                }
                else{
                    strcpy(tmpLog[j], "O Gervásio");
                    strcat(tmpLog[j], " jogou a carta ");
                    aux2[0] = aux[4];
                    aux2[1] = '\0';
                    strcat(tmpLog[j], aux2);
                    switch (aux[5]){
                        case 'B':{
                            strcat(tmpLog[j], " azul.");
                            break;
                        }
                        case 'G':{
                            strcat(tmpLog[j], " verde.");
                            break;
                        }
                        case 'R':{
                            strcat(tmpLog[j], " vermelha.");
                            break;
                        }
                        case 'W':{
                            strcat(tmpLog[j], " branca.");
                            break;
                        }
                        case 'Y':{
                            strcat(tmpLog[j], " amarela.");
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    }
    return j;
}

//Exportar a estrutura para um ficheiro
int exportLog(Log log[]){
    FILE* Flog;
    if ((Flog = fopen("save.log", "w")) != NULL){
        int i = 0;
        for (i = 0; log[i] != NULL; i++){
            fprintf(Flog, "%s\n", log[i]->exp);
        }
        fclose(Flog);
        return 1;
    }
    else{
        return 0;
    }
}

//Ler o ficheiro das jogadas do jogo guardado
int loadLog(Log log[]){
    FILE* Flog;
    if ((Flog = fopen("save.log", "r")) != NULL){
        int i = 0;
        char aux[20];
        for (i = 0; !feof(Flog); i++){
            fscanf(Flog, "%s", aux);
            if (strcmp(aux, "")){
                log[i] = (Log) malloc(sizeof(struct _Log));
                strcpy(log[i]->exp, aux);
                memset(aux, '\0', 10);
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}

//Inserir uma jogada na estrutura Log
int insertLog(Log log[], char* exp){
    int i = 0;
    while (log[i] != NULL) i++;
    log[i] = (Log) malloc(sizeof(struct _Log));
    if (log[i] != NULL){
        if(strcpy(log[i]->exp, exp) != NULL){
            return 1;
        }
    }
    return 0;
}

//Apagar o ficheiro Log e libertar a variavel com a estrutura Log
int deleteLog(Log log[]){
    int i = 0;
    for (i = 0; log[i] != NULL; i++){
        free(log[i]);
    }
    return 1;
}