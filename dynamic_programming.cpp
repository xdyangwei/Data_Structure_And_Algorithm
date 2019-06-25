//
// Created by 杨炜 on 2019/4/22.
//
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

//给定n个非负整数a1，a2，...，an，每个数代表坐标中的一个点(i, ai)。
// 在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
//思路：使用双指针分别指向第一个元素和最后一个元素，算出它俩构成容器的大小
//由于面积=底乘高，而容器的高度由二者中的较小值决定，因此如果高度较小的一个元素不动，移动另一个元素，无论如何面积减小因此应该将
//高度较小的元素移动，若是前指针向后移，若是后指针则向前移
int maxArea(vector<int>& height) {
auto n=height.size();
int Max=0;
for(int i=0,j=n-1;i<j;){
    int min_height=min(height[i],height[j]);
    Max=max(min_height*(j-i),Max);
    if(height[i]<height[j])
        i++;
    else
        j--;
}
return Max;
}

//整数转罗马数字
string intToRoman(int num) {
vector<string> v1{"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
vector<int> v{1000,900,500,400,100,90,50,40,10,9,5,4,1};
map<int,string,greater<int>> m1;
for(int i=0;i<v.size();i++){
    m1.insert(pair<int,string>(v[i],v1[i]));
}
map<int,int,greater<int>> m;
for(auto vv:v){
    int x=num/(vv);
    m.insert(pair<int,int>(vv,x));
    num=num%vv;
}
string s="";
for(auto xx:m){
    if(xx.second!=0){
        auto y=xx.second;
        while(y--){
            s+=string(m1[xx.first]);
        }
    }
}
return s;
}

int LCS_sequence(string s1,string s2){
    auto m=s1.size();
    auto n=s2.size();
    if(!m||!n)
        return 0;
    vector<vector<int>> v(m+1,vector<int>(n+1,0));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1])
                v[i][j]=v[i-1][j-1]+1;
            else
                v[i][j]=max(v[i-1][j],v[i][j-1]);
        }
    }
    return v[m][n];
}

int LCS_substring(string s1,string s2){
    auto m=s1.size();
    auto n=s2.size();
    if(!m||!n)
        return 0;
    vector<vector<int>> v(m+1,vector<int>(n+1,0));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1])
                v[i][j]=v[i-1][j-1]+1;
            else
                v[i][j]=0;
        }
    }
    int MAX=0;
    for(auto x:v)
        for(auto xx:x){
            if(xx>MAX)
                MAX=xx;
        }
    return MAX;
}

//最长回文子串
int LongestPalindromicSubstring(const string& a){
    auto n=a.size();
    if(!n)
        return 0;
    vector<int> v(n,0);
    v[0]=1;
    for(int i=1;i<n;i++){
        auto x=i-1;
        auto y=i+1;
        int count=1;
        if(x>=0&&y<n) {
            while(a[x]==a[i]){
                count++;
                x--;
            }
            while(a[y]==a[i]){
                count++;
                y++;
            }
            auto j=x;auto k=y;
            while (j >= 0 && k < n) {
                if (a[j] == a[k]) {
                    count += 2;
                    j--;k++;
                } else {
                    break;
                }
            }
        }
        v[i]=count;
    }
    int MAX=0;
    for(auto xx:v){
        if(xx>MAX)
            MAX=xx;
    }
    return MAX;
}

string longestPalindrome(string a) {
    auto n=a.size();
    if(!n)
        return 0;
    map<int,pair<int,int>> m;
    m[0]=make_pair(0,1);
    for(int i=1;i<n;i++){
        int x=i-1;int y=i+1;int count=1;
        if(x>=0&&y<n){
            while(a[x]==a[i]){
                count++;
                x--;
            }
            while(a[y]==a[i]){
                count++;
                y++;
            }
        }
        while(x>=0&&y<n){
            if(a[x]==a[y]){
                count+=2;
                x--;y++;
            }else{
                break;
            }
        }
        m.insert(make_pair(i,make_pair(x+1,count)));
    }
    int start=0,MAX=0;
    for(auto xx:m){
        if(xx.first<0)
            cout<<"hh"<<endl;
        if(xx.second.second>MAX) {
            start = xx.second.first;
            MAX=xx.second.second;
        }
    }
    return a.substr(start,MAX);
}

//No.264 medium 编写一个程序，找出第 n 个丑数。
//丑数就是只包含质因数 2, 3, 5 的正整数。
int nthUglyNumber(int n) {
    vector<int> uglyNums {1};
    int curUgly = 1;
    int u2_idx = 0, u3_idx = 0, u5_idx = 0;
    int u2_num = 0, u3_num = 0, u5_num = 0;
    while (uglyNums.size() < n) {
        u2_num = uglyNums[u2_idx] * 2;
        u3_num = uglyNums[u3_idx] * 3;
        u5_num = uglyNums[u5_idx] * 5;
        curUgly = min(min(u2_num, u3_num), u5_num);
        if (curUgly == u2_num) u2_idx++;
        if (curUgly == u3_num) u3_idx++;
        if (curUgly == u5_num) u5_idx++;
        uglyNums.push_back(curUgly);
    }
    return uglyNums[n-1];
}

//跳台阶：一只青蛙一次可以跳上1级台阶，也可以跳上2级。
//求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。
//思路：使用DP
int jumpFloor(int number) {
    if(number==1){
        return 1;
    }
    if(number==2)
        return 2;
    vector<int> v(number+1,0);
    v[1]=1;v[2]=2;
    for(int i=3;i<=number;i++){
        v[i]=v[i-1]+v[i-2];
    }
    return v[number];
}

//矩形覆盖：我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
//请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
//思路：使用DP
int rectCover(int number) {
    if(number==1){
        return 1;
    }
    if(number==2)
        return 2;
    vector<int> v(number+1,0);
    v[1]=1;v[2]=2;
    for(int i=3;i<=number;i++){
        v[i]=v[i-1]+v[i-2];
    }
    return v[number];
}

//给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
//如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。
//注意你不能在买入股票前卖出股票。
//思路：使用动态规划
int maxProfit(vector<int>& prices) {
    int now=0;
    int maxmoney=0;
    for(int i=1;i<prices.size();++i)
    {
        now+=(prices[i]-prices[i-1]);
        maxmoney=max(now,maxmoney);
        now=max(0,now);
    }
    return maxmoney;
}

//给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。
//你需要让组成和的完全平方数的个数最少。
//思路：动态规划,递归方程为f(n)=1+min(f(n-1^2),f(n-2^2)...,f(n-k^2)),其中k^2<=n，进行求解
int numSquares(int n) {
    vector<int> v(n+1,0);
    for(int i=1;i<=n;i++){
        int Min=n;
        for(int j=1;j*j<=i;j++){
            Min=min(Min,v[i-j*j]);
        }
        v[i]=1+Min;
    }
    return v[n];
}

int main(){
    cout<<numSquares(13);
}