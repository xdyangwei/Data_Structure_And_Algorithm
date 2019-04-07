//
// Created by 杨炜 on 2019/3/17.
//
#include <iostream>
#include <stack>
#include<queue>
#include <cmath>
#include <algorithm>
using namespace std;

template<typename T>
class Queue_with_Stack {
public:
    void push(T v) {
        s1.push(v);
    }

    auto front() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
            return s2.top();
        } else {
            return s2.top();
        }
    }

    void pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
            s2.pop();
        } else {
            s2.pop();
        }
    }

private:
    stack<T> s1;
    stack<T> s2;
};

template<typename T>
class Stack_with_Queue {
public:
    void push(T v) {
        q1.push(v);
    }

    auto top() {
        if (q2.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            return q1.front();
        } else {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            return q2.front();
        }
    }

    void pop() {
        if (q1.size() == 1) {
            q1.pop();
        } else {
            q2.pop();
        }
    }

private:
    queue<T> q1;
    queue<T> q2;
};

//find the repeat number in a array
//solution1:use an extra array
int repeat_number_with_extra_space(vector<int> v){
    vector<int> v1(v.size(),0);
    int n;
    for(auto xx:v){
        v1[xx]=v1[xx]+1;
        if(v1[xx]>1){
            n=xx;
            break;
        }
    }
    return n;
}

//solution2:使用二分法求1-n之间1-n/2之间数的数目，如果大于n/2则表示多的数在这个区间中
//否则就去n/2+1-n这个区间去找，直到找到重复数字为止
int repeat_number_with_binary(vector<int> v){
    auto n=v.size();
    auto start=1;auto end=n-1;
    while(start!=end){
        auto mid=(end-start)/2+1;
        int count=0;
        for(auto xx:v){
            if(xx>=start&&xx<=mid){
                count++;
            }
        }
        if(count>mid){
            end=mid;
        }else{
            start=mid+1;
        }
    }
    return start;
}

//solution3:将当前值与其对应下标的值进行交换，比如值为1且当前下标不为1，下标为1位置上的值也不是1就与其交换
//直到找到重复的值，不过这个方法需要改变原来的数组
int repeat_number_with_swap(vector<int>& v){
    auto z=0;
    for(auto i=1;i<=v.size();i++){
        if(v[i-1]!=i){
            auto x=v[v[i-1]];
            if(v[v[i-1]-1]==v[i-1]){
                z=v[i-1];
                break;
            }
            v[v[i-1]-1]=v[i-1];v[i-1]=x;
        }
    }
    return z;
}
//二维数组从左到右递增，从上到下递增，先给一个数输出能否在二维数组中找到该数
//思路：从左下角开始比较，当左下角数值比x小时，就可以排除左小角值所在的那一列
//当数值比x大时，这一行就可以排除了，然后继续取左下角值
//也可以从右上角开始，当x比右上角数大时这一排可以排除，当比右上角小时这一列可以排除
bool two_dimension_array_find(vector<vector<int>> v,int x){
    auto n=v.size();auto m=v[0].size();bool flag=0;
    for(int i=n-1,j=0;i>=0&&j<=m-1;) {
            if (v[i][j] == x) {
                flag = 1;
                break;
            } else if (v[i][j] > x) {
                i--;
            } else {
                // cout<<"here"<<endl;
                j++;
            }
    }
    return flag;
}

//顺时针输出一个矩阵，主要注意点为边界条件的判定
void print_one_circle(vector<vector<int> > matrix,vector<int>& v1,int start){
    auto m=matrix.size();auto n=matrix[0].size();
    for(int i=start;i<=n-1-start;i++)
        v1.push_back(matrix[start][i]);
    for(int i=start+1;i<=m-1-start;i++)
        v1.push_back(matrix[i][n-1-start]);
    for(int i=n-2-start;i>=start;i--)
        v1.push_back(matrix[m-1-start][i]);
    for(int i=m-2-start;i>=start+1;i--)
        v1.push_back(matrix[i][start]);
}
vector<int> printMatrix(vector<vector<int> > matrix){
    int start=0;auto m=matrix.size();auto n=matrix[0].size();
    vector<int> v1;
    while(start<=(m/2-1)&&start<=(n/2-1)){
        print_one_circle(matrix,v1,start);
        start++;
    }
    //cout<<start<<" "<<m/2<<" "<<n/2<<endl;
    if(start==(m/2)){
        //cout<<"yes"<<endl;
        for(int i=start;i<=n-1-start;i++)
            v1.push_back(matrix[start][i]);
    }
    if(start==(n/2)) {
        for (int i = start; i <= m-1  - start; ++i) {
            v1.push_back(matrix[i][start]);
        }
    }
    return v1;
}

//实现栈数据结构，并且使得从栈中pop、push和min（取最小值）都是常数级别
template <typename T>
struct Stack{
    stack<T> s1;
    stack<T> s2;
    void push(T v){
        s1.push(v);
        if(s2.empty())
            s2.push(v);
        else{
            if(v<s2.top())
                s2.push(v);
            else{
                s2.push(s2.top());
            }
        }
    }
    void pop(){
        if(!s1.empty()){
            s1.pop();s2.pop();
        }else{
            cerr<<"empty stack can't pop"<<endl;
        }
    }
    T top(){
        return s1.top();
    }
    T min(){
        if(!s2.empty()){
            return s2.top();
        } else{
            cerr<<"empty stack has no min"<<endl;
        }
    }
};

//栈的压入、弹出序列，给定一个栈的压入顺序和弹出序列，判断弹出序列是否可能是
//该压栈序列的弹出序列
bool IsPopOrder(vector<int> pushV,vector<int> popV) {
    stack<int> s1;int i=0;int j=0;
    auto copy_popV=popV;
    while(i!=pushV.size()&&j!=popV.size()){
        if(pushV[i]!=popV[j]){
            s1.push(pushV[i]);
            i++;
        } else{
            popV.erase(popV.begin());
            pushV.erase(i+pushV.begin());
            i--;
            j=0;
        }
    }
//    for(auto xx:popV){
//        cout<<xx<<endl;
//    }
    if(popV.empty()){
        return true;
    } else{
        return false;
    }
}

//打怪雇佣问题，穿越山谷时依次遇见n只怪兽，如果当前怪兽武力值大于其雇佣的怪兽武力值和
//则小Q需要贿赂这只怪兽才能保证其不被攻击
//思路：多重背包问题
int min_coins(){
    int n;
    cin>>n;
    auto tmp=n;
    int x;
    vector<int> monsters;
    while(n--){
        cin>>x;
        monsters.push_back(x);
    }
    vector<int> coins;
    while (tmp--){
        cin>>x;
        coins.push_back(x);
    }
    vector<pair<int,int>> min_coin(monsters.size(),make_pair(0,0));
    min_coin[0].first=monsters[0];
    min_coin[0].second=coins[0];
    for(int i=1;i<=min_coin.size()-1;i++){
        if(min_coin[i-1].first>=monsters[i]){
            min_coin[i]=min_coin[i-1];
        }else{
            auto y=monsters[i]-min_coin[i-1].first;
            if(find_if(monsters.begin(),monsters.begin()+i,[y](int a){return a>=y?true: false;})==monsters.begin()+i)
            min_coin[i].first=monsters[i];
            min_coin[i].second=min_coin[i-1].second+coins[i];
        }
    }
    return min_coin[min_coin.size()-1].second;
}

int min_length(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    for(int i=0;i<n;){
        if((s[i]=='0'&&s[i+1]=='1')||(s[i]=='1'&&s[i+1]=='0')){
            s.erase(i,2);
            i=i-1;
        }else{
            i++;
        }
    }
    return s.size();
}

int least_coin(){
    int m,n;
    cin>>m>>n;
    vector<int> v;
    int x;
    while(n--){
        cin>>x;
        v.push_back(x);
    }
    //cout<<"here"<<endl;
    sort(v.begin(),v.end());
    if(v[0]!=1)
        return -1;
    vector<int> v1(v.size()+1,0);
    v1[1]=1;
    for(int i=2;i<=m;i++){
        //cout<<i<<endl;
        auto it=find_if(v.begin(),v.end(),[i](int a){return (a>i)?true: false;});
        //cout<<*it<<endl;
        auto y=*(it-1);
        //cout<<y<<endl;
        auto addi=i%y;
        v1[i]+=(i/y);
        //cout<<v1[i]<<endl;
        while(addi!=0){
            auto it1=find_if(v.begin(),v.end(),[addi](int a){return (a>addi)?true: false;});
            auto z=*(it1-1);
            v1[i]+=(addi/z);
            addi=addi%z;
        }
    }
    int MAX=0;
    for(auto xx:v1)
        MAX=max(MAX,xx);
    return MAX;
}
int main() {
    cout<<least_coin();
    return 0;

}