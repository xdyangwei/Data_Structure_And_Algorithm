//
// Created by 杨炜 on 2019/9/4.
//
#include <queue>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
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

int main(){
    yinzhang();
}