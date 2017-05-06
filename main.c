#include <stdio.h>

#include "globals.h"
#include "util.h"
#include "scan.h"

int lineno=0;
FILE* source;
FILE* listing;
FILE* code;

int EchoSource=FALSE;
int TraceScan=TRUE;

int Error=FALSE;

int main(int argc, const char * argv[]) {
    char* pgm="/Users/admin/Desktop/example.tiny";      
    //读取源文件
    source= fopen(pgm, "r");
    //判断读取是否出错
    if(source==NULL){
        fprintf(stderr, "File %s not found\n",pgm);
        exit(1);
    }
    //标准输出
    listing=stdout;                                     

    fprintf(listing, "\nTINY COMPLATION: %s\n",pgm);
    //词法分析
    while (getToken()!=ENDFILE);
    
    fclose(source);
    return 0;
}
