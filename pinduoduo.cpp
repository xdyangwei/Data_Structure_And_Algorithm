//
// Created by 杨炜 on 2019/9/4.
//
#include <queue>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <cmath>

using namespace std;

struct BinaryNode{
    int data;
    BinaryNode* left_child;
    BinaryNode* right_child;
};
int Max_width(BinaryNode* root){
    std::queue<BinaryNode*> q;
    if(!root)
        return 0;
    q.push(root);
    int max_width=1;
    while(!q.empty()){
        decltype(q) q1;
        while(!q.empty()){
            auto x=q.front();
            if(x->left_child) {
                q1.push(x->left_child);
            }
            if(x->right_child){
                q1.push(x->right_child);
            }
            q.pop();
        }
        max_width=max(max_width,(int)q1.size());
        while(!q1.empty()){
            auto x=q1.front();
            q.push(x);q1.pop();
        }
    }
    return max_width;
}

//二进制回文数
void parliam_number(){
    int n;
    cin>>n;
    vector<int> v;
    while(n--){
        int x;cin>>x;v.push_back(x);
    }
    for(auto xx:v){
        bitset<32> b(xx);
        int x=-1;
        for(int i=31;i>=0;i--){
            if(b[i]==1){
                x=i;break;
            }
        }
        if(x==-1){
            cout<<"YES"<<endl;
        }else{
            vector<int> v1;
            for(int i=x;i>=0;i--){
                v1.push_back(b[i]);
            }
            auto v2=v1;
            reverse(v1.begin(),v1.end());
            if(v2==v1)
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
    }
}

//递增树
void add_tree(){
    int n;cin>>n;
    vector<BinaryNode*> v;
    while(n--){
        int n1;cin>>n1;
        int value,left,right;
        vector<pair<int,int>> v1;
        map<int,BinaryNode*> v2;
        v1.resize(5001);
        while(n1--){
            cin>>value>>left>>right;
            auto x=new BinaryNode;x->data=value;
            v1[value]=make_pair(left,right);
        }
    }
}

void coffee(){
    int n;
    while(cin>>n) {
        vector<pair<int, int>> v;
        int n1 = n;
        vector<vector<int>> days;
        while (n--) {
            int k, m;
            cin >> k >> m;
            v.push_back(make_pair(k, m));
            vector<int> v1;
            while (m--) {
                int x;
                cin >> x;
                v1.push_back(x);
            }
            days.push_back(v1);
        }
        set<int> s;
        for (int i = 1; i <= 30; i++) {
            s.insert(i);
        }
        for (int i = 0; i < n1; i++) {
            auto s1 = s;
            auto vv = days[i];
            auto iterval = v[i].first;
            for (auto xx:vv) {
                s1.erase(xx);
                auto xxx = 1;
                while (xx - xxx > 0 && xxx <= iterval) {
                    s1.erase(xx - xxx);
                    xxx++;
                }
                xxx = 1;
                while (xx + xxx <= 30 && xxx <= iterval) {
                    s1.erase(xx + xxx);
                    xxx++;
                }
            }
            vector<int> vvv(s1.begin(), s1.end());
            for (int i = 1; i < vvv.size(); i++) {
                if (vvv[i] - vvv[i - 1] < iterval + 1)
                    vvv.erase(vvv.begin() + i);
            }
            cout << vvv.size() + days[i].size() << endl;
            s1 = s;
        }
    }
}


bool judge(vector<vector<int>> v,int i,int j,int length,int value){
    bool flag=true;
    int x=0;
    vector<vector<int>> v1;
    while(x<=length){
        int y=0;
        vector<int> v2;
        while(y<=length){
            v2.push_back(v[i][j+y]);
            y++;
        }
       v1.push_back(v2);
        x++;
    }
    for(auto xx:v1){
        for(auto xxx:xx){
            if(xxx!=value){
                flag= false;break;
            }
        }
        if(flag==false)
            break;
    }
    return flag;
}

int len(vector<vector<int>> v,int i,int j,int length){
    int n=v.size();int m=v[0].size();
    int x=length/3;
    if(judge(v,i,j,x,0)&&judge(v,i,j+x,x,1)&&judge(v,i,j+2*x,x,0)&&judge(v,i+x,j,x,1)&&judge(v,i+x,j+x,x,1)&&judge(v,i+x,j+2*x,x,1)&&
    judge(v,i+2*x,j,x,0)&&judge(v,i+2*x,j+x,x,1)&&judge(v,i+2*x,j+2*x,x,0))
        return length;
    else
        return -1;
}

void yinzhang(){
    int n;
    cin>>n;
    vector<vector<vector<int>>> v;
    while(n){
        int n1,m;cin>>n1>>m;vector<vector<int>> v1;cin.get();
        while(n1--){
            vector<int> v2;
                string str;getline(cin,str);
                for(auto xx:str)
                    v2.push_back(xx-'0');

            v1.push_back(v2);

        }
        v.push_back(v1);
        n--;
    }
    for(auto vv:v){
        auto n=vv.size();auto m=vv[0].size();
        bool flag=false;pair<pair<int,int>,int> p({-1,-1},-1);
        for(int i=0;i<n-2;i++){
            for(int j=0;j<m-2;j++){
                int length=3;
                while(i+length<n&&j+length<m){
                    auto x=len(vv,i,j,length);
                    if(x>p.second){
                        p.first=make_pair(i,j);
                        p.second=x;
                    }
                    length+=3;
                }
            }
        }
        if(p.second==-1)
            cout<<"-1 -1 -1 -1"<<endl;
        else{
            cout<<p.first.first<<" "<<p.first.second<<" "<<p.first.first+p.second-1<<" "<<p.first.second+p.second-1<<endl;
        }
    }
}

bool judge_1(vector<int> v,vector<int> a){
    bool flag=true;
    for(int i=0;i<a.size();i++){
        if(a[i]==0){
            if(v[i]>=v[i+1]){
                flag= false;break;
            }
        }else{
            if(v[i]<=v[i+1]){
                flag=false;break;
            }
        }
    }
    return flag;
}

void pailie(){
    int n;cin>>n;
    int n1=n-1;
    vector<int> a;
    while(n1--){
        int x;cin>>x;a.push_back(x);
    }
    vector<int> p;
    for(int i=1;i<=n;i++){
        p.push_back(i);
    }
    int Count=0;
    if(judge_1(p,a))
        Count++;
    while(next_permutation(p.begin(),p.end())){
        if(judge_1(p,a))
            Count++;
    }
    cout<<Count<<endl;
}

vector<vector<int>> vv;
void pailie_recursive(vector<int> &v,int n,vector<int> a){
    if(v.size()==n){
        vv.push_back(v);
        return ;
    }
    for(int i=1;i<=n;i++){
        if(find(v.begin(),v.end(),i)==v.end()){
            v.push_back(i);
            int m=v.size()-1;
            if(a[m-1]==0&&m>=1){
                if(v[m-1]>=v[m]) {
                    v.pop_back();
                    continue;
                }
            }
            if(a[m-1]==1&&m>=1){
                if(v[m-1]<=v[m]) {
                    v.pop_back();
                    continue;
                }
            }
            pailie_recursive(v,n,a);
            v.pop_back();
        }
    }
}

void pailie_2(){
    int n;cin>>n;
    int n1=n-1;
    vector<int> a;
    while(n1--){
        int x;cin>>x;a.push_back(x);
    }
    vector<int> p;
    pailie_recursive(p,n,a);
    for(auto x:vv){
        for(auto xx:x)
            cout<<xx<<" ";
        cout<<endl;
    }
    cout<<vv.size()<<endl;
}

void pailie_dp(){
    int n;cin>>n;
    int n1=n-1;
    vector<int> a;
    while(n1--){
        int x;cin>>x;a.push_back(x);
    }
    vector<vector<int>> v1(n,vector<int>(n,0));
    vector<vector<int>> v2(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        v2[i][0]=1;
        for(int j=1;j<=i;j++){
            v2[i][j]=(v2[i-1][j-1]+v2[i-1][j])%(int)(pow(10,9)+7);
        }
    }
    for(int i=0;i<n;i++)
        v1[i][i]=1;
    for(int i=2;i<n;i++){
        for(int j=1;j<=n-i+1;j++){
            int k=j+i-1;
            if(a[j]==1){
                v1[j][k]=(v1[j][k]+v1[j+1][k])%(int)(pow(10,9)+7);
            }
            if(a[k-1]==0)
                v1[j][k]=(v1[j][k]+v1[j][k-1])%(int)(pow(10,9)+7);
            for(int z=j+1;z<=k-1;z++){
                if(a[z-1]==0&&a[z]==1){
                    v1[j][k]=(v1[j][k]+(long long)(v2[i-1][z-j]*v1[j][z-1]%(int)(pow(10,9)+7)*v1[z+1][k]%(int)(pow(10,9)+7)))%(int)(pow(10,9)+7);
                }
            }
        }
    }
    for(auto x:v1){
        for(auto xx:x)
            cout<<xx<<" ";
        cout<<endl;
    }
}

int main(){
    pailie_dp();
}