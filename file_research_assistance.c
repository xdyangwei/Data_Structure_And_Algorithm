//
// Created by 杨炜 on 2019/10/30.
//
#include <stdio.h>
#include <string.h>
typedef struct Line{
    int line_numer;//行号
    int number;//这一行中匹配的字符串个数
}Line;

void file_output(const char* str){
    FILE* file=NULL;
    file=fopen("C:\\data1.txt","r");//
    if(file==NULL){
        printf("fail to open the file!\n");
        return ;
    }
    char line[121];int line_number=1;
    Line array[1000];
    int total_number=0;
    int index=0;
    while(fgets(line, sizeof(line),file)!=NULL){
        char word[121];
        int len=0;
        int number=0;
        while(sscanf(line,"%s",word)==1){
            //printf("%s\n",word);
            if(strcmp(word,str)==0) {
                number++;
                total_number++;
            }
            len=strlen(word);
            strcpy(line,line+len+1);
        }
        if(number){
            Line l;l.line_numer=line_number;l.number=number;
            array[index++]=l;
        }
        line_number++;
    }
    printf("%s total appears:%d\n",str,total_number);
    for(int i=0;i<index;i++){
        printf("No.%d line appear %d times\n",array[i].line_numer,array[i].number);
    }
}
int main(){
    char word[100];
    gets(word);
    file_output(word);
    return 0;
}