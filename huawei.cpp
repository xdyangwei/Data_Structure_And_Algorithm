//
// Created by 杨炜 on 2019/6/21.
//
#include <iostream>
#include <bitset>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <map>

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

//写出一个程序，接受一个由字母和数字组成的字符串，
//和一个字符，然后输出输入字符串中含有该字符的个数。不区分大小写。
//思路：使用STL中的count的方法
int numbers_of_char(string str,char c){
    return count_if(str.begin(),str.end(),[=](char a){
        return tolower(c)==tolower(a);
    });
}

//去重加排序
//思路：考虑使用set
void deduplication_and_sort(){
    int n;
    while(cin>>n) {
        set<int> s;
        while (n--) {
            int x;
            cin >> x;
            s.insert(x);
        }
        for (auto ss:s) {
            cout << ss << endl;
        }
    }
}

//连续输入字符串，请按长度为8拆分每个字符串后输出到新的字符串数组；
//•长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
//思路：使用string的substr方法
void str_split(string str){
    if(str.size()<=8){
        str.insert(str.size(),8-str.size(),'0');
        cout<<str<<endl;
        return ;
    }
    vector<string> v;
    for(int i=0;i<str.size();i+=8){
        v.push_back(str.substr(i,8));
    }
    auto n=v.size();
    if(v[n-1].size()<=8){
        v[n-1].insert(v[n-1].size(),8-v[n-1].size(),'0');
    }
    for(auto xx:v){
        cout<<xx<<endl;
    }
}

//写出一个程序，接受一个十六进制的数值字符串，
//输出该数值的十进制字符串。（多组同时输入 ）
//思路：使用stoi函数的非默认参数版本
void hex_to_dec(){
    string s;
    while(cin>>s){
      //cin>>s;
        cout<<stoi(s, nullptr,16)<<endl;
    }
}

//功能:输入一个正整数，按照从小到大的顺序输出它的所有质数的因子（如180的质数因子为2 2 3 3 5 ）
//最后一个数后面也要有空格
//思路：从2开始看能否被输入的数整除，无需判断此数是否为质数，因为不是质数的话肯定能被2或者3整除不会循环到的
void getResult(long input){
    while (input!=1){
        for(int i=2;i<=input;i++){
            if(input%i==0){
                cout<<i<<" ";
                input/=i;
                break;
            }
        }
    }
}

//写出一个程序，接受一个正浮点数值，输出该数值的近似整数值。
//如果小数点后数值大于等于5,向上取整；小于5，则向下取整。
//思路：使用to_string()方法
void double_to_int(){
    double x;
    cin>>x;
    auto s=to_string(x);
    auto it=s.find(".");
    if(it==string::npos)
        cout<<x;
    else{
        auto y=s[it+1];
        if(y>='5')
            cout<<(int)x+1;
        else
            cout<<(int)x;
    }
}

//数据表记录包含表索引和数值，请对表索引相同的记录进行合并，
//即将相同索引的数值进行求和运算，输出按照key值升序进行输出。
//思路：使用map即可
void sum_of_value(){
    int n;
    cin>>n;
    map<int,int> m;
    while(n--){
        int index,value;
        cin>>index>>value;
        if(m.find(index)==m.end()){
            m[index]=value;
        }else{
            m[index]+=value;
        }
    }
    for(auto xx:m){
        cout<<xx.first<<" "<<xx.second<<endl;
    }
}

int main(){
    sum_of_value();
    return 0;
}