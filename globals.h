#ifndef globals_h
#define globals_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1


/*MAXRESERVED=保留字的数目*/
#define MAXRESERVED 8

//枚举词法符号
typedef enum {
    ENDFILE,ERROR,                              //文件结尾和错误
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,   //保留字
    ID,NUM,     //标识符和数字(可能是不定的字母)
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
}TokenType;


extern FILE* source;        //源码文件
extern FILE* listing;       //输出列表文件

extern int lineno;          //源码的行数
#endif




//源文件跟踪标志
extern int EchoSource;
//跟踪标志
extern int TraceScan;
//错误
extern int error;

#endif /* globals_h */
