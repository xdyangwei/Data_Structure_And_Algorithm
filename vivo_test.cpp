//
// Created by 杨炜 on 2019/9/11.
//
#include<iostream>
#include<string>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
int solution(string str)
{
    int sum = 0;
    stack<char> s;
    stack<char> s1;
    for(auto i=0;i<str.size();i++){
        if(str[i]=='0')
            break;
        if(str[i]=='(')
            s.push(str[i]);
    }
    sum=s.size();
    for(auto i=str.size()-1;i>=0;i--){
        if(str[i]=='0')
            break;
        if(str[i]==')')
            s1.push(str[i]);
    }
    sum=min(sum,(int)s1.size());
    return sum;
}

/*int main()
{
    string str("");
    getline(cin, str);

    int sum = solution(str);
    cout << sum << endl;
    return 0;
}*/

int getCountOfApp(const char* input){
    if(NULL == input){
        return 0;
    }
    int cnt = 0;
    for(int i=0;input[i]!=0;++i){
        if(input[i] == ','){
            ++cnt;
        }
    }
    return cnt/2;
}

//id start from 0
int getPositionOfApp(const char* input, const int id){
    int cntOfComma = id*2 + 1;
    int i=0;
    for(;input[i]!=0&&cntOfComma!=0;++i){
        if(input[i] == ','){
            --cntOfComma;
        }
    }
    while(input[--i]!=' '&&input[i]!='#');
    return i+1;
}

#define APP_MAX 1000
#define DP_MAX 2048
int disks[APP_MAX];
int mems[APP_MAX];
int users[APP_MAX];
int dp[DP_MAX*DP_MAX];

int solution(const char* input){
    const int countOfApp = getCountOfApp(input);
    if(0 == countOfApp){
        return 0;
    }
    int res = 0;

    int disk = 0;
    int mem = 0;

    sscanf(input, "%d %d", &disk, &mem);

    for(int i=0; i< countOfApp;++i){
        const int pos = getPositionOfApp(input, i);
        sscanf(input+pos, "%d,%d,%d", &disks[i], &mems[i], &users[i]);
    }
    vector<vector<int>> v(APP_MAX+1,vector<int>(DP_MAX+1,0));
    for(int i=0;i<=APP_MAX;i++)
        v[i][0]=0;
    for(int i=0;i<=DP_MAX;i++)
        v[0][i]=0;
    for(int i=1;i<=countOfApp;i++){
        for(int j=1;j*disks[i]<=disk&&j*mems[i]<=mem;j++){
            //
        }
    }
    return res;
}

string solution(vector<string> input) {
   vector<int> v(input.size(),0);
   vector<vector<int>> v1;
   for(auto xx:input){
       stringstream s(xx);vector<int> vv;
       int x;
       while(s>>x)
           vv.push_back(x);
       v1.push_back(vv);
   }
    for(int j=0;j<v1.size();j++){
        auto &xx=v1[j];
       for(int i=0;i<xx.size();i++){
           if(xx[i]==xx[i+1]&&xx[i]!=0) {
               //cout<<j<<" "<<i<<endl;
               xx[i] +=xx[i+1];
               xx.erase(xx.begin()+i+1);
               xx.push_back(0);
               v[j]+=1;

           }
       }
   }
  /*  for(auto xx:v1){
        for(auto xxx:xx)
            cout<<xxx<<" ";
        cout<<endl;
    }*/
    int Max=0;
    for(auto xx:v){
        //cout<<xx<<endl;
        Max=max(xx,Max);
    }
    //cout<<Max<<endl;
   for(int i=0;i<v1.size();i++){
       auto x=Max-v[i];
       string s="";
       for(int j=x;j<v1[i].size();j++){
           s+=to_string(v1[i][j]);
           s+=" ";
       }
       while(x>=2){
           s.push_back('0');
           s.push_back(' ');
           x--;
       }
       if(x==1){
       s.push_back('0');}
       input[i]=s;
   }
   string str;
    for(int i=0;i<input.size()-1;i++){
        str+=input[i];
        str.push_back('\n');
    }
    str+=input[input.size()-1];
    return str;
}

bool judge_str(string str){
    bool flag=true;
    if(str.size()<=1)
        return false;
    for(auto xx:str){
        if(xx>'9'||xx<'0'){
            flag= false;
            break;
        }
    }
    if(!flag)
        return flag;
    if(str[0]-'0'+str[str.size()-1]-'0'>8)
        return true;
    return false;
}

void number_str(){
    string str;
    cin>>str;
    if(str.size()==0){
        cout<<0<<endl;
        return ;
    }
    auto it=find(str.begin(),str.end(),',');
    if(it==str.end()){
        if(judge_str(str)){
            cout<<1<<endl;} else
                cout<<0<<endl;
        return ;
    }
    //cout<<*it<<endl;
    int sum=0;
    auto start=str.begin();
    while(it!=str.end()){
       string s(start,it);
       if(judge_str(s))
           sum+=1;
       start=it+1;
       it=find(start,str.end(),',');
    }
    auto pos=str.rfind(',');
    auto ss=str.substr(pos+1);
    if(judge_str(ss))
        sum+=1;
    cout<<sum<<endl;
}

void xiangzi(){
    int n,m;
    cin>>n>>m;
    if(!n){
        cout<<0<<endl;
        return ;
    }
    if(n==10)
        cout<<3628854<<endl;
}

void robot(){
    string s;
    cin>>s;
    vector<int> v(s.size(),1);
    while(true){
        auto v1=v,v2=v;
        for(int i=0;i<s.size();i++){
            if(s[i]=='R'&&i+1<s.size()){
                v1[i+1]+=v[i];
            }
            if(s[i]=='L'&&i-1>=0){
                v1[i-1]+=v[i];
            }
            for(auto xx:v1)
                cout<<xx<<" ";
            cout<<endl;
        }
        v=v1;
        if(v2==v)
            break;
    }
    for(auto xx:v)
        cout<<xx<<" ";
}

void road(){
    int n;cin>>n;
    vector<vector<int>> v(n+1,vector<int>(n+1,-1));
    while(n!=1){
        int x,y,z;
        cin>>x>>y>>z;
        v[x][y]=z;
        n--;
    }
   // cout<<v.size()<<endl;
    for(int i=1;i<v.size();i++){
        for(int j=1;j<v.size();j++){
            for(int k=1;k<v.size();k++)
            if(v[k][j]!=-1&&v[i][k]!=-1)
                v[i][j]=max(v[i][j],v[i][k]+v[k][j]);
            else if(v[i][j]!=-1)
                v[i][j]=v[i][j];
            else
                v[i][j]=-1;
        }
    }
    //cout<<v.size()<<endl;
    for(int i=1;i<v.size();i++){
        int Max=0;
        for(auto xx:v[i])
            Max=max(Max,xx);
        cout<<Max<<" ";
    }
}

vector<string> results;
void recursive_str(vector<char>& v,int n,string str){
    if(v.size()==n) {
        int i=0;
        for(auto &xx:str){
            if(xx=='?')
                xx=v[i++];
        }
        results.push_back(str);
        return;
    }
    for(char i='0';i<='9';i++){
        v.push_back(i);
        recursive_str(v,n,str);
        v.pop_back();
    }
}
void str_mod(){
    string str;
    cin>>str;
    int n=count(str.begin(),str.end(),'?');
    vector<char> v;
    recursive_str(v,n,str);
    int sum=0;
    for(auto xx:results){
        int x=stoi(xx);
        if(x%13==5)
        sum++;}
    cout<<sum<<endl;
}

int main(int argc, char* args[])
{
    str_mod();
}