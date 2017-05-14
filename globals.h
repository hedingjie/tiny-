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

/*********************************************************************/
/************************   语   法   树    ***************************/
/*********************************************************************/

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {Opk,ConstK,Idk} ExpKind;

//用于进行类型检查
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILEREN 3

typedef struct TreeNode{
    struct TreeNode * child[MAXCHILDREN];
    struct TreeNode * sibling;
    int lineno;
    NodeKind nodekind;
    union{StmtKind stmt;ExpKind exp;} kind;
    union{TokenType op;int val;char* name;} attr;
    ExpType type;
};




//源文件跟踪标志
extern int EchoSource;
//跟踪标志
extern int TraceScan;
//跟踪语法分析
extern int TraceParse;
//跟踪分析过程
extern int TraceAnalyze;
//跟踪code
extern int TraceCode;
//错误
extern int Error;

#endif /* globals_h */
