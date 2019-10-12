//
// Created by 杨炜 on 2019/10/9.
//
#include <iostream>
#include <stack>
#include <vector>
#define DOWN 1
#define RIGHT 2
#define UP 3
#define LEFT 4
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

struct my_type{
    int x;
    int y;
    int next;
};
void maze_with_obstacles(vector<vector<int>>& v){
    if(v.empty()||v[0].empty()||v[0][0]==1)
        return ;
    stack<my_type> s1;
    vector<vector<int>> visited(v.size(),vector<int>(v[0].size(),0));
    my_type entrance;entrance.x=1;entrance.y=1;entrance.next=DOWN;visited[0][0]=1;
    s1.push(entrance);
    while(true){
        auto &tmp=s1.top();
        cout<<tmp.x<<" "<<tmp.y<<" "<<tmp.next<<endl;
        if(tmp.x==v.size()&&tmp.y==v[0].size())
            break;
        my_type next_pos;
        switch(tmp.next){
            case DOWN:
                if(tmp.x==v.size()){
                    tmp.next=RIGHT;
                }else{
                    if(v[tmp.x][tmp.y-1]||visited[tmp.x][tmp.y-1]){
                        tmp.next=RIGHT;
                    }else{
                        next_pos.x=tmp.x+1;
                        //cout<<next_pos.x<<endl;
                        next_pos.y=tmp.y;
                        next_pos.next=DOWN;
                        visited[tmp.x][tmp.y-1]=1;
                        s1.push(next_pos);
                        //cout<<s1.top().x<<endl;
                    }
                }
                break;
            case RIGHT:
                if(tmp.y==v[0].size())
                    tmp.next=UP;
                else{
                    if(v[tmp.x-1][tmp.y]||visited[tmp.x-1][tmp.y]){
                        tmp.next=UP;
                    }else{
                        next_pos.x=tmp.x;
                        next_pos.y=tmp.y+1;
                        next_pos.next=DOWN;
                        visited[tmp.x-1][tmp.y]=1;
                        s1.push(next_pos);
                    }}
                break;
            case UP:
                if(tmp.x==0){
                    tmp.next=LEFT;
                }else {
                    if (v[tmp.x - 2][tmp.y - 1]||visited[tmp.x - 2][tmp.y - 1]) {
                        tmp.next = LEFT;
                    } else {
                        next_pos.x = tmp.x - 1;
                        next_pos.y = tmp.y;
                        next_pos.next = DOWN;
                        visited[tmp.x - 2][tmp.y - 1]=1;
                        s1.push(next_pos);
                    }
                }
                break;
            case LEFT:
                if(tmp.y==0){
                    s1.pop();
                    visited[tmp.x-1][tmp.y-1]=0;
                }
                else {
                    if (v[tmp.x - 1][tmp.y - 2]||visited[tmp.x - 1][tmp.y - 2]) {
                        s1.pop();
                        visited[tmp.x-1][tmp.y-1]=0;
                    }
                    else {
                        next_pos.x = tmp.x;
                        next_pos.y = tmp.y - 1;
                        next_pos.next = DOWN;
                        visited[tmp.x - 1][tmp.y - 2]=1;
                        s1.push(next_pos);
                    }
                }
        }
        //cout<<s1.top().x<<endl;
    }
    stack<my_type> s2;
    while(!s1.empty()){
        auto x=s1.top();
        s2.push(x);
        s1.pop();
    }
    while(!s2.empty()){
        auto x=s2.top();
        cout<<x.x<<" "<<x.y<<" "<<x.next<<endl;
        s2.pop();
    }
}
int main(){
    cout<<Ackerman_with_stack2(3,1)<<endl;
    cout<<Ackerman_recursive(3,1)<<endl;
}
