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
    file=fopen("C:\\data1.txt","r");//文件打开模式为read只读模式
    if(file==NULL){
        printf("fail to open the file!\n");
        return ;
    }
    char line[121];//存放一行的数据，最多不超过120
    int line_number=1;//行号，用以累加
    Line array[1000];//存放匹配成功的行号和出现次数
    int total_number=0;//总共出现次数
    int index=0;//array的下标，用于对array赋值
    while(fgets(line, sizeof(line),file)!=NULL){//每次获取一行的数据
        char word[121];
        int len=0;
        int number=0;
        while(sscanf(line,"%s",word)==1){//将获取的行数据写入到word中直到读取到空格符
            //printf("%s\n",word);
            if(strcmp(word,str)==0) {//字符串匹配，相等则匹配成功
                number++;            //当前行的次数+1
                total_number++;      //总次数+1
            }
            len=strlen(word);        //获取本字符串的长度用于将字符串指针向前移到下一个字符串开头
            strcpy(line,line+len+1);//字符串拷贝，将下一个字符串开始的内容复制到line所指向指针的位置
        }
        if(number){                  //当前行指定字符串出现次数不为0则存入到array数组中记录
            Line l;l.line_numer=line_number;l.number=number;
            array[index++]=l;        //数组下标+1
        }
        line_number++;
    }
    //输出所需内容
    printf("%s total appears:%d\n",str,total_number);//输出总次数
    for(int i=0;i<index;i++){
        printf("No.%d line appear %d times\n",array[i].line_numer,array[i].number);//输出匹配成功的每一行中出现的次数
    }
}
int main(){
    char word[100];
    gets(word);
    file_output(word);
    return 0;
}