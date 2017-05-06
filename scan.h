#ifndef scan_h
#define scan_h

#include "globals.h"

//单词的最大长度
#define MAXTOKENLEN 40
//读入的行的最大长度
#define BUFLEN 256

//当前读取的字符串
//extern char tokenString[MAXTOKENLEN+1];
TokenType getToken(void);




//状态
typedef enum{
    START,INASSIGN,INCOMMENT,INNUM,INID,DONE
} StateType;
//当前读取的字符串
char tokenString[MAXTOKENLEN+1];


//储存当前行的数组
static char lineBuf[BUFLEN];
//读取到当前行的位置
static int linepos=0;
static int bufsize=0;
//文件结束标志
static int EOF_Flag=FALSE;

/******************************************************
* 该函数用与获取每一行的下一个字符
******************************************************/
static int getNextChar(void){
    if(!(linepos<bufsize)){
        //linepos>=bufsize,说明已经到达一行的末尾,此时要增加行号,并且开始读取下一行
        lineno++;
        if(fgets(lineBuf, BUFLEN-1, source)){
            //读取下一行成功,表示还未到达文件的末尾
            if(EchoSource) fprintf(listing, "%4d: %s",lineno,lineBuf);
            bufsize= strlen(lineBuf);
            linepos=0;
            return lineBuf[linepos++];
        }
        else{
            //文件末尾
            EOF_Flag=TRUE;
            return EOF;
        }
    }
    else{
        //为到达一行的末尾,继续读取一行的下一个字符
        return lineBuf[linepos++];
    }
}

/******************************************************
* 该函数在出错的时候,退回,以不影响后面的单词的读取
******************************************************/
static void ungetNextChar(void){
    if(!EOF_Flag)   linepos--;
}

//实现词法分析符号与字符串的对应
static struct{
    char* str;
    TokenType tok;
}reservedWords[MAXRESERVED]={
        {"if",IF},{"then",THEN},{"else",ELSE},{"end",END},{"repeat",REPEAT},{"until",UNTIL},{"read",READ},{"write",WRITE}
};

//以现行搜索的方式查找保留字
static  TokenType reservedLookup(char* s){
    int i;
    for(i=0;i<MAXRESERVED;i++){
        if(!strcmp(s,reservedWords[i].str)){
            return reservedWords[i].tok;
        }
    }
    return ID;
}


/******************************************************
 ======该函数在出错的时候,退回,以不影响后面的单词的读取=======
******************************************************/



/******************************************************
* 该函数是词法分析器的核心功能,用于从读入的字符串中扫描出单词符号
******************************************************/
TokenType getToken(void){
    int tokenStringIndex=0;
    TokenType currentToken;     //当前读取到的单词
    StateType state=START;      //初始化状态为"开始"
    int save;                   //是否保存单词
    while(state!=DONE){
        int c= getNextChar();
        save=TRUE;
        switch(state){
            case START:
                if(isdigit(c)){     
                    //可能是数值情况
                    state=INNUM;
                }
                else if(isalpha(c)){
                    //可能是变量标识符的情况
                    state=INID;
                }
                else if(c==':'){
                    //可能是赋值情况
                    state=INASSIGN;
                }
                else if((c==' ')||(c=='\t')||(c=='\n')||c=='\r'){
                    //跳过空字符
                    save=FALSE;
                }
                else if(c=='{'){
                    //注释开始
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
                    //注释没有结束,文件便结束的情况
                    state=DONE;
                    currentToken=ENDFILE;
                }
                else if(c=='}'){
                    //注释结束
                    state=START;
                }
                break;  //incomment
            case INASSIGN:
                state=DONE;
                if(c=='='){
                    //确定为赋值情况
                    currentToken=ASSIGN;
                }
                else{
                    //错误情况
                    ungetNextChar();
                    save=FALSE;
                    currentToken=ERROR;
                }
                break;  //INASSIGN
            case INNUM:
                if(!isdigit(c)){
                    //错误情况
                    ungetNextChar();
                    save=FALSE;
                    state=DONE;
                    currentToken=NUM;
                }
                break;  //INNUM
            case INID:
                if(!isalpha(c)){
                    //错误情况
                    ungetNextChar();
                    save=FALSE;
                    state=DONE;
                    currentToken=ID;
                }
                break;  //INID
            case DONE:
            default:
                //未定义状态,视为状态机的bug
                fprintf(listing, "Scanner Bug:state=%d\n",state);
                state=DONE;
                currentToken=ERROR;
                break;
        }
        if((save)&&(tokenStringIndex<=MAXTOKENLEN))
            //根据之前的控制符决定是否保存当前字符
            tokenString[tokenStringIndex++]=(char)c;
        if(state==DONE){
            //完成一个单词的读取
            tokenString[tokenStringIndex]='\0';
            if(currentToken==ID)
                //最开始,我们是将保留字视为一个变量标识符,在最后我们要根据之前的词法分析与单词对应表
                //确定该变量标识符是否是一个保留字
                currentToken= reservedLookup(tokenString);
        }
    }
    if(TraceScan){
        //输出当前的结果
        fprintf(listing, "\t%d:",lineno);
        printToken(currentToken, tokenString);
    }
    return  currentToken;
}

#endif