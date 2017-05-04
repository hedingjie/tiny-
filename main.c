//
//  main.c
//  tiny
//
//  Created by admin on 2017/4/10.
//  Copyright © 2017年 admin. All rights reserved.
//

#include <stdio.h>

#include "globals.h"

#define NO_PARSE FALSE
#define NO_ANALYZE FALSE

#define NO_CODE FALSE

#include "util.h"

#include "scan.h"

int lineno=0;
FILE* source;
FILE* listing;
FILE* code;

int EchoSource=TRUE;
int TraceScan=TRUE;

int Error=FALSE;

int main(int argc, const char * argv[]) {
    // insert code here...
    TreeNode* syntaxTree;
//    char pgm[120];
//    if(argc!=2){
//        fprintf(stderr, "usage: %s <filename>\n",argv[0]);
//        exit(1);
//    }
//    strcpy(pgm, argv[1]);
//    if(strchr(pgm, '.')==NULL)
//        strcat(pgm, '.tiny');
    char* pgm="/Users/admin/Desktop/example.tiny";
    source= fopen(pgm, "r");
    if(source==NULL){
        fprintf(stderr, "File %s not found\n",pgm);
        exit(1);
    }
    listing=stdout;
//    listing='/Users/admin/Desktop/examplers.txt';
    fprintf(listing, "\nTINY COMPLATION: %s\n",pgm);
//#if NO_PARSE
    while (getToken()!=ENDFILE);
//#endif
    fclose(source);
    return 0;
}
