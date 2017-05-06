//
//  util.h
//  tiny
//
//  Created by admin on 2017/4/10.
//  Copyright © 2017年 admin. All rights reserved.
//

#ifndef util_h
#define util_h

#include "globals.h"

void printToken(TokenType,const char*);

char* copyString(char*);


#endif

#include "globals.h"

/**********************************
* 该函数根据输入的词法分析类型和读取得到
* 的字符串，在输出中打印词法扫描的结果。
**********************************/

void printToken(TokenType token,const char* tokenString){
    switch (token) {
        //保留字情况：直接输出对应的单词
        case IF:
        case THEN:
        case ELSE:
        case END:
        case REPEAT:
        case UNTIL:
        case READ:
        case WRITE:
            fprintf(listing,"reserved word:%s\n",tokenString);
            break;
        //特殊符号：输出词法分析符号所对应的特殊符号
        case ASSIGN:    fprintf(listing, ":=\n");break;
        case LT:    fprintf(listing, "<\n");break;
        case EQ:    fprintf(listing, "=\n");break;
        case LPAREN:    fprintf(listing, "(\n");break;
        case RPAREN:    fprintf(listing, ")\n");break;
        case SEMI:    fprintf(listing, ";\n");break;
        case PLUS:    fprintf(listing, "+\n");break;
        case MINUS:    fprintf(listing, "-\n");break;
        case TIMES:    fprintf(listing, "*\n");break;
        case OVER:    fprintf(listing, "/\n");break;
        case ENDFILE:   fprintf(listing, "EOF\n");break;
        //数字：输出该数字的值
        case NUM:
            fprintf(listing, "NUM, VAL=%s\n",tokenString);break;
        //变量：输出变量的标识符
        case ID:
            fprintf(listing, "ID, NAME=%s\n",tokenString);break;
        //出错：打印出错符号
        case ERROR:
            fprintf(listing, "ERROR:%s\n",tokenString);break;
        //未定义的符号
        default:
            fprintf(listing,"UNKNOWN TOKEN:%d\n",token);break;
    }
}



/**
 * 拷贝字符串
 * @param s
 * @return
 */
char* copyString(char* s){
    int n;
    char* t;
    if(s==NULL) return NULL;
    n= strlen(s)+1;
    t= malloc(n);
    if(t==NULL){
        fprintf(listing, "Out of memory error at line %d\n",lineno);
    } else{
        stpcpy(t, s);
    }
    return t;
}
