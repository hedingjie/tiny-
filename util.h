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

TreeNode* newStmtNode(StmtKind);

TreeNode* newExpNode(ExpKind);

char* copyString(char*);

void printTree(TreeNode*);

#endif /* util_h */

//
//  util.c
//  tiny
//
//  Created by admin on 2017/4/10.
//  Copyright © 2017年 admin. All rights reserved.
//

#include "globals.h"

void printToken(TokenType token,const char* tokenString){
    switch (token) {
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
        case NUM:
            fprintf(listing, "NUM, VAL=%s\n",tokenString);break;
        case ID:
            fprintf(listing, "ID, NAME=%s\n",tokenString);break;
        case ERROR:
            fprintf(listing, "ERROR:%s\n",tokenString);break;
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
