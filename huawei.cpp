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

//密码要求:
//1.长度超过8位
//2.包括大小写字母.数字.其它符号,以上四种至少三种
//3.不能有相同长度超2的子串重复
void passwd_verify(){
    string s;
    while(cin>>s){
        if(s.size()<=8)
            cout<<"NG"<<endl;
        else{
            int count=0;
            auto it=find_if(s.begin(),s.end(),[](char c){
                return c>='0'&&c<='9';
            });
            if(it!=s.end())
                count++;
            auto it1=find_if(s.begin(),s.end(),[](char c){
                return c>='a'&&c<='z';
            });
            if(it1!=s.end())
                count++;
            auto it2=find_if(s.begin(),s.end(),[](char c){
                return c>='A'&&c<='Z';
            });
            if(it2!=s.end())
                count++;
            auto it3=find_if(s.begin(),s.end(),[](char c){
                return (c<'0'||c>'9')&&(c<'a'||c>'z')&&(c<'A'||c>'Z');
            });
            if(it3!=s.end())
                count++;
            if(count<3)
                cout<<"NG"<<endl;
            else{
                map<string,int> ss;bool flag=true;
                for(int i=0;i<s.size()-2;i++){
                    auto str=s.substr(i,3);
                    if(ss.find(str)!=ss.end()&&ss[str]!=i-2&&ss[str]!=i-1){
                        flag= false;
                        break;
                    }else{
                        ss.insert(make_pair(str,i));
                    }
                }
                if(flag==true)
                    cout<<"OK"<<endl;
                else
                    cout<<"NG"<<endl;
            }
        }
    }
}

//开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。
//从（0,0）点开始移动，从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。
//输入：
//合法坐标为A(或者D或者W或者S) + 数字（两位以内）
//思路：进行坐标正确性判断
pair<int,int> move_one_step(string s,pair<int,int> p){
    //cout<<s[0]<<endl;
    if(s.size()<=1||s.size()>3||(s[0]!='A'&&s[0]!='S'&&s[0]!='W'&&s[0]!='D'))
        return p;
    else{
        bool flag=true;
        for(int i=1;i<s.size();i++){
            if(s[i]<'0'||s[i]>'9'){
                flag= false;break;
            }
        }
        //cout<<flag<<endl;
        if(!flag)
            return p;
        auto x=stoi(s.substr(1));
        if(s[0]=='A'){
            auto pp=p;pp.first-=x;
            return pp;
        }else if(s[0]=='W'){
            auto pp=p;pp.second+=x;
            return pp;
        }else if(s[0]=='S'){
            auto pp=p;pp.second-=x;
            //cout<<pp.first<<" "<<pp.second<<endl;
            return pp;
        }else{
            auto pp=p;pp.first+=x;
            return pp;
        }
    }
}

void move(){
    string s;
    cin>>s;
    auto start=0;
    auto it=s.find(";");
    pair<int,int> p(0,0);
    while(it!=string::npos){
        auto ss=s.substr(start,it-start);
        p=move_one_step(ss,p);
        //cout<<p.first<<" "<<p.second<<endl;
        start=it+1;
        it=s.find(";",it+1);
    }
    cout<<p.first<<","<<p.second<<endl;
}


//请解析IP地址和对应的掩码，进行分类识别。要求按照A/B/C/D/E类地址归类，不合法的地址和掩码单独归类。
//子网掩码为前面是连续的1，然后全是0。（例如：255.255.255.32就是一个非法的掩码）
//本题暂时默认以0开头的IP地址是合法的，比如0.1.1.2，是合法地址
bool mask_judge(string s){
    auto it=find(s.begin(),s.end(),'0');
    if(find(it,s.end(),'1')!=s.end())
        return false;
    return true;
}

int ip_address_judge(string s){
    auto it=s.find("~");
    auto ip=s.substr(0,it);
    auto mask=s.substr(it+1);
    if(ip>="1.0.0.0"&&ip<="126.255.255.255"&&ip.substr(0,2)!="10"&&mask_judge(mask)){
        return 0;
    }else if(ip>="128.0.0.0"&&ip<="191.255.255.255"&&(ip<"172.16.0.0"||ip>"172.31.255.255")&&mask_judge(mask)){
        return 1;
    }else if(ip>="192.0.0.0"&&ip<="223.255.255.255"&&(ip<"192.168.0.0"||ip>"192.168.255.255")&&mask_judge(mask)){
        return 2;
    }else if(ip>="224.0.0.0"&&ip<="239.255.255.255"&&mask_judge(mask)){
        return 3;
    }else if(ip>="240.0.0.0"&&ip<="255.255.255.255"&&mask_judge(mask)){
        return 4;
    }else if((ip>="10.0.0.0"&&ip<="10.255.255.255")||(ip>="172.16.0.0"&&ip<="172.31.255.255")||(ip>="192.168.0.0"&&ip<="192.168.255.255")&&mask_judge(mask)){
        return 6;
    }else if(ip>="0.0.0.0"&&ip<="0.255.255.255"&&mask_judge(mask)){
        return 10;
    }else{
        return 5;
    }
}

void ip_address_classify(){
    string s;
    vector<int> v(6,0);
    int i=0;
    while(i++<4){
        cin>>s;
        if(ip_address_judge(s)<=v.size()-1)
            v[ip_address_judge(s)]+=1;
    }
    for(auto xx:v){
        cout<<xx<<" ";
    }
}

//简单密码
//简单的字符替换即可
void simple_password(){
    string s;
    while(cin>>s){
        string s1="";
        for(auto xx:s){
            if(xx>=65&&xx<=90){
                if(xx==90)
                    s1+='a';
                else
                    s1+=(xx+33);
            }else if(xx>=97&&xx<=122){
                char c;
                if(xx=='s')
                    c=7;
                else if(xx<='r')
                    c=(xx-97)/3+2;
                else if(xx!='z')
                    c=(xx-116)/3+8;
                else
                    c=9;
                s1+=to_string(c);
            } else
                s1+=xx;
        }
        cout<<s1<<endl;
    }
}

//实现删除字符串中出现次数最少的字符，
//若多个字符出现次数一样，则都删除。输出删除这些单词后的字符串，
//字符串中其它字符保持原来的顺序。
//思路：遍历字符串
void delete_least_char(){
    string s;
    while(cin>>s){
        map<char,int> m;
        for(auto ss:s){
            if(m.find(ss)!=m.end())
                m[ss]+=1;
            else
                m[ss]=1;
        }
        set<char> v;
        int count=s.size();
        for(auto mm:m){
            if(mm.second<count){
                v.clear();
                v.insert(mm.first);
                count=mm.second;
            }else if(mm.second==count)
                v.insert(mm.first);
        }
        for(auto i=0;i<s.size();i++){
            if(v.find(s[i])!=v.end()){
                s.erase(s.begin()+i);
                i--;
            }
        }
        cout<<s<<endl;
    }
}

//兑换汽水瓶
void transfer_bottle(){
    int n;
    while(cin>>n){
        int Count=0;
        while(n>=3){
            auto x=n/3;
            auto y=n%3;
            Count+=x;
            n-=(3*x);
            n+=x;
        }
        if(n==2)
            Count+=1;
        cout<<Count<<endl;
    }
}

//合唱队
void sing_and_song(){
    int n;
    while(cin>>n){
        vector<int> v;
        while(n--){
            int x;cin>>x;
            v.push_back(x);
        }
        int Count=v.size();
        for(int i=0;i<v.size();i++){
            int count=0;
            for(int j=0;j<i;j++){
                if(v[j]>=v[j+1])
                    count++;
            }
            for(int j=i+1;j<v.size();j++){
                if(v[j]<=v[j-1])
                    count++;
            }
                Count=min(count,Count);
        }
        cout<<Count<<endl;
    }
}

//放苹果
//把M个同样的苹果放在N个同样的盘子里，允许有的盘子空着不放，
//问共有多少种不同的分法？（用K表示）5，1，1和1，5，1 是同一种分法。
static set<vector<int>> distribution;
void apple_count(int m,int n,vector<int>& v){
    if(m==0&&n<=v.size()){
        auto x=v;
        sort(x.begin(),x.end());
        distribution.insert(x);
    }else if(m>0&&n==v.size()){
      return ;
    }else{
        for(int i=0;i<=m;i++){
            v[n]=i;
            apple_count(m-i,n+1,v);
            v[n]=0;
        }
    }
}

void apple(){
    int m,n;
    while(cin>>m>>n){
        vector<int> v(n,0);
        apple_count(m,0,v);
        cout<<distribution.size()<<endl;
        distribution.clear();
    }
}

//杨辉三角的变形
//以上三角形的数阵，第一行只有一个数1，以下每行的每个数，是恰好是它上面的数，左上角数到右上角的数，3个数之和（如果不存在某个数，认为该数就是0）。
//求第n行第一个偶数出现的位置。如果没有偶数，则输出-1。例如输入3,则输出2，输入4则输出3。
void triangle_sum(){
    int n;
    while(cin>>n){
        vector<vector<int>> v(n+1,vector<int>());
        v[1].push_back(1);
        for(int i=2;i<=n;i++){
            for(int j=0;j<v[i-1].size()+2;j++){
                int x=v[i-1].size();
                auto y=(j-2>=0?v[i-1][j-2]:0)+(j-1>=0&&j-1<x?v[i-1][j-1]:0)+(j<x?v[i-1][j]:0);
                v[i].push_back(y);
            }
        }
        for(int i=1;i<v[n].size();i++){
            if((v[n][i]&0x1)==0) {
                cout << i+1 << endl;
                break;
            }
        }
    }
}

//计算整数二进制中1的个数
//使用biteset
void number_of_one_binary(){
    int num;
    while(cin>>num){
        bitset<32> b(num);
        int Count=0;
        for(int i=0;i<32;i++){
            if(b[i]==1)
                Count++;
        }
        cout<<Count<<endl;
    }
}

//编写一个截取字符串的函数，输入为一个字符串和字节数，输出为按字节截取的字符串。
//但是要保证汉字不被截半个，如"我ABC"4，应该截为"我AB"，输入"我ABC汉DEF"6，
//应该输出为"我ABC"而不是"我ABC+汉的半个"。
//使用string判断每个字符
void str_intercept(){
    string s;int num;
    while(cin>>s>>num){
        string str="";
        for(int i=0;i<s.size()&&num>=1;){
            if((s[i]>=65&&s[i]<=90)||(s[i]>=97&&s[i]<=122)){
                str+=s[i];num-=1;i++;
            }
            else{
                if(num<=1)
                    break;
                else
                {
                    cout<<s[i]<<endl;
                    str+=(string(s.begin()+i,s.begin()+1));num-=2;i+=1;
                }
            }
        }
        cout<<str<<endl;
    }
}

//字符串合并处理，将输入的两个字符串合并。
//对合并后的字符串进行排序，要求为：下标为奇数的字符和下标为偶数的字符分别从小到大排序。
void SortString(string &s){
    string s1="";
    string s2="";
    for(int i=0;i<s.size();i++){
        if(i&0x1){
            s1+=s[i];
        }else{
            s2+=s[i];
        }
    }
    sort(s1.begin(),s1.end());sort(s2.begin(),s2.end());
    for(int i=0,j=0,k=0;i<s.size();i++){
        if(i&0x1){
            s[i]=s1[j];j++;
        }else{
            s[i]=s2[k];k++;
        }
    }
}

char TransferChar(char a,char b){
    int x;
    if(b=='0')
        x=a-'0';
    else if(b=='a')
        x=a-'a'+10;
    else
        x=a-'A'+10;
    bitset<4> b1(x);
    int i=0,j=3;
    while(i<j){
        int y=b1[i];
        b1[i]=b1[j];
        b1[j]=y;
        i++;j--;
    }
    if(b=='0'&&b1.to_ulong()<10)
        return b1.to_ulong()+'0';
    else if(b1.to_ulong()<10)
        return b1.to_ulong()+'0';
    else{
        return b1.to_ulong()-10+'A';
    }
}

void TransferString(string &s){
    for(int i=0;i<s.size();i++){
        if(s[i]>='0'&&s[i]<='9'){
            s[i]=TransferChar(s[i],'0');
        }else if(s[i]>='A'&&s[i]<='F')
            s[i]=TransferChar(s[i],'A');
        else if(s[i]>='a'&&s[i]<='f')
            s[i]=TransferChar(s[i],'a');
        else{
            continue;
        }
    }
}

void ProcessString(string s1,string s2){
    auto s=s1+s2;
    SortString(s);
    TransferString(s);
    cout<<s<<endl;
}

//密码截取，最长对称子串
void max_symmetrical_substring(string s){
    vector<int> v;
    for(int i=0;i<s.size();i++){
        int j=i,k=i+1,tmp=0;
        if(j>=0&&k<s.size()&&s[j]!=s[k])
            tmp=1;
        else if(j<0||k>=s.size()){
            tmp=1;
        }else {
            while (j>=0&&k<s.size()){
                if(s[j]==s[k]){
                j--;k++;}
                else
                    break;
            }
            tmp=max(tmp,k-j-1);
        }
        j=i-1,k=i+1;int tmp1=0;
        if(j>=0&&k<s.size()&&s[j]!=s[k])
            tmp1=1;
        else if(j<0||k>=s.size()){
            tmp1=1;
        }else {
            while (j>=0&&k<s.size()){
                if(s[j]==s[k]){
                    j--;k++;}
                else
                    break;
            }
            tmp1=max(tmp1,k-j-1);
        }
        v.push_back(max(tmp,tmp1));
    }
    int Max=0;
    for(auto xx:v)
        Max=max(xx,Max);
    cout<<Max<<endl;
}

//单词倒排
void Reverse_String(){
    string s;
    while(getline(cin,s)){
        for(auto &xx:s){
            if(xx<'A'||(xx>'Z'&&xx<'a')||xx>'z')
                xx=' ';
        }
        stringstream s1(s);
        string str;vector<string> v;
        while(s1>>str){
            v.push_back(str);
        }
        string ss="";
        for(auto i=v.rbegin();i<v.rend();i++){
            ss+=(*i);
            ss+=" ";
        }
        ss.erase(ss.end()-1);
        cout<<ss<<endl;
    }
}

//整数与IP地址间转换

vector<string> str_split1(string s){
    vector<string> v;
    auto start=s.begin();
    while(find(start,s.end(),'.')!=s.end()){
        auto it=find(start,s.end(),'.');
        string s1(start,it);
        v.push_back(s1);
        start=it+1;
    }
    v.push_back(string(start,s.end()));
    return v;
}

string int_to_ip(string s){
    string ss;
    auto s1=s.substr(0,8);
    bitset<8> b1(s1);
    ss+=to_string(b1.to_ulong());
    ss+=".";
    auto s2=s.substr(8,8);
    bitset<8> b2(s2);
    ss+=to_string(b2.to_ulong());
    ss+=".";
    auto s3=s.substr(16,8);
    bitset<8> b3(s3);
    ss+=to_string(b3.to_ulong());
    ss+=".";
    auto s4=s.substr(24,8);
    bitset<8> b4(s4);
    ss+=to_string(b4.to_ulong());
    return ss;
}

void int_transfer_ip(){
    string ip_str,ip_int;
    while(cin>>ip_str>>ip_int){
        auto v=str_split1(ip_str);
        string s1;
        for(auto xx:v){
            bitset<8> b(stoi(xx));
            s1+=b.to_string();
        }
        bitset<32> b1(s1);
        cout<<b1.to_ulong()<<endl;
        bitset<32> b2(stoi(ip_int));
        cout<<int_to_ip(b2.to_string())<<endl;
    }
}

//把这些图片按照大小（ASCII码值从小到大）排列收好
//使用sort函数
void picture_sort(){
    string s;
    while(cin>>s){
        sort(s.begin(),s.end());
        cout<<s<<endl;
    }
}

//蛇形矩阵是由1开始的自然数依次排列成的一个矩阵上三角形。
//找规律
void print_row(set<int>& v,int n,int m){
    auto x=(*v.begin());
    for(int i=0;i<n;i++){
        cout<<x<<" ";
        v.erase(x);
        x+=(m++);
    }
    cout<<endl;
}
void snake_rectangle(){
    int n;
    while(cin>>n){
        int x=n,y=1;
        set<int> v;
        while(x){
            for(int i=1;i<=x;i++){
                v.insert(y++);
            }
            x--;
        }
        int z=n;
        for(int i=0;i<n;i++){
            print_row(v,z,n-z+2);
            z--;
        }
    }
}

void str_encryption(){
    string key,str;
    while(cin>>key>>str){
        set<char> s;
        string ss="";
        for(int i=0;i<key.size();i++){
            if(s.find(key[i])==s.end()){
                s.insert(key[i]);
                ss+=string(1,key[i]);
            }else{
                continue;
            }
        }
        //cout<<ss<<endl;
        for(char c='A';c<='Z';c++){
            if(s.find(c)==s.end()&&s.find(c+32)==s.end())
                ss+=c;
        }
        map<char,char> m;int i=0;
        for(char c='A';c<='Z';c++){
            if(ss[i]>='a'&&ss[i]<='z') {
                m[c+32] = ss[i];
                i++;
            }else{
            m[c]=ss[i++];
            m[c+32]=m[c]+32;}
        }
        string sss="";
        for(auto xx:str){
            sss+=m[xx];
        }
        cout<<sss<<endl;
    }
}

//称砝码，使用递归时间复杂度过大，尝试使用迭代
void sum_of_fama(int n,vector<int> &v,vector<int> &v1,int &count,set<int>& sum){
    if(n<v.size()){
        for(int i=0;i<=v1[n];i++){
            auto x=count;
            count+=v[n]*i;
            sum_of_fama(n+1,v,v1,count,sum);
            count=x;
        }
    } else{
        sum.insert(count);
        }
}

void fama(){
    int n;
    while(cin>>n){
        int n1=n;
        vector<int> v;
        while(n1--){
            int x;
            cin>>x;
            v.push_back(x);
        }
        n1=n;
        vector<int> v1;
        while(n1--){
            int x;cin>>x;v1.push_back(x);
        }
        int count=0;
        set<int> sum;
        sum_of_fama(0,v,v1,count,sum);
        cout<<sum.size()<<endl;//递归代码,复杂度超限
    }
}

//使用动态规划求解称砝码问题
void fama_1(){
    int n;
    while(cin>>n){
        int n1=n;
        vector<int> v;
        while(n1--){
            int x;
            cin>>x;
            v.push_back(x);
        }
        n1=n;
        vector<int> v1;int sum=0;
        while(n1--){
            int x;cin>>x;
            v1.push_back(x);
        }
        for(int i=0;i<n;i++)
            sum+=(v1[i]*v[i]);
        vector<int> dp(sum+1,0);
        dp[0]=1;
        for(int i=0;i<n;i++){
            for(int j=0;j<v1[i];j++){
                for(int k=sum;k>=v[i];k--){
                    if(dp[k-v[i]]==1)
                        dp[k]=1;
            }
        }
        }
        int Count=0;
        for(auto xx:dp){
            if(xx==1)
                Count+=1;
        }
        cout<<Count<<endl;
    }
}

//字符统计，输入一行字符，分别统计出包含英文字母、空格、数字和其它字符的个数。
void str_judge(){
    string str;
    while(getline(cin,str)){
        int word=0,space=0,number=0,other=0;
        for(auto xx:str){
            if((xx>='A'&&xx<='Z')||(xx>='a'&&xx<='z')){
                word+=1;
            }else if(xx==' ')
                space+=1;
            else if(xx>='0'&&xx<='9')
                number+=1;
            else
                other+=1;
        }
        cout<<word<<endl;
        cout<<space<<endl;
        cout<<number<<endl;
        cout<<other<<endl;
    }
}

//学英语，为了快速读出一串数字，编写程序将数字转换成英文
static map<char,string> mm1{{'2',"twenty"},{'3',"thirty"},{'4',"forty"},{'5',"fifty"},{'6',"sixty"},{'7',"seventy"},{'8',"eighty"},{'9',"ninty"}};
static map<string,string> mm2{{"10","ten"},{"11","eleven"},{"12","twelve"},{"13","thirteen"},{"14","fourteen"},{"15","fifteen"},{"16","sixteen"},{"17","seventeen"},{"18","eighteen"},{"19","ninteen"}};
static map<char,string> mm3{{'1',"one"},{'2',"two"},{'3',"three"},{'4',"four"},{'5',"five"},{'6',"six"},{'7',"seven"},{'8',"eight"},{'9',"nine"},{'0',""}};
static bool flag=1;
void recursive_parse(string s){
    if(s.empty())
        return ;
    else{
        if(s.size()<=9&&s.size()>=7){
            int index=0;
            if(s.size()==7)
                index=1;
            else if(s.size()==8)
                index=2;
            else
                index=3;
            recursive_parse(s.substr(0,index));
            if(s[0]!='0')
            cout<<"million"<<" ";
            recursive_parse(s.substr(index));
        }else if(s.size()<=6&&s.size()>=4){
            int index=0;
            if(s.size()==4)
                index=1;
            else if(s.size()==5)
                index=2;
            else
                index=3;
            recursive_parse(s.substr(0,index));
            if(s[0]!='0')
            cout<<"thousand"<<" ";
            recursive_parse(s.substr(index));
        }else if(s.size()==3){
            recursive_parse(s.substr(0,1));
            if(s[0]!='0'){
                cout<<"hundred"<<" ";
            }else
                flag=false;
            recursive_parse(s.substr(1));
        }else if(s.size()==2){
            if(s[0]!='0'||s[1]!='0') {
                if(flag==true)
                cout << "and ";
            }
            if(s[0]>='2') {
                //cout<<s[1]<<endl;
                cout << mm1[s[0]] << " ";
                recursive_parse(s.substr(1, 1));
            }
            else if(s[0]=='1'){
                cout<<mm2[s]<<" ";
            }else{
                recursive_parse(s.substr(1, 1));
            }

        }else{
            cout<<mm3[s[0]]<<" ";
        }

    }
}

void parse(){
    long number;
    while(cin>>number){
        auto s=to_string(number);
        if(s.size()<=2)
            flag= false;
        if(s.size()<=9)
            recursive_parse(s);
        else
            cout<<"error";
        cout<<endl;
    }
}

void beautify_of_one(string name){
    vector<pair<char,int>> v;
    for(auto xx:name){
        auto it=find_if(v.begin(),v.end(),[=](pair<char,int> p){
            return p.first==xx||p.first==xx-32?true: false;
        });
        if(it==v.end()){
            if(xx<='Z'&&xx>='A')
                v.push_back(make_pair(xx+32,1));
            else
                v.push_back(make_pair(xx,1));
        }else{
            (*it).second+=1;
        }
    }
    sort(v.begin(),v.end(),[](pair<char,int> p1,pair<char,int> p2){
        return p1.second>p2.second?true: false;
    });
    int Count=0;
    for(int i=0;i<v.size();i++){
        Count+=((26-i)*v[i].second);
    }
    cout<<Count<<endl;
}

void beautity_of_name(){
    int n;
    cin>>n;
    string name;
    vector<string> v;
    while(n--){
        cin>>name;
        v.push_back(name);
    }
    for(auto xx:v){
        beautify_of_one(xx);
    }
}

//线性插值
void linear_insert(){
    int m, n;
    while (cin >> m >> n)
    {
        int M, N, A, B;
        cin >> M >> A;
        cout << M << " " << A << endl;
        for (int i = 1; i < m; ++i)
        {
            cin >> N >> B;
            if (N == M) continue;
            else
            {
                // 不连续，在M-N之间插值
                for (int j = 1; j < N - M; ++j)
                {
                    cout << M + j << " " << A + ((B - A) / (N - M))*j << endl;
                }
                cout << N << " " << B << endl;
                M = N;
                A = B;
            }
        }
    }
}

int main(){
    linear_insert();
    return 0;
}