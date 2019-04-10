//
// Created by 杨炜 on 2019/4/10.
//
#include <iostream>
#include <string>
#include <type_traits>
#include <map>
#include "dist/jsoncpp.cpp"
using namespace std;
using namespace Json;

auto writer(double x,double y,double r){
    Value v;
    v["x"]=x;
    v["y"]=y;
    v["r"]=r;
    auto &z=v;
    return z;
}

auto reader(string s){
    CharReaderBuilder b;
    Value v;
    JSONCPP_STRING errs;
    bool flag=b.newCharReader()->parse(s.c_str(),s.c_str()+s.size(),&v,&errs);
    cout<<flag<<endl;
    cout<<v<<endl;
    auto x=v.getMemberNames();
    map<string,double> m1;
    for(auto xx:x){
    pair<string,double> p(xx, v[xx].asDouble());
        //m1.insert(make_pair(xx,v[xx]));
        m1.insert(p);
    }
    return m1;
}
int main(){
    auto x=writer(6,8,10);
    StreamWriterBuilder b;
    auto s=writeString(b,x);
    auto m=reader(s);
    for(auto mm:m){
        cout.setf(ios::fixed);
        cout<<setprecision(2);
        cout<<mm.first<<" "<<mm.second<<endl;
    }
    return 0;
}
