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
#include <sstream>
#include <tuple>
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

//输入一个int型整数，按照从右向左的阅读顺序，
//返回一个不含重复数字的新的整数。
//思路：使用辅助数组即可
void de_duplicate(){
    int x;
    cin>>x;
    auto s=to_string(x);
    auto n=s.size();
    vector<int> v(10,-1);
    string str="";
    for(int i=n-1;i>=0;i--){
        if(v[s[i]-'0']==-1) {
            str += to_string(s[i]-'0');
            v[s[i]-'0']=0;
        }
    }
    cout<<str;
}

//编写一个函数，计算字符串中含有的不同字符的个数。
//字符在ACSII码范围内(0~127)。不在范围内的不作统计。
//思路：使用辅助数组
void different_number(){
    string s;
    cin>>s;
    vector<int> v(128,-1);
    auto n=s.size();
    int count=0;
    for(int i=0;i<n;i++){
        if(v[s[i]]==-1){
            count++;
            v[s[i]]=0;
        }
    }
    cout<<count<<endl;
}

//写出一个程序，接受一个字符串，然后输出该字符串反转后的字符串。
//使用栈或者STL中的reverse方法
void str_reverse(){
    string s;cin>>s;
    reverse(s.begin(),s.end());
    cout<<s<<endl;
}

//将一个英文语句以单词为单位逆序排放。例如“I am a boy”，逆序排放后为“boy a am I”
//所有单词之间用一个空格隔开，语句中除了英文字母外，不再包含其他字符
//思路：使用getline和STL中的reverse
void str_reverse_without_word(){
    string s;
    getline(cin,s);
    reverse(s.begin(),s.end());
    stringstream s1(s);
    string ss;
    string str="";
    while(s1>>ss){
        reverse(ss.begin(),ss.end());
        str+=(" "+ss);
    }
    str.erase(str.begin());
    cout<<str;
}

//给定n个字符串，请对n个字符串按照字典序排列。
//思路：使用sort函数即可
void str_sort(){
    int n;cin>>n;
    vector<string> v;
    while(n--){
        string s;
        cin>>s;
        v.push_back(s);
    }
    sort(v.begin(),v.end());
    for(auto xx:v){
        cout<<xx<<endl;
    }
}

//开发一个简单错误记录功能小模块，能够记录出错的代码所在的文件名称和行号。
//处理：
//1、 记录最多8条错误记录，循环记录，对相同的错误记录（净文件名称和行号完全匹配）只记录一条，错误计数增加；
//2、 超过16个字符的文件名称，只记录文件的最后有效16个字符；
//3、 输入的文件可能带路径，记录文件名称不能带路径。
//思路：使用string的各种操作以及STL里的find_if算法
string get_filename(string str){
    auto x=str.rfind("\\");
    if(x==string::npos)
        return str;
    else
        return str.substr(x+1);
}
void mistake_log(){
    vector<tuple<string,int,int>> log;
    string s;
    while(getline(cin,s)){
        auto it=s.find(" ");
        auto filename=s.substr(0,it);
        auto number=stoi(s.substr(it+1));
        auto x=find_if(log.begin(),log.end(),[filename,number](tuple<string,int,int> t1){
            return get_filename(get<0>(t1))==get_filename(filename)&&get<1>(t1)==number;
        });
        if(x==log.end()){
            log.push_back(make_tuple(filename,number,1));
        }else{
            get<2>(*x)+=1;
        }
    }
    int j=0;
    if(log.size()>8)
        j=log.size()-8;
    for(int i=j;i<log.size();i++){
        auto ss=get<0>(log[i]);
        auto it1=ss.rfind("\\");
        if(it1==string::npos){
            if(ss.size()<=16)
                cout<<ss<<" ";
            else
                cout<<ss.substr(ss.size()-16)<<" ";
        }else{
            auto sss=ss.substr(it1+1);
            if(sss.size()<=16)
                cout<<sss<<" ";
            else
                cout<<sss.substr(sss.size()-16)<<" ";
        }
        cout<<get<1>(log[i])<<" "<<get<2>(log[i])<<endl;
    }
}

int main(){
   mistake_log();
    return 0;
}