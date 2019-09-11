//
// Created by 杨炜 on 2019/9/11.
//
#include<iostream>
#include<string>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <vector>

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
            v[i]=max(v[i-1][j],v[]);
        }
    }


    return res;
}

int main(int argc, char* args[])
{
    char input[10000];
    cin.getline(input,10000);
    cout<<solution(input)<<endl;
}