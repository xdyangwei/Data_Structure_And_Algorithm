//
// Created by 杨炜 on 2019/6/21.
//
#include <iostream>
#include <bitset>
#include <cmath>
#include <string>
using namespace std;

//输入一个int型的正整数，计算出该int型数据在内存中存储时1的个数。
//思路：使用bitset或者使用短除法
int one_numbers(int a){
    bitset<32> b(a);
    int count=0;
    for(int i=0;i<32;i++){
        if(b[i]==1)
            count++;
    }
    return count;
}

//与1、2、4这些2的次方进行位与运算
int one_numbers_2(int a){
    int count=0;
    for(int i=0;i<32;i++){
        if(a&static_cast<int>(pow(2,i)))
            count++;
    }
    return count;
}

//输入一个整数，将这个整数以字符串的形式逆序输出
//程序不考虑负数的情况，若数字含有0，则逆序形式也含有0，如输入为100，则输出为001
//思路：使用to_string方法
string int_to_str(int x){
   auto str=to_string(x);
   auto n=str.size();
   string s="";
   for(int i=n-1;i>=0;i--){
        s+=str[i];
   }
   return s;
}

//计算字符串最后一个单词的长度，单词以空格隔开。
//思路：使用string的rfind方法
int length_of_last_str(string str){
    auto x=str.rfind(" ");
    if(x==string::npos)
        return str.size();
    return str.size()-x-1;
}


int main(){
    string s;
    getline(cin,s);
    cout<<length_of_last_str(s);
    return 0;
}