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

TreeNode* newStmtNode(StmtKind kind){
    TreeNode* t=(TreeNode*) malloc(sizeof(TreeNode));
    int i;
    if(t==NULL){
        fprintf(listing, "Out of memory error at line %d",lineno);
    }
    else{
        for(i=0;i<MAXCHILDREN;i++){
            t->child[i]=NULL;
        }
        t->sibling=NULL;
        t->nodeKind=StmtK;
        t->kind.stmt=kind;
        t->lineno=lineno;
    }
    return t;
}

TreeNode* newExpNode(ExpKind kind){
    TreeNode*  t=(TreeNode* )malloc(sizeof(TreeNode));
    int i;
    if(t==NULL){
        fprintf(listing, "Out of memory error at line %d",lineno);
    }
    else{
        for(i=0;i<MAXCHILDREN;i++){
            t->child[i]=NULL;
        }
        t->sibling=NULL;
        t->nodeKind=ExpK;
        t->kind.exp=kind;
        t->lineno=lineno;
        t->type=Void;
    }
    return t;
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

/**
 * Variable indentno is used by printTree to
 * store current number of spaces to indent
 */

static indentno=0;

/*
 * macros to increase/decrease indentation
 */

#define INDENT indentno+=2
#define UNINDENT indentno-=2

/**
 * printSpace indents by printing spaces
 */

static void printSpaces(void){
    int i;
    for(i=0;i<indentno;i++){
        fprintf(listing, " ");
    }
}

/**
 * 打印语法树
**/

void printTree(TreeNode * tree){
    int i;
    INDENT;
    while(tree!=NULL){
        printSpaces();
        if(tree->nodeKind==StmtK){
            switch(tree->kind.stmt){
                case IfK:
                    fprintf(listing, "If\n");
                    break;
                case RepeatK:
                    fprintf(listing, "Repeat\n");
                    break;
                case AssignK:
                    fprintf(listing, "Assign to: %s\n",tree->attr.name);
                    break;
                case ReadK:
                    fprintf(listing, "Read: %s\n",tree->attr.name);
                    break;
                case WriteK:
                    fprintf(listing, "Write: %s\n",tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown ExpNode Kind\n");
                    break;
            }
        }
        else if(tree->nodeKind==ExpK){
            switch(tree->kind.exp){
                case OpK:
                    fprintf(listing, "Op: ");
                    printToken(tree->attr.op, "\0");
                    break;
                case ConstK:
                    fprintf(listing, "Const: %d",tree->attr.val);
                    break;
                case IdK:
                    fprintf(listing, "ID: %s",tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown ExpNode Kind\n");
                    break;
            }
        }
        else{
            fprintf(listing, "不明节点");
        }
        for(i=0;i<MAXCHILDREN;i++)
            printTree(tree->child[i]);
        tree=tree->sibling;
    }
    UNINDENT;
}
