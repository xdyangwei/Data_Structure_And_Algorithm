//
// Created by 杨炜 on 2019/4/9.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <set>

using namespace std;
int chocolate(int n){
    if(n>=1){
    for(int i=1;i<=n;i++){
        return 1+chocolate(n-i);
    }}else{
        return 0;
    }
}
int water(){
    int n,w;
    cin>>n>>w;
    auto m=2*n;
    vector<int> v;
    int x;
    while(m--){
        cin>>x;
        v.push_back(x);
    }
    double z=w/(3.0*n);
    //cout<<z<<endl;
    for(int i=0;i<=2*n-1;i++){
    if(v[i]<2*z&&i<n-1)
    {z=(double)(v[i])/2;//cout<<z<<endl;
    }
    if(v[i]<z&&i>=n)
        z=v[i];
    }
    cout.setf(ios::fixed);
    cout<<setprecision(6);
    cout<<(3*n*z)<<endl;
}
static vector<int> v;
void dfs(multimap<int,int>& m,int x){
    set<int> s;
    for(auto xx:m){
        s.insert(xx.first);
        s.insert(xx.second);
    }
    for(auto xx:m){
        if(xx.first==x||xx.second==x){
            s.erase(xx.first);
            s.erase(xx.second);
        }
    }
    for(auto vv:v){
        s.erase(vv);
    }
    for(auto ss:s){
        v.push_back(ss);
        dfs(m,ss);
    }
}

int exercise_route(){
    int N,M;
    cin>>N>>M;
    multimap<int,int> m1;
    auto m=M;
    int a,b;
    while(m--){
        cin>>a>>b;
        m1.insert(make_pair(a,b));
    }
    set<int> s;
    for(auto xx:m1){
        s.insert(xx.first);
        s.insert(xx.second);
    }
    int count=0;
    for(auto ss:s){
        dfs(m1,ss);
        count+=(v.size());
        v.clear();

    }
    cout<<count<<endl;
    return 0;}
int main(){
    exercise_route();
}