//
// Created by 杨炜 on 2019/4/9.
//

#include <iostream>
#include <vector>
#include <iomanip>
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
int main(){
    //cout<<zuhe(6,2)<<endl;
    //cout<<pailie(0);
    water();
}