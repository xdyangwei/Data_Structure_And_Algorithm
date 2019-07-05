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


//quick_sort快速排序练习
void quick_sort(vector<int> &v,int start,int end){
    if(v.empty()||start==end)
        return ;
    int z=start;
    auto x=v[z];
    for(int i=z+1;i<end;i++){
        if(v[i]<=x){
            auto y=v[i];
            v.erase(v.begin()+i);
            v.insert(v.begin(),y);
            z++;
        }
    }
    quick_sort(v,0,z);
    quick_sort(v,z+1,end);
}

//冒泡排序bubble_sort
void bubble_sort(vector<int> &v){
    if(v.size()<=1)
        return ;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            if(v[j]<v[i]){
                auto x=v[j];
                v[j]=v[i];
                v[i]=x;
            }
        }
    }
}

//插入排序,每次都是局部排序，每次结束不能找到最小或最大项
void insert_sort(vector<int> &v){
    if(v.size()<=1)
        return ;
    for(int i=1;i<v.size();i++){
        for(int j=i-1;j>=0;j--){
            if(v[j]>v[i]){
                auto x=v[j];
                v[j]=v[i];
                v[i]=x;
            }
        }
    }
}

//选择排序，每次迭代找出最大或最小项，然后与之交换
void select_sort(vector<int>& v){
    if(v.size()<=1)
        return ;
    for(int i=0;i<v.size();i++){
        int tem=v[i];
        int pos=i;
        for(int j=i;j<v.size();j++){
            if(v[j]<tem) {
                tem =v[j];
                pos = j;
            }
        }
        auto x=v[i];
        v[i]=tem;
        v[pos]=x;
    }
}

//归并排序,使用分治法把问题分解为子问题，最后在合并起来
void merge(vector<int> &v,int m,int n){
    vector<int> v1;
    auto middle=(m+n)/2;
    int i,j;
    for(i=m,j=middle+1;i<=middle&&j<=n;){
        if(v[i]<=v[j]){
            v1.push_back(v[i]);i++;
        }else{
            v1.push_back(v[j]);j++;
        }
    }
    while(i<=middle){
        v1.push_back(v[i]);
        i++;
    }
    while(j<=n){
        v1.push_back(v[j]);
        j++;
    }
    for(int k=m,l=0;k<=n&&l<v1.size();k++,l++)
        v[k]=v1[l];
}

void merge_sort(vector<int> &v,int m,int n){
    if(n>m){
        auto middle=(m+n)/2;
        merge_sort(v,m,middle);
        merge_sort(v,middle+1,n);
    }
    merge(v,m,n);
}



int main(){
    vector<int> v{9,8,7,6,5,4,3,2,1};
    merge_sort(v,0,v.size()-1);
    for(auto xx:v)
        cout<<xx<<endl;
}