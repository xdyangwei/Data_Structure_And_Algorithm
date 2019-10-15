//
// Created by 杨炜 on 2019/10/9.
//
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <queue>

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
    map<int,bool> m{{DOWN,1},{RIGHT,1},{UP,1},{LEFT,1}};
};

//栈解决迷宫问题
//思路：每次都依次判断下右上左是否可走，可走压栈，不可走就换个方向，当发现四个方向都无路可走的时候就出栈，然后将此时的栈顶
//元素即上一步路径所走的当前方向设置为不可走即可
void maze_with_obstacles(vector<vector<int>>& v){
    if(v.empty()||v[0].empty()||v[0][0]==1)
        return ;
    stack<my_type> s1;
    vector<vector<int>> visited(v.size(),vector<int>(v[0].size(),0));
    my_type entrance;entrance.x=1;entrance.y=1;entrance.next=DOWN;visited[0][0]=1;
    s1.push(entrance);
    while(true){
        auto &tmp=s1.top();
        if(tmp.x==v.size()&&tmp.y==v[0].size())
            break;
        my_type next_pos;
        switch(tmp.next){
            case DOWN:
                if(tmp.x==v.size()){
                    tmp.next=RIGHT;
                }else{
                    if(v[tmp.x][tmp.y-1]||visited[tmp.x][tmp.y-1]||!tmp.m[DOWN]){
                        tmp.next=RIGHT;
                    }else{
                        next_pos.x=tmp.x+1;
                        next_pos.y=tmp.y;
                        next_pos.next=DOWN;
                        visited[tmp.x][tmp.y-1]=1;
                        s1.push(next_pos);
                    }
                }
                break;
            case RIGHT:
                if(tmp.y==v[0].size()) {
                    tmp.next = UP;
                }
                else{
                    if(v[tmp.x-1][tmp.y]||visited[tmp.x-1][tmp.y]||!tmp.m[RIGHT]){
                        tmp.next=UP;
                        visited[tmp.x-1][tmp.y]=0;
                    }else{
                        next_pos.x=tmp.x;
                        next_pos.y=tmp.y+1;
                        next_pos.next=DOWN;
                        visited[tmp.x-1][tmp.y]=1;
                        s1.push(next_pos);
                    }
                }
                break;
            case UP:
                if(tmp.x==0){
                    tmp.next=LEFT;
                }else {
                    if (v[tmp.x - 2][tmp.y - 1]||visited[tmp.x - 2][tmp.y - 1]||!tmp.m[UP]) {
                        tmp.next = LEFT;
                        visited[tmp.x - 2][tmp.y - 1]=0;
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
                    s1.top().m[s1.top().next]= false;
                }
                else {
                    if (v[tmp.x - 1][tmp.y - 2]||visited[tmp.x - 1][tmp.y - 2]||!tmp.m[LEFT]) {
                        s1.pop();
                        s1.top().m[s1.top().next]= false;
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

struct parking_car{
    char status;
    int number;
    int time;
};

stack<parking_car> parking_lot;
queue<parking_car> road;
int parking_lot_size=2;
void car_arrival(parking_car car){
    if(parking_lot.size()==parking_lot_size){
        auto len=road.size();
        road.push(car);
        cout<<"waiting at "<<len+1<<" position"<<endl;
    } else{
        parking_lot.push(car);
        auto len=parking_lot.size();
        cout<<"parking at "<<len<<" position"<<endl;
    }
}

void car_departure(parking_car car){
    stack<parking_car> s1;
    while(true){
        auto x=parking_lot.top();
        if(x.number==car.number){
            parking_lot.pop();
            cout<<"parking_time: "<<car.time-x.time<<" total_cost: "<<(car.time-x.time)*3<<endl;
            while(!s1.empty()){
                parking_lot.push(s1.top());
                s1.pop();
            }
            break;
        }else{
            s1.push(x);
            parking_lot.pop();
        }
    }
    if(!road.empty()){
        auto x=road.front();
        x.time=car.time;
        parking_lot.push(x);
        road.pop();
    }
}
void parking_lot_management(int number){
    parking_car car;
    cin>>car.status>>car.number>>car.time;
    if(car.status=='A')
        car_arrival(car);
    else
        car_departure(car);
}


int main(){
    vector<vector<int>> v{{0,0,1,0,0,0,1,0},{0,0,1,0,0,0,1,0},{0,0,0,0,1,1,0,1},{0,1,1,1,0,0,1,0},{0,0,0,1,0,0,0,0},{0,1,0,0,0,1,0,1},{0,1,1,1,1,0,0,1},{1,1,0,0,0,1,0,1},{1,1,0,0,0,0,0,0}};
    maze_with_obstacles(v);
}
