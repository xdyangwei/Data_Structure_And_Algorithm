//
// Created by 杨炜 on 2019/3/24.
//
#include <iostream>
#include <memory>
#include <cstring>
#include <bitset>
using namespace std;
//单字节拷贝实现memcpy函数
void *my_memcpy(void* dst,const void* src,int n){
    if(dst== nullptr||src== nullptr||n<=0)
        return nullptr;
    auto pdst= static_cast<char*>(dst);
    auto psrc= (char*)src;
    //const char* a="ss";
    //char* psrc= static_cast<char*>(src);
    //考虑内存重叠的情况，即dst目标位置在src的后n个地址之内
    //此时如果从头地址向尾地址赋值的话会破坏原来src中的内容，因此需要从尾地址向头地址赋值
    if(pdst>psrc&&pdst<psrc+n){
        pdst=pdst+n-1;
        psrc=psrc+n-1;
        while(n--){
            *(pdst--)=*(psrc--);
        }
    }else{
        while(n--){
            *(pdst++)=*(psrc++);
        }
    }
    return dst;
}

//实现strcpy函数，同上为了防止地址覆盖，可以直接使用
char* my_strcpy(char* dst,const char* src){
if(dst== nullptr||src== nullptr)
    return nullptr;
    auto x= static_cast<char*>(my_memcpy(dst,src,strlen(src)+1));
    return x;
}

//实现memset函数
void* my_memset(void* dst,int ch,size_t n){
    auto pdst= static_cast<char*>(dst);
    ch= static_cast<unsigned char>(ch);
    cout<<ch<<endl;
    while(n--){
        *((pdst++))=ch;
    }
    return dst;
}

//实现memmove函数,与之前实现了目标重叠的memcpy相同
void* my_memmove(void* dst,const void* src,size_t n){
    void* ret=dst;
    if(dst>src&&(char*)dst<(char*)src+n){
        dst=(char*)dst+n-1;
        src=(char*)src+n-1;
        while(n--){
            *(char*)dst=*(char*)src;
            dst=(char*)dst-1;
            src=(char*)src-1;
        }
    }else{
        while (n--){
        *(char*)dst=*(char*)src;
        dst=(char*)dst+1;
        src=(char*)src+1;}
    }
    return ret;
}

//实现strncpy函数，从原字符串复制到n个字符到现字符串
//若复制了n个字符还没到\0字符，则在dst所指字符串后面加上\0
char* my_strncpy(char* dst,const char* src,size_t n){
    auto x=min(strlen(src)+1,n);
    //cout<<x<<endl;
    auto y=(char*)my_memcpy(dst,src,x);
    int count=0;
    while(*y!='\0'){
       // cout<<*(y+count)<<endl;
        //y++;
        count++;
        if(count==n)
            break;
    }
    //cout<<count<<endl;
    if(count==n){
    *(y+count)='\0';
    }else{

        while(count!=n){
            *(y+count)='\0';
            count++;
        }
    }
    return y;
}

int main(){
    char a[]="aaaaaaaa";
//    cout<<(*y)<<endl;
allocator<char> aa;
auto p=aa.allocate(2);
    auto x=my_strncpy(p,a,1);
    while(*(x)!='\0'){
        cout<<*x<<endl;
        x=x+1;}
    //cout<<strlen(x)<<endl;
}