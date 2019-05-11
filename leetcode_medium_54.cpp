//
// Created by 杨炜 on 2019/5/4.
//
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

//螺旋矩阵，给定一个包含 m x n 个元素的矩阵（m 行, n 列），
//请按照顺时针螺旋顺序，返回矩阵中的所有元素。
//思路：使用for循环输出
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if(matrix.empty())
        return vector<int>();
    auto m=matrix.size();
    auto n=matrix[0].size();
    if(m==1){
        return vector<int>(matrix[0].begin(),matrix[0].end());
    }
    vector<int> v;
    if(n==1){
        for(auto xx:matrix)
            v.push_back(xx[0]);
        return v;
    }
    int i=0,j=0;auto m1=m;auto n1=n;
    for(;i<m/2&&j<n/2;i++,j++) {
        for (int k=j; k < n - j;k++) {
            v.push_back(matrix[i][k]);
        }
        for(int l=i+1;l<m-i;l++){
            v.push_back(matrix[l][n-j-1]);
        }
        for(int z=n-j-2;z>=j;z--){
            v.push_back(matrix[m-i-1][z]);
        }
        for(int y=m-j-2;y>i;y--){
            v.push_back(matrix[y][j]);
        }
        m1-=2;n1-=2;
    }
    if((m1%2==1||n1%2==1)&&(m1>=2||n1>=2)) {
        if (i < m / 2) {
            auto z=i;
            while (z <=m-i-1) {
                v.push_back(matrix[z][j]);
                z++;
            }
        } else if (j < n / 2) {
            auto z=j;
            while (z <= n-j-1) {
                v.push_back(matrix[i][z]);
                z++;
            }
        } else if (i == m / 2 && j == n / 2) {
            v.push_back(matrix[i][j]);
        }
    }
    if(m1==1&&n1==1)
        v.push_back(matrix[i][j]);
    return v;
}

//No.55 medium 给定一个非负整数数组，你最初位于数组的第一个位置。
//数组中的每个元素代表你在该位置可以跳跃的最大长度。
//判断你是否能够到达最后一个位置。
//思路：使用动态规划，使用一个变量表示当前能走的最大值，在遍历这个数组过程中
//如果该变量递减后的值小于当前遍历值，则将当前遍历值赋值给这个变量，当此变量==0时表示无法继续走下去了表示到不了终点
bool canJump(vector<int>& nums) {
    int len = nums.size();
    if (len == 0)
        return true;
    int mid_num = 0;
    mid_num = nums[0];
    for (int i = 1; i < len;++i)
    {
        if (mid_num < 1)
            return false;
        mid_num--;
        mid_num = max(mid_num,nums[i]);
    }
    return true;
}

//No.56 medium 给出一个区间的集合，请合并所有重叠的区间。
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> v;
    sort(intervals.begin(),intervals.end(),[](vector<int> v1,vector<int> v2){
        return v1[0]<v2[0];
    });
    for(auto it=intervals.begin();it!=intervals.end();){
        auto x=(*it)[1];int Max=x;
        auto it1=find_if(it,intervals.end(),[&](vector<int> v){
            if(v[0]>Max)
                return true;
            else
                Max=max(Max,v[1]);
            return false;
        });
        vector<int> v1;
        if(it1!=it+1){
            v1.push_back((*it)[0]);v1.push_back(Max);
            v.push_back(v1);
            it=it1;
        }else{
            v.push_back(*it);
            it++;
        }

    }
    return v;
}

//No.58 easy 给定一个仅包含大小写字母和空格 ' ' 的字符串，
// 返回其最后一个单词的长度。
//思路：从字符串末尾开始遍历到第一个空格为止
int lengthOfLastWord(string s) {
    if(s.empty())
        return 0;
    auto n=s.size();
    auto ss=s;
    for(int i=n-1;i>=0;i--) {
        if (s[i]==' ')
            ss.pop_back();
        else{
            break;
        }
    }
    auto x=ss.rfind(' ');
    if(x==string::npos)
        return ss.size();
    else{
        return ss.size()-x-1;
    }
}

//No.59 medium 给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，
//且元素按顺时针顺序螺旋排列的正方形矩阵。
vector<vector<int>> generateMatrix(int n) {
    deque<int> v1;
    vector<vector<int>> v(n,vector<int>(n,0));
    for(int i=1;i<=pow(n,2);i++)
        v1.push_back(i);
    int i=0;
    while(!v1.empty()){
        for(int j=i;j<n-i;j++) {
            v[i][j] = v1.front();
            v1.pop_front();
        }
        for(int j=i+1;j<n-i;j++){
            v[j][n-i-1]=v1.front();
            v1.pop_front();
        }
        for(int j=n-i-2;j>=i;j--){
            v[n-i-1][j]=v1.front();
            v1.pop_front();
        }
        for(int j=n-i-2;j>=i+1;j--){
            v[j][i]=v1.front();
            v1.pop_front();
        }
        i++;
    }
    return v;
}

//No.60 medium 给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。
//按大小顺序列出所有排列情况，并一一标记
//给定 n 和 k，返回第 k 个排列
//递归版本
static vector<string> v1;
void recursive_permutation(string& s,int n,vector<int>& v){
    if(n==s.size())
        return ;
    auto m=v.size();
    for(int i=0;i<m;i++){
        s[n]=v[i]+'0';
        auto x=v[i];
        auto it=find(v.begin(),v.end(),v[i]);
        v.erase(it);
        if(n==s.size()-1)
            v1.push_back(s);
        recursive_permutation(s,n+1,v);
        v.insert(it,x);
    }
}
string getPermutation(int n, int k) {
    string s(n,'0');
    vector<int> v;
    for(int i=1;i<=n;i++)
        v.push_back(i);
    recursive_permutation(s,0,v);
    return v1[k-1];
}

//使用next_permautation版本
string getPermutation_1(int n, int k){
    vector<char> v;
    for(int i=1;i<=n;i++)
        v.push_back(i+'0');
    while(k!=1){
        next_permutation(v.begin(),v.end());
        k--;
    }
    string s="";
    for(auto xx:v)
        s.push_back(xx);
    return s;
}

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

//No.61 medium 给定一个链表，旋转链表，
//将链表每个节点向右移动 k 个位置，其中 k 是非负数。
ListNode* rotateRight(ListNode* head, int k) {
    if(head== nullptr)
        return nullptr;
    int i=1;
    auto p=head,q=head,y=head;
    while(head->next!= nullptr){
        i++;
        head=head->next;
    }
    if(k>=i){
        k=k%i;
    }
    if(k==0)
        return p;
    auto x=k;
    while(x--){
        p=p->next;
    }
    while(p->next!= nullptr){
        p=p->next;
        q=q->next;
    }
    auto z=q->next;
    q->next= nullptr;
    p->next=y;
    return z;
}

//No.62 medium 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
//问总共有多少条不同的路径？
int uniquePaths(int m, int n) {
    vector<vector<int>> v(m+1,vector<int>(n+1,0));
    for(int i=0;i<=m;i++){
        v[i][n]=1;
    }
    for(int i=0;i<=n;i++){
        v[m][i]=1;
    }
    for(int i=m-1;i>=1;i--){
        for(int j=n-1;j>=1;j--){
            v[i][j]=v[i+1][j]+v[i][j+1];
        }
    }
    return v[1][1];
}

//No.63 medium 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
//现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    auto m=obstacleGrid.size();
    if(!m)
        return 0;
    auto n=obstacleGrid[0].size();
    vector<vector<int>> v(m,vector<int>(n,0));
    int flag=0;
    for(int i=m-1;i>=0;i--){
        if(obstacleGrid[i][n-1]==1){
            flag=i+1;break;
        }
    }
    for(int i=flag;i<m;i++)
        v[i][n-1]=1;
    flag=0;
    for(int i=n-1;i>=0;i--){
        if(obstacleGrid[m-1][i]==1){
            flag=i+1;break;
        }
    }
    for(int i=flag;i<n;i++)
        v[m-1][i]=1;
    for(int i=m-2;i>=0;i--){
        for(int j=n-2;j>=0;j--){
            if(obstacleGrid[i][j]==1)
                v[i][j]=0;
            else{
                v[i][j]=v[i+1][j]+v[i][j+1];
            }
        }
    }
    return v[0][0];
}

//No.66 easy 给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。
//最高位数字存放在数组的首位， 数组中每个元素只存储一个数字。
vector<int> plusOne(vector<int>& digits) {
    auto n=digits.size();
    if(!n)
        return vector<int>();
    auto x=find_if(digits.rbegin(),digits.rend(),[](int a){
        return a!=9;
    });
    if(x==digits.rend()){
        digits.clear();
        digits.push_back(1);
        while(n--)
            digits.push_back(0);
    }else if(x==digits.rbegin()){
     digits[n-1]+=1;
    }else{
        (*x)+=1;
        for(auto it=digits.rbegin();it!=x;it++)
            (*it)=0;
    }
    return digits;
}

//No.67 easy 给定两个二进制字符串，返回他们的和（用二进制表示）。
//输入为非空字符串且只包含数字 1 和 0。
string addBinary(string a, string b) {
    auto m=a.size();
    auto n=b.size();
    auto x=max(m,n)+1;
    string s(x,'0');
    int i,j,k;
    for(i=m-1,j=n-1,k=x-1;i>=0&&j>=0;i--,j--,k--){
        if(a[i]=='0'||b[j]=='0'){
            if(s[k]=='1'){
                if(a[i]=='0'&&b[j]=='0')
                    s[k]='1';
                else{
                    s[k]='0';
                    s[k-1]+=1;
                }
            }else{
            s[k]+=(a[i]-'0'+b[j]-'0');
            }
        }
        else{
            if(s[k]=='1')
                s[k-1]+=1;
            else {
                s[k - 1] += 1;
                s[k]='0';
            }
        }
    }
    if(i>=0){
        while(i>=0){
            if(s[k]=='1'&&a[i]=='1'){
                s[k]='0';
                s[k-1]+=1;
            }else{
            s[k]+=(a[i]-'0');}
            i--;k--;
        }
    }
    if(j>=0){
        while(j>=0){
            if(s[k]=='1'&&b[j]=='1') {
                s[k] = '0';
                s[k-1]+=1;
            } else{
            s[k]+=(b[j]-'0');}
            j--;k--;
        }
    }
    if(s[0]=='0')
        return s.substr(1);
    return s;
}

//No.69 easy 实现 int sqrt(int x) 函数。
//计算并返回 x 的平方根，其中 x 是非负整数。
//由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。
int mySqrt(int x) {
    if(x==0)
        return 0;
    long y=1;
    long answer=0;
    long start=0,end=0;
    for(long i=0;i<=31;i++){
        long z=y<<i;
        if(z*z==x){
            answer=z;
            break;
        }else if(z*z<x){
            auto zz=z<<1;
            if(zz*zz>x){
                start=z;
                end=zz;
                break;
            }else{
                continue;
            }
        }
    }
    if(answer!=0)
        return answer;
    for(auto i=start;i<=end;i++){
        if(i*i<x&&(i+1)*(i+1)>x){
            answer=i;
            break;
        }
    }
    return answer;
}

//No.70 easy 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
//每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
//思路：动态规划
int climbStairs(int n) {
    vector<int> v(n+1,0);
    v[0]=1;
    v[1]=1;
    for(int i=2;i<=n;i++){
        v[i]=v[i-1]+v[i-2];
    }
    return v[n];
}
int main(){
    cout<<climbStairs(5);
}
