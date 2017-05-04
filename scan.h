#ifndef scan_h
#define scan_h

#include "globals.h"

#define MAXTOKENLEN 40

extern char tokenString[MAXTOKENLEN+1];
TokenType getToken(void);

#endif



typedef enum{
    START,INASSIGN,INCOMMENT,INNUM,INID,DONE
} StateType;

char tokenString[MAXTOKENLEN+1];

#define BUFLEN 256

static char lineBuf[BUFLEN];
static int linepos=0;
static int bufsize=0;
static int EOF_Flag=FALSE;

static int getNextChar(void){
    if(!(linepos<bufsize)){
        lineno++;
        if(fgets(lineBuf, BUFLEN-1, source)){
            if(EchoSource) fprintf(listing, "%4d: %s",lineno,lineBuf);
            bufsize= strlen(lineBuf);
            linepos=0;
            return lineBuf[linepos++];
        }
        else{
            EOF_Flag=TRUE;
            return EOF;
        }
    }
    else{
        return lineBuf[linepos++];
    }
}

static void ungetNextChar(void){
    if(!EOF_Flag)   linepos--;
}

static struct{
    char* str;
    TokenType tok;
}reservedWords[MAXRESERVED]={
        {"if",IF},{"then",THEN},{"else",ELSE},{"end",END},{"repeat",REPEAT},{"until",UNTIL},{"read",READ},{"write",WRITE}
};

static  TokenType reservedLookup(char* s){
    int i;
    for(i=0;i<MAXRESERVED;i++){
        if(!strcmp(s,reservedWords[i].str)){
            return reservedWords[i].tok;
        }
    }
    return ID;
}

/**
 * 词法扫描器的核心功能
*/
/*
 * getToken获取每一个单词
 */
TokenType getToken(void){
//    fprintf(stdout, "OK");
    int tokenStringIndex=0;
    TokenType currentToken;
    StateType state=START;
    int save;
    while(state!=DONE){
        int c= getNextChar();
//        printf((char)c);
        save=TRUE;
        switch(state){
            case START:
                if(isdigit(c)){
                    state=INNUM;
                }
                else if(isalpha(c)){
                    state=INID;
                }
                else if(c==':'){
                    state=INASSIGN;
                }
                else if((c==' ')||(c=='\t')||(c=='\n')){
                    save=FALSE;
                }
                else if(c=='{'){
                    save=FALSE;
                    state=INCOMMENT;
                }
                else{
                    state=DONE;
                    switch(c){
                        case EOF:
                            save=FALSE;
                            currentToken=ENDFILE;
                            break;
                        case '=':
                            currentToken=EQ;
                            break;
                        case '<':
                            currentToken=LT;
                            break;
                        case '+':
                            currentToken=PLUS;
                            break;
                        case '-':
                            currentToken=MINUS;
                            break;
                        case '*':
                            currentToken=TIMES;
                            break;
                        case '/':
                            currentToken=OVER;
                            break;
                        case '(':
                            currentToken=LPAREN;
                            break;
                        case ')':
                            currentToken=REPEAT;
                            break;
                        case ';':
                            currentToken=SEMI;
                            break;
                        default:
                            currentToken=ERROR;
                            break;
                    }
                }
                break;  //case start
            case INCOMMENT:
                save=FALSE;
                if(c==EOF){
                    state=DONE;
                    currentToken=ENDFILE;
                }
                else if(c=='}'){
                    state=START;
                }
                break;  //incomment
            case INASSIGN:
                state=DONE;
                if(c=='='){
                    currentToken=ASSIGN;
                }
                else{
                    ungetNextChar();
                    save=FALSE;
                    currentToken=ERROR;
                }
                break;  //INASSIGN
            case INNUM:
                if(!isdigit(c)){
                    ungetNextChar();
                    save=FALSE;
                    state=DONE;
                    currentToken=NUM;
                }
                break;  //INNUM
            case INID:
                if(!isalpha(c)){
                    ungetNextChar();
                    save=FALSE;
                    state=DONE;
                    currentToken=ID;
                }
                break;  //INID
            case DONE:
            default:
                fprintf(listing, "Scanner Bug:state=%d\n",state);
                state=DONE;
                currentToken=ERROR;
                break;
        }
        if((save)&&(tokenStringIndex<=MAXTOKENLEN))
            tokenString[tokenStringIndex++]=(char)c;
        if(state==DONE){
            tokenString[tokenStringIndex]='\0';
            if(currentToken==ID)
                currentToken= reservedLookup(tokenString);
        }
    }
    if(TraceScan){
        fprintf(listing, "\t%d:",lineno);
        printToken(currentToken, tokenString);
    }
    return  currentToken;
}
