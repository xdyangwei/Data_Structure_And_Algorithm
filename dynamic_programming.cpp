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

//给定一个无序的整数数组，找到其中最长上升子序列的长度。
//思路：利用辅助数组记录以这个下标为结束的最长上升子序列的长度，使用动态规划
int lengthOfLIS(vector<int>& nums) {
    auto n=nums.size();
    if(n<=0)
        return 0;
    vector<int> v(n,1);
    v[0]=1;
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(nums[j]<nums[i])
                v[i]=max(v[j]+1,v[i]);
        }
    }
    int Max=0;
    for(auto xx:v){
        Max=max(xx,Max);
    }
    return Max;
}

//给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j)
//范围内元素的总和，包含 i,  j 两点。
//使用动态规划
vector<int> sums;
vector<int> num;
void NumArray(vector<int>& nums) {
    auto n=nums.size();
    if(n<=0)
        return ;
    sums.resize(n);
    num=nums;
    sums[0]=nums[0];
    for(int i=1;i<sums.size();i++){
        sums[i]=sums[i-1]+nums[i];
    }
}

int sumRange(int i, int j) {
    return sums[j]-sums[i]+num[i];
}

//给定一个二维矩阵，计算其子矩形范围内元素的总和，
//该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2)。
vector<vector<int>> dp;
void NumMatrix(vector<vector<int>>& matrix) {
    int M = matrix.size();
    int N;
    if(M==0)  N = 0;
    else  N = matrix[0].size();

    dp = vector<vector<int>>(M+1, vector<int>(N+1,0));
    // dp[i][j] 表示 前i行前j列的矩形的和
    for(int i=1; i<=M; i++){
        for(int j=1; j<=N; j++){
            dp[i][j] = matrix[i-1][j-1]+dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
        }
    }
}

int sumRegion(int row1, int col1, int row2, int col2) {
    int ans = dp[row2+1][col2+1];
    ans -= dp[row1][col2+1];
    ans -= dp[row2+1][col1];
    ans += dp[row1][col1];
    return ans;
}

//给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​
//设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
//你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
//卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
//思路：DP 时间复杂度(O(n^2))
int maxProfit_1(vector<int>& prices) {
    if(prices.empty()||prices.size()==1)
        return 0;
    int n=prices.size();
    vector<int> v(n+2,0);
    for(int i=n-2;i>=0;i--){
        for(int j=i+1;j<n;j++){
            for(int k=j+2;k<n+2;k++)
            v[i]=max(v[i],prices[j]-prices[i]+v[k]);
        }
    }
    int Max=0;
    for(auto xx:v)
        Max=max(xx,Max);
    return Max;
}

//优化后的DP,将每一天的状态分为三种，分别为(除冷冻期外的)未持有状态、持有股票中和处于冷冻期
//使用二维数组表示当天分别处于这三种状态下的收益
int maxProfit_2(vector<int>& prices){
    if(prices.empty()||prices.size()==1)
        return 0;
    int n=prices.size();
    vector<vector<int>> v(n,vector<int>(3,0));
    v[0][0]=0;v[0][1]=-prices[0];v[0][2]=0;
    for(int i=1;i<n;i++){
        v[i][0]=max(v[i-1][0],v[i-1][2]);
        v[i][1]=max(v[i-1][1],v[i-1][0]-prices[i]);
        v[i][2]=v[i-1][1]+prices[i];
    }
    int Max=0;
    for(auto xx:v){
        Max=max(xx[0],Max);
        Max=max(xx[2],Max);
    }
    return Max;
}

//给定不同面额的硬币 coins 和一个总金额 amount。
//编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
//如果没有任何一种硬币组合能组成总金额，返回 -1。
//可以当成是01背包来解决，使用DP
int coinChange(vector<int>& coins, int amount) {
    if(coins.empty()||amount<0)
        return -1;
    if(amount==0)
        return 0;
    auto n=coins.size();
    vector<int> v(amount+1,1000000);
    v[0]=0;
    for(int i=1;i<=amount;i++){
        for(auto coin:coins){
            if(i-coin>=0)
                v[i]=min(v[i],v[i-coin]+1);
        }
    }
    if(v[amount]==1000000)
        return -1;
    return v[amount];
}

//递归版本,时间复杂度太高
static bool flag1= false;
int coinChange_1(vector<int>& coins, int amount) {
    if(amount==0) {
        flag1=true;
        return 0;
    }
    else if(amount<0){
        return -1;
    }
    else{
        int Min=10000000;
        for(auto xx:coins) {
            if(coinChange_1(coins,amount-xx)==-1)
                continue;
            Min = min(Min, 1 + coinChange_1(coins, amount - xx));
        }
        if(flag1)
        return Min;
        else
            return -1;
    }
}

//01背包问题再练习
//当每个商品可取数量为1时，可以使用二维数组进行限制
//当每个商品数量无限时，可以使用一维数组
int max_profit(vector<int> &cost,vector<int> &profit,int capital){
    vector<vector<int>> v(cost.size()+1,vector<int>(capital+1,0));
    for(int i=1;i<=cost.size();i++){
        for(int j=1;j<=capital;j++){
            if(j-cost[i-1]>=0){
                v[i][j]=max(v[i][j],v[i-1][j-cost[i-1]]+profit[i-1]);
            }
        }
    }
    int Max=0;
    //for(auto x:v)
        for(auto xx:v[cost.size()])
            Max=max(xx,Max);
    return Max;
}

int main(){
    vector<int> v1{15,10,12,8};
    vector<int> v2{12,8,9,5};
    cout<<max_profit(v1,v2,30);
}