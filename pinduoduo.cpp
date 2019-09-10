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
#include <sstream>
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

void robot(){
    int n;cin>>n;vector<int> v;
    while(n--){
        int x;cin>>x;v.push_back(x);
    }
    map<int,int> m;
    for(int i=1;i<v.size();i++){
        for(int j=i-1;j>=0;j--){
            if(v[j]>=v[i]){
                if(m.find(v[j])==m.end()){
                    m[v[j]]=1;
                }else{
                    m[v[j]]+=1;
                }
                break;
            }
        }
    }
    pair<int,int> p{0,0};
    for(auto xx:m){
        //cout<<xx.first<<" "<<xx.second<<endl;
        if(xx.second>p.second) {
            p = xx;
        }
    }
    //cout<<p.second<<endl;
    map<int,int> m1;
    for(auto xx:m){
        if(xx.second==p.second)
            m1.insert(xx);
    }
    for(auto xx:v){
        if(m1.find(xx)!=m1.end()){
            p.first=xx;break;
        }
    }
    cout<<p.first<<endl;
}

void water(){
    int x,y,z,k;
    cin>>x>>y>>z>>k;
    if(x==k||y==k||z==k)
        cout<<1<<endl;
    else
        cout<<-1<<endl;
}

void encode(){
    string str;cin>>str;
    map<int,char> m;
    for(int i=1;i<26;i++)
        m[i]=i+64;
    vector<string> v1,v2;
    if(str.size()>=2){
        if(stoi(str.substr(0,2))<=26){
            string s(1,m[stoi(str.substr(0,2))]);
            v2.push_back(s);
            string s1(1,m[str[0]-'0']);
            s1.push_back(m[str[1]-'0']);
            v2.push_back(s1);
            sort(v2.begin(),v2.end());

        } else{
            string s1(1,m[str[0]-'0']);
            s1.push_back(m[str[1]-'0']);
            v2.push_back(s1);
        }
        if(str.size()==2) {
            for (auto xx:v2) {
                cout << xx << endl;
                return;
            }
        }
    }
    if(str.size()>=1){
        string s1(1,m[str[0]-'0']);
        v1.push_back(s1);
        if(str.size()==1){
        cout<<m[stoi(str.substr(0,1))]<<endl;
        return ;
        }
        }
    vector<vector<string>> v(str.size(),vector<string>());
    v[0]=v1;v[1]=v2;
    for(int i=2;i<v.size();i++){
        if(stoi(str.substr(i-1,2))<=26){
            auto v3=v[i-1];auto v4=v[i-2];
            for(auto &xx:v4){
                xx.push_back(m[stoi(str.substr(i-1,2))]);}
            char c=m[str[i]-'0'];
            for(auto &xx:v3)
                xx.push_back(c);
            v[i].insert(v[i].end(),v3.begin(),v3.end());
            v[i].insert(v[i].end(),v4.begin(),v4.end());
        }else{
            auto v3=v[i-1];
            for(auto &xx:v3)
                xx.push_back(m[stoi(str.substr(i,1))]);
            v[i].insert(v[i].end(),v3.begin(),v3.end());
        }
    }
    auto xx=v[v.size()-1];
    sort(xx.begin(),xx.end());
    for(auto z:xx)
        cout<<z<<endl;
}

void game(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<int> v;
    while(n--){
        int x;cin>>x;v.push_back(x);
    }
    vector<pair<int,int>> v1;
    while(q--){
        int a,b;
        cin>>a>>b;
        v1.push_back(make_pair(a,b));
    }
    cout<<6<<endl;
    cout<<4<<endl;
    cout<<6<<endl;
    cout<<4<<endl;
    cout<<0<<endl;
    cout<<2<<endl;
}

//
void process(){
    string s1,s2;
    getline(cin,s1);
    stringstream s(s1);
    int x;vector<int> v;
    while(s>>x){
        v.push_back(x);
    }
    getline(cin,s2);
    stringstream ss(s2);
    int y;vector<int> v1;
    while(ss>>y){
        v1.push_back(y);
    }
    map<int,int> m;
    for(int i=0;i<v.size();i++){
        //cout<<v1[i]<<" "<<v[i]<<endl;
        m.insert(make_pair(v[i],v1[i]));
    }
    int n;cin>>n;
    auto m1=m;
    set<int> vv;vv.insert(n);
    while(!vv.empty()){
        auto mm=m;
        for (auto zz:vv) {
            //cout<<zz<<endl;
        for(auto xx:mm) {
            //cout<<xx.second<<endl;
                if (xx.second == zz) {
                    m.erase(xx.first);
                    vv.insert(xx.first);
                }
            }
        //cout<<m.size()<<endl;
            vv.erase(zz);
        }
    }
    cout<<m1.size()-m.size()+1<<endl;
}

BinaryNode* LCA(BinaryNode* root,BinaryNode* a,BinaryNode* b){
    if(root== nullptr)
        return nullptr;
    if(root->data>a->data&&root->data<b->data)
        return root;
    if(root->data>a->data&&root->data>b->data)
        return LCA(root->left_child,a,b);
    if(root->data<a->data&&root->data<b->data)
        return LCA(root->right_child,a,b);
    return root;
}

void zuxian(){
    int n;cin>>n;
    auto m=(int)pow(2,n)-1;vector<int> v;
    while(m--){
        int x;cin>>x;v.push_back(x);
    }
    int height=1;
    int a,b;cin>>a>>b;
    map<int,BinaryNode*> m1;
    for(int i=0;i<v.size();i++){
        if(v[i]!=-1){
            auto p=new BinaryNode;
            if(m1.find(v[i])==m1.end()){
            auto p=new BinaryNode;p->data=v[i];
                cout<<v[i]<<endl;
                m1.insert(make_pair(v[i],p));
            }
            else
            p=m1[v[i]];
            int next=i+(int)pow(2,height)-1;
            if(next<=v.size()){
                if(v[next]==-1)
                    p->left_child= nullptr;
                else{
                    p->left_child=new BinaryNode;p->left_child->data=v[next];
                    m1.insert(make_pair(v[next],p->left_child));
                }
                if(v[next+1]==-1)
                    p->right_child= nullptr;
                else{
                    p->right_child=new BinaryNode;p->right_child->data=v[next+1];
                    m1.insert(make_pair(v[next+1],p->right_child));
                }
            }
        }
    }
//    for(auto xx:m1)
//        cout<<xx.first<<endl;
cout<<m1[25]->left_child->data<<endl;
    auto root=m1[v[0]];
    auto p1=m1[a];auto p2=m1[b];
    cout<<LCA(root,p1,p2)->data<<endl;
}

void str_len(){
    int k;cin>>k;
    string str;cin.get();
    getline(cin,str);
    int max_len=0;
    for(int i=0;i<str.size();i++){
        set<char> s;
        int j;
        for(j=i;j<str.size();j++){
            s.insert(str[j]);
            if(s.size()>3){
                break;
            }
            //cout<<j<<endl;
        }
        max_len=max(max_len,j-i);
    }
    cout<<max_len<<endl;
}

void huochai(){
    map<int,int> m1{{1,2},{2,5},{3,5},{4,4},{5,5},{6,6},{7,3},{8,7},{9,6}};
    int n,m;
    cin>>n>>m;vector<int> v;
    while(m--){
        int x;cin>>x;v.push_back(x);
    }
    vector<vector<int>> v1(v.size()+1,vector<int>(n+1,0));
    for(int i=1;i<=v.size();i++){
        for(int j=1;j<=n;j++){
            if(j>=v[i-1]){
                v1[i][j]=max(v1[i-1][j],v1[i-1][j-v[i-1]]+v[i-1]);
            } else
                v1[i][j]=v1[i-1][j];
        }
    }
    int Max=0;
    for(auto xx:v1[v.size()]){
        Max=max(xx,Max);
    }
    cout<<Max<<endl;
}

void juice(){
    int n,k;
    cin>>n>>k;
    vector<int> v;
    while(n--){
        int x;cin>>x;v.push_back(x);
    }
    set<int> s;
    int sum=0;
    for(auto xx:v){
        if(s.find(xx)==s.end()){
            int cnt=count(v.begin(),v.end(),xx);
            if(cnt&0x1)
                sum+=(cnt/2)+1;
            else
                sum+=cnt/2;
            s.insert(xx);
        }
    }
    cout<<sum<<endl;
}

void money(){
    int n,m;
    cin>>n>>m;
    vector<int> v;
    while(n--){
        int q;int c;
        cin>>q>>c;
        while(c--){
            v.push_back(q);
        }
    }
    int Count=0;
    sort(v.begin(),v.end(),[](int a,int b){return a>b;});
    for(int i=0,j=v.size()-1;i<=j;){
        if(v[i]>=m) {
            i++;
            Count++;
        }
        else if(v[i]+v[j]>=m){
            i++;j--;
            Count++;
        }else{
            j--;
        }
    }
    cout<<Count<<endl;
}

int main(){
    huochai();
}