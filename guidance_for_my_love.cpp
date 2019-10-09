//
// Created by 杨炜 on 2019/10/9.
//
#include <iostream>
#include <stack>
using namespace std;
int Ackerman_recursive(int m,int n){
    if(m==0)
        return n+1;
    else if(n==0)
        return Ackerman_recursive(m-1,1);
    else
        return Ackerman_recursive(m-1,Ackerman_recursive(m,n-1));
}

int Ackerman_with_stack(int m,int n){
    int N=100;
    int temp[m+1][N];
    for(int i=0;i<N;i++)
        temp[0][i]=i+1;
    for(int i=1;i<=m;i++){
        temp[i][0]=temp[i-1][1];
        for(int j=1;j<N;j++){
            temp[i][j]=temp[i-1][temp[i][j-1]];
        }
    }
    /*for(int i=0;i<=m;i++){
        for(int j=0;j<N;j++)
            cout<<temp[i][j]<<" ";
        cout<<endl;}*/
    return temp[m][n];
}

int Ackerman_with_stack2(int m,int n){
    stack<int> s;
    s.push(m);
    while(!s.empty()){
        m=s.top();
        s.pop();
        if(!m)
            n=n+1;
        else if(!n){
            n=1;
            m=m-1;
            s.push(m);
        }else{
            n=n-1;
            s.push(m-1);//sequece is specifiec because calculate m first
            s.push(m);
        }
    }
    return n;
}
int main(){
    cout<<Ackerman_with_stack2(3,1)<<endl;
    cout<<Ackerman_recursive(3,1)<<endl;
}
