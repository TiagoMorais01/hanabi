typedef struct _Log* Log;

Log* newLog();
char* getExp(Log[], int);
int getLastThree(Log[], Player, Player, char*[]);
int exportLog(Log[]);
int loadLog(Log[]);
int insertLog(Log[], char*);
int deleteLog(Log[]);