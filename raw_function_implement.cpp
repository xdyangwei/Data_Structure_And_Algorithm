//
// Created by 杨炜 on 2019/3/24.
//
#include <iostream>
#include <memory>
#include <cstring>
#include <bitset>
#include <mutex>
#include <vector>
#include <algorithm>

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

//饿汉式单例模式
class Singlton{
public:
    static Singlton* getInstance();
private:
    Singlton(){};
    static Singlton* instance;
};
Singlton* Singlton::getInstance(){
    return instance;
}
Singlton* Singlton::instance=new Singlton();

//懒汉式单例模式
//线程不安全，线程安全需要加锁
class Singlton_2{
public:
    static Singlton_2* getInstance();
private:
    Singlton_2(){};
    static Singlton_2* instance;
};

Singlton_2* Singlton_2::instance= nullptr;
Singlton_2* Singlton_2::getInstance() {
    //if(instance== nullptr) {
        //unique_lock<mutex> u;
        if (instance == nullptr)
            instance = new Singlton_2();
      //  u.unlock();
    //}
    return instance;
}

//二分查找循环版本
void binary_search(vector<int>& v,int k){
    sort(v.begin(),v.end());
    int start=0,end=v.size()-1;
    int flag=-1;
    while(start<end){
        int mid=(start+end)/2;
        if(v[mid]==k){
            flag=mid;break;
        }else if(v[mid]>k){
            end=mid;
        }else{
            start=mid;
        }
    }
    cout<<flag<<endl;
}

//二分查找递归版本
int binary_search_recursive(vector<int>& v,int k,int start,int end){
    if(start<end){
        int mid=(start+end)/2;
        if(v[mid]==k)
            return mid;
        else if(v[mid]<k)
            return binary_search_recursive(v,k,mid,end);
        else
            return binary_search_recursive(v,k,start,mid);
    }else{
        return -1;
    }
}

int main(){
    vector<int> v{1,2,3,4,5};
    cout<<binary_search_recursive(v,2,0,4);
}