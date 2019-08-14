//
// Created by 杨炜 on 2019/4/9.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <set>
#include <algorithm>
#include <bitset>
#include <stack>

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

//统计每个月兔子的总数
int getTotalCount(int month){
    int count;
    if (month < 3)
        count = 1;
    else
        count = getTotalCount(month - 1) + getTotalCount(month - 2);
    return count;
}

//参数解析
void parse_arguments(){
    string str;
    while(getline(cin,str)){
        bool flag = false;
        vector<string> vec;
        string row;
        for (int i = 0; i < str.size(); i++) {
            if (flag) {//在括号内
                if (str[i] != '\"') row += str[i];
                else flag = false;
            } else {
                if (str[i] == ' ') {
                    vec.push_back(row);
                    row = "";
                } else if (str[i] == '\"') flag = true;
                else row += str[i];
            }
        }
        vec.push_back(row);
        cout << vec.size() << endl;
        for (auto i : vec) cout << i << endl;
    }
}

//字符逆序
//将一个字符串str的内容颠倒过来，并输出。
//str的长度不超过100个字符。 如：输入“I am a student”，输出“tneduts a ma I”。
void reverse_str(){
    string str;
    while(getline(cin,str)){
        reverse(str.begin(),str.end());
        cout<<str<<endl;
    }
}

//取平均数使得剩下的数最大
double average_of_numbers(vector<double>& v){
    if(v.size()==1)
        return v[0];
    else{
        double x=(v[0]+v[1])/2;
        v.push_back(x);
        v.erase(v.begin(),v.begin()+2);
        sort(v.begin(),v.end());
        return average_of_numbers(v);
    }
}

//不在同一行同一列的两个数乘积最大
struct dim{
    int value;
    int x;
    int y;
    dim(int a,int b,int c):
    value(a),x(b),y(c){}
};
int max_product(vector<vector<int>> &v){
    if(v.empty()||v[0].empty())
        return 0;
    vector<dim> v1;
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[0].size();j++) {
            v1.push_back(dim(v[i][j],i,j));
        }
    }
    sort(v1.begin(),v1.end(),[](dim a,dim b){
        return a.value>b.value?true: false;
    });
    int Max=0;
    for(int i=0;i<v1.size();i++){
        for(int j=0;j<v1.size()&&j!=i;j++){
            if(v1[i].x!=v1[j].x&&v1[i].y!=v1[j].y)
                Max=max(Max,v1[i].value*v1[j].value);
        }
    }
    return Max;
}

//最大连续bit数
void longest_one_number(){
    int n;
    while(cin>>n){
        bitset<32> b(n);
        int Max=0;
        for(int i=0;i<32;){
            if(b[i]){
                int j=1;
                while(b[i+j]){
                    j++;
                }
                Max=max(Max,j);
                i+=j;
            }else{
                i++;
            }
        }
        cout<<Max<<endl;
    }

}

//0-1背包问题
void knapsack_0_1(){
    int n,W;
    while(cin>>n>>W){
        vector<pair<int,int>> v1;
        while(n--){
            int w,v;
            cin>>w>>v;
            v1.push_back(make_pair(w,v));
        }
        vector<int> v2(W+1,0);
        for(int i=0;i<v1.size();i++){
            for(int j=W;j>=v1[i].first;j--)
                v2[j]=max(v2[j-v1[i].first]+v1[i].second,v2[j]);
        }
        cout<<v2[W]<<endl;
    }
}

void find_bit(){
    int n;
    while(cin>>n){
        bitset<32> b(n);
        int pos=32;int Count=0;
        for(int i=0;i<30;i++){
            if(b[i]==1&&b[i+1]==0&&b[i+2]==1){
                pos=min(pos,i);
                Count++;
            }
        }
        if(pos==32)
            pos=-1;
        cout<<Count<<" "<<pos<<endl;
    }
}

void table_data_parse(){
    string str;
    while(cin>>str){
        int x=count(str.begin(),str.end(),',');
        string s;int Count=1;bool flag=true;vector<string> v(x+2,"");
        for(int i=0;i<str.size();i++){
            if(str[i]==','&&s.empty()){
                Count++;}
            else if(str[i]==','&&!s.empty()){
                s.push_back(str[i]);
                v[Count].push_back(str[i]);
            }else if(str[i]=='"'&&!s.empty()){
                auto it=find(s.begin(),s.end(),'"');
                if(it==s.end()) {
                    flag = false;break;
                }else if((i<str.size()-1&&str[i+1]!=',')){
                    v[Count].push_back(str[i]);
                }else{
                    for(int i=0;i<s.size();){
                        if(s[i]=='"'||s[i]==',')
                            s.erase(s.begin()+i);
                        else
                            i++;
                    }
                }
            }else if(str[i]=='"'&&s.empty()){
                s.push_back(str[i]);
            }else{
                v[Count].push_back(str[i]);
            }
        }
        if(flag&&s.empty()){
            cout<<Count<<endl;
            for(int i=1;i<=Count;i++){
                if(v[i].size()==0)
                    cout<<"--"<<endl;
                else if(find(v[i].begin(),v[i].end(),'"')!=v[i].end()){
                    for(int j=0;j<v[i].size()-1;j++){
                        if(v[i][j]=='"'&&v[i][j+1]=='"'){
                            v[i].erase(v[i].begin()+j);
                        }
                    }
                    cout<<v[i]<<endl;
                }
                else
                    cout<<v[i]<<endl;}
        }else{
            cout<<"Error"<<endl;
        }
    }
}

struct data1{
    int m;
    int i;
    int n;
};

void recommend_friends(){
    int n;
    while(cin>>n){
        vector<vector<int>> v2;
        vector<decltype(v2)> vv;
        vector<data1> v3;
        while(n--){
            int m,i,n;data1 d;
            cin>>m>>i>>n;
            d.m=m;d.i=i;d.n=n;
            v3.push_back(d);
            int k;cin>>k;
            vector<vector<int>> v1(m,vector<int>(m,0));
            while(k--){
                int j,l,v;
                cin>>j>>l>>v;
                v1[j][l]=v;v1[l][j]=v;
            }
            vv.push_back(v1);
        }
        int z=0;
        for(auto xx:vv){
            set<int> vvv;
            auto ii=v3[z].i;auto nn=v3[z].n;
            vector<vector<int>> vvvv(nn+1);
            if(nn==1){
                for(int i=0;i<xx.size();i++){
                    if(xx[ii][i]!=0){
                        vvv.insert(i);
                    }
                }
            }else{

        }
            cout<<vvv.size()<<" ";
            for(auto xx:vvv){
                cout<<xx<<" ";
            }
            cout<<endl;
        }
    }
}

int main(){
    recommend_friends();
    return 0;
}