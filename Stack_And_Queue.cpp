//
// Created by 杨炜 on 2019/3/17.
//
#include <iostream>
#include <stack>
#include<queue>
#include <cmath>
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

int main() {
    vector<vector<int>> v{{1,2},{3,4},{5,6}};
    cout<<two_dimension_array_find(v,10);
}