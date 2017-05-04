//
//  globals.h
//  tiny
//
//  Created by admin on 2017/4/10.
//  Copyright © 2017年 admin. All rights reserved.
//

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
#endif

/*MAXRESERVED=保留字的数目*/
#define MAXRESERVED 8

typedef enum {
    ENDFILE,ERROR,
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,   //保留字
    ID,NUM,     //标识符和数字(可能是不定的字母)
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
}TokenType;


extern FILE* source;        //源码文件
extern FILE* listing;       //输出列表文件
extern FILE* code;          //TM的编码文本

extern int lineno;          //源码的行数

/*****************************
 *******语法树转化**************
 ****************************/

typedef enum{StmtK,ExpK} NodeKind;      //节点的种类
typedef enum{IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;        //语句的种类
typedef enum{OpK,ConstK,IdK} ExpKind;       //表达式的种类,用于检查表达式的种类
typedef enum{Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode{
    struct treeNode* child[MAXCHILDREN];
    struct treeNode* sibling;
    int lineno;
    NodeKind nodeKind;
    union{StmtKind stmt;ExpKind exp;}kind;
    union{
        TokenType op;
        int val;
        char* name;
    }attr;
    ExpType type;
} TreeNode;


/*****************************
 *******跟踪的标志**************
 ****************************/

extern int EchoSource;

extern int TraceScan;

extern int TraceParse;

extern int TraceAnalyze;

extern int TraceCode;

extern int error;

#endif /* globals_h */
