#ifndef _PARSE_H_
#define _PARSE_H_

#include "globals.h"
#include "util.h"
#include "scan.h"

static TokenType token;     //存储当前的记号
//递归调用的函数原型
static TreeNode* stmt_sequence(void);
static TreeNode* statement(void);
static TreeNode* if_stmt(void);
static TreeNode* repeat_stmt(void);
static TreeNode* assign_tmt(void);
static TreeNode* read_stmt(void);
static TreeNode* write_stmt(void);
static TreeNode* exp(void);
static TreeNode* simple_exp(void);
static TreeNode* term(void);
static TreeNode* factor(void);

//语法错误
static void syntaxError(char* message){
    fprintf(listing,"\n>>>");
    fprintf(listing,"Syntax error at line %d:%s",lineno,message);
    Error=TRUE;
}
static void match(TokenType expected){
    if(token==expected){
        token=getToken();
    }
    else{
        syntaxError("unexpected token -> ");
        printToken(token,tokenString);
        fprintf(listing,"      ");
    }
}
//函数实现

TreeNode* 

#endif