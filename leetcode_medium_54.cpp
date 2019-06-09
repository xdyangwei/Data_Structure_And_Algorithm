//
// Created by 杨炜 on 2019/5/4.
//
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
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

//No.71 medium 简化路径 以 Unix 风格给出一个文件的绝对路径，你需要简化它。或者换句话说，将其转换为规范路径。
//在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..）
//表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。
string simplifyPath(string path) {
    vector<string> vec;
    int idx = 0;
    if (path[idx] == '/')
    {
        vec.push_back("/");
        idx++;
    }
    int start = 0;
    while (idx < path.size())
    {
        while (idx < path.size() && path[idx] == '/')
            idx++;
        start = idx++;
        while (idx < path.size() && path[idx] != '/')
            idx++;
        string str = path.substr(start, idx - start);
        if (str.size() > 0)
        {
            if (str == "..")
            {
                if (vec.size() > 1)
                    vec.pop_back();
            }
            else if (str != "." && str != "/")
                vec.push_back(str);
        }
    }
    string ret;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i > 1)
            ret.push_back('/');
        ret.append(vec[i]);
    }
    return ret;
}

//No.73 medium 给定一个 m x n 的矩阵，如果一个元素为 0，
//则将其所在行和列的所有元素都设为 0。请使用原地算法。
void setZeroes(vector<vector<int>>& matrix) {
    vector<pair<int,int>> v;
    if(matrix.empty()||matrix[0].empty())
        return ;
    for(int i=0;i<=matrix.size()-1;i++){
        for(int j=0;j<=matrix[0].size()-1;j++){
            if(matrix[i][j]==0)
                v.push_back(make_pair(i,j));
        }
    }
    for(auto vv:v){
        auto x=vv.first;
        auto y=vv.second;
        for(int i=0;i<matrix[0].size();i++)
            matrix[x][i]=0;
        for(int i=0;i<matrix.size();i++)
            matrix[i][y]=0;
    }
}

//No.74 medium 编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。
//该矩阵具有如下特性：
//每行中的整数从左到右按升序排列。
//每行的第一个整数大于前一行的最后一个整数。
//思路：每次和左下角或者右上角的数进行比较
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(matrix.empty()||matrix[0].empty())
        return false;
    auto m=matrix.size();
    auto n=matrix[0].size();
    bool flag= false;
    for(int i=m-1;i>=0;i--){
        if(target==matrix[i][0]){
            flag=true;
            break;
        }else if(target<matrix[i][0]){
            continue;
        }else{
            int j=1;
            for(;j<n;j++){
                if(matrix[i][j]==target){
                    flag=true;
                    break;
                }
            }
            if(flag==true||j==n)
                break;
        }
    }
    return flag;
}

//No.75 medium 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，
//使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
//此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
//思路：先算出三种颜色的数量，然后使用三指针法
void sortColors(vector<int>& nums) {
    int ptr0 = 0;                 //left of ptr is all 0
    int ptr1 = 0;                 //btw ptr0, ptr1 is 1
    int ptr2 = nums.size() - 1;   //right of ptr are all 2
    //undefined(unsorted) nums are btween ptr1 and ptr2
    while(ptr1 <= ptr2){// still have undefined numbers
        if(nums[ptr1] == 0){
            int temp = nums[ptr1];
            nums[ptr1] = nums[ptr0];
            nums[ptr0] = temp;
            //after swap, increment both
            ptr0 ++;
            ptr1 ++;
        }
        else if(nums[ptr1] == 1){
            ptr1 ++;
        }
        else{
            int temp = nums[ptr1];
            nums[ptr1] = nums[ptr2];
            nums[ptr2] = temp;
            ptr2 --;
        }

    }
}

//No.77 medium 给定两个整数 n 和 k，
//返回 1 ... n 中所有可能的 k 个数的组合。
static vector<vector<int>> v2;
void recursive_combine(int n,int k,vector<int>& v){
    if(k==0) {
        v2.push_back(v);
    }
    else {
        for (int i = n; i >= 1; i--) {
            v.push_back(i);
            recursive_combine(i-1,k-1,v);
            v.pop_back();
        }
    }
}
vector<vector<int>> combine(int n, int k) {
    vector<int> v;
    recursive_combine(n,k,v);
    return v2;
}

//No.78 medium 给定一组不含重复元素的整数数组 nums，
//返回该数组所有可能的子集（幂集）
vector<vector<int>> subsets(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result = {{}};
    for(int i = 0 ; i < n ; i++){
        int count = result.size();
        vector<vector<int>> temp(result);
        result.insert(result.end(),temp.begin(),temp.end());
        for(int j = 0 ; j < count ; j++){
            result[j].push_back(nums[i]);
        }
    }
    return result;
}

//No.82 medium 给定一个排序链表，删除所有含有重复数字的节点，
//只保留原始链表中 没有重复出现的数字。
ListNode* deleteDuplicates_head(ListNode* head){
    if(head== nullptr||head->next== nullptr)
        return head;
    else{
        auto p=head->next;
        if(p->val==head->val) {
            while (p!= nullptr&&p->val == head->val)
                p = p->next;
            head=p;
            deleteDuplicates_head(head);
        }else
            return head;
    }
}

ListNode* deleteDuplicates_noecxept(ListNode* head) {
    auto p=deleteDuplicates_head(head);
    if(p->next== nullptr||p== nullptr)
    return p;
    else{
        auto z=p;
        auto x=z->next;
        while(x!= nullptr&&x->next!= nullptr){
            auto y=x->next;
            if(y->val==x->val) {
                while (y != nullptr && y->val == x->val) {
                    y = y->next;
                }
                z->next = y;
                x = y;
            }else{
                x=x->next;
                z=z->next;
            }
        }
    }
    return p;
}

//No.83 easy 给定一个排序链表，删除所有重复的元素，
//使得每个元素只出现一次。
ListNode* deleteDuplicates(ListNode* head) {
    if(head== nullptr||head->next== nullptr)
        return head;
    auto x=head;
    while(head->next!= nullptr){
        auto p=head->next;
        while(p!= nullptr&&p->val==head->val)
            p=p->next;
        head->next=p;
        if(p!=nullptr)
            head=head->next;
    }
    return x;
}

//No.79 medium 给定一个二维网格和一个单词，找出该单词是否存在于网格中。
//单词必须按照字母顺序，通过相邻的单元格内的字母构成，
//其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
//思路：使用回朔法和递归
static vector<pair<int,int>> index;
static stack<pair<int,int>> s1;
bool recursive_backtracking(int n,int i,int j,vector<vector<char>>& board, string word,vector<vector<int>>& flag);
bool exist(vector<vector<char>>& board, string word) {
    if(word.empty()||board.empty()||board[0].empty())
        return false;
    auto m=board.size();
    auto n=board[0].size();
    vector<vector<int>> flag(m,vector<int>(n,0));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==word[0]){
                index.push_back(make_pair(i,j));
            }
        }
    }
    for(auto xx:index){
        flag[xx.first][xx.second]=1;
        s1.push(make_pair(xx.first,xx.second));
        if(recursive_backtracking(0,xx.first,xx.second,board,word,flag)){
            return true;
        }
        flag[xx.first][xx.second]=0;
        while(!s1.empty())
            s1.pop();
    }
    return false;
}


bool recursive_backtracking(int n,int i,int j,vector<vector<char>>& board, string word,vector<vector<int>>& flag){
    if(n==word.size()-1)
        return true;
    else{
        if(i-1>=0&&board[i-1][j]==word[n+1]&&flag[i-1][j]==0) {
            flag[i-1][j]=1;s1.push(make_pair(i-1,j));
            return recursive_backtracking(n + 1, i - 1, j, board,word,flag);
        }else if(j+1<board[0].size()&&board[i][j+1]==word[n+1]&&flag[i][j+1]==0){
            flag[i][j+1]=1;s1.push(make_pair(i,j+1));
            return recursive_backtracking(n+1,i,j+1,board,word,flag);
        }else if(i+1<board.size()&&board[i+1][j]==word[n+1]&&flag[i+1][j]==0){
            flag[i+1][j]=1;s1.push(make_pair(i+1,j));
            return recursive_backtracking(n+1,i+1,j,board,word,flag);
        }else if(j-1>=0&&board[i][j-1]==word[n+1]&&flag[i][j-1]==0){
            flag[i][j-1]=1;s1.push(make_pair(i,j-1));
            return recursive_backtracking(n+1,i,j-1,board,word,flag);
        }else{
            if(s1.size()==1)
                return false;
            s1.pop();
            auto x=s1.top().first;
            auto y=s1.top().second;
            if(i-1>=0&&flag[i-1][j]==1&&i-1!=x&&j!=y)
                flag[i-1][j]=0;
            if(j+1<board[0].size()&&flag[i][j+1]==1&&i!=x&&j+1!=y)
                flag[i][j+1]=0;
            if(i+1<board.size()&&flag[i+1][j]==1&&i+11!=x&&j!=y)
                flag[i+1][j]=0;
            if(j-1>=0&&flag[i][j-1]==1&&i!=x&&j-1!=y)
                flag[i][j-1]=0;
            return recursive_backtracking(n-1,x,y,board,word,flag);
        }
    }
}

//No.80 medium 给定一个排序数组，你需要在原地删除重复出现的元素，
//使得每个元素最多出现两次，返回移除后数组的新长度。
int removeDuplicates(vector<int>& nums) {
    if(nums.size()<=2)
        return nums.size();
    //auto n=nums.size();
    for(int i=2;i<nums.size();){
        if(nums[i]==nums[i-2]){
            auto y=i-2;
            nums.erase(nums.begin()+i);
        }else
            i++;
    }
    return nums.size();
}

//Huawei 实习笔试1
vector<int> str_split(string ip1){
    vector<int> v;
    auto it=ip1.find('.');
    auto first_1=stoi(ip1.substr(0,it));
    auto it2=ip1.find('.',it+1);
    auto first_2=stoi(ip1.substr(it+1,it2-it-1));
    auto it3=ip1.find('.',it2+1);
    auto first_3=stoi(ip1.substr(it2+1,it3-it2-1));
    auto first_4=stoi(ip1.substr(it3+1));
    v.push_back(first_1);v.push_back(first_2);
    v.push_back(first_3);v.push_back(first_4);
    return v;
}

string ip_and_mask(vector<int>& v1,vector<int>& v2){
    auto n=v1.size();
    string s="";
    for(int i=0;i<n;i++){
        s+=to_string(v1[i]&v2[i]);
        s+='.';
    }
    auto nn=s.size();
    return s.substr(0,nn-1);
}

void judge_ip(){
    string ip1,ip2,mask;
    cin>>ip1>>ip2>>mask;
    auto v1=str_split(ip1);
    auto v2=str_split(ip2);
    auto v3=str_split(mask);
    auto s1=ip_and_mask(v1,v3);
    auto s2=ip_and_mask(v2,v3);
    cout<<(s1==s2?1:0)<<" ";
    cout<<s1;
}

//Huawei 实习笔试2 leetcode 221
int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty())
        return 0;
    auto n = matrix.size();
    auto m = matrix[0].size();
    vector<vector<int>> v(n,vector<int>(m,0));
    for (int i = 0; i < n; i++)
        v[i][0] = matrix[i][0] - '0';
    for (int i = 0; i < m; i++)
        v[0][i] = matrix[0][i] - '0';
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (matrix[i][j] == '1') {
                if (v[i - 1][j - 1]!=0) {
                    auto x = sqrt(v[i - 1][j - 1]);
                    auto y = x;
                    int flag = 1;
                    while (x) {
                        if (matrix[i - x][j] == '0' || matrix[i][j - x] == '0')
                            flag = 0;
                        x -= 1;
                    }
                    if (flag == 1) {
                        v[i][j] = pow(sqrt(v[i - 1][j - 1]) + 1, 2);
                    }
                    else
                    {
                        int z = 1;
                        while (z != y) {
                            if (matrix[i - z][j] == '1'&&matrix[i][j - z] == '1')
                                z++;
                            else {
                                break;
                            }
                        }
                        v[i][j] = pow(z, 2);
                    }
                }
                else {
                    v[i][j] = 1;
                }
            }
        }
    }
    int max_size = 0;
    for (auto x : v)
        for (auto xx : x)
            max_size = max(max_size, xx);
    return max_size;
}

//Huawei 实习笔试3
int job_timelen(){
    int m,n;
    cin>>m>>n;
    vector<int> v;
    auto x=n;
    int y;
    while(x--){
        cin>>y;
        v.push_back(y);
    }
    sort(v.begin(),v.end());
    vector<int> vm(v.begin(),v.begin()+m);
    v.erase(v.begin(),v.begin()+m);
    int Max=0;
    while(!v.empty()) {
        for (auto &xx:vm) {
            xx -= 1;
            if (xx == 0) {
                xx = v[0];
                v.erase(v.begin());
            }
        }
        Max+=1;
    }
    sort(vm.begin(),vm.end());
    auto z=vm.size();
    return Max+vm[z-1];
}

//No.81 medium 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
//( 例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2] )。
//编写一个函数来判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。
//思路：使用二分查找
bool binary_search(vector<int>& nums, int target){
    int n=nums.size();
    int start=0,end=n-1;
    bool flag= false;
    while(start<=end){
        int mid=(start+end)/2;
        if(nums[mid]==target){
            flag= true;
            break;
        }else if(nums[mid]<target) {

            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    return flag;
}

bool search(vector<int>& nums, int target) {
    sort(nums.begin(),nums.end());
    return binary_search(nums,target);
}

//No.86 medium 给定一个链表和一个特定值 x，对链表进行分隔，
//使得所有小于 x 的节点都在大于或等于 x 的节点之前。
//你应当保留两个分区中每个节点的初始相对位置。
ListNode* partition(ListNode* head, int x) {
    vector<ListNode*> s1,s2;
    while(head!= nullptr){
    if(head->val<x)
        s1.push_back(head);
    else
        s2.push_back(head);
    head=head->next;
}
    vector<ListNode*> v;
    while(!s1.empty()){
        v.push_back(s1[0]);
        s1.erase(s1.begin());
    }
    while(!s2.empty()){
        v.push_back(s2[0]);
        s2.erase(s2.begin());
    }
    for(int i=0;i<v.size()-1;i++){
        v[i]->next=v[i+1];
    }
    v[v.size()-1]->next= nullptr;
    return v[0];
}

//No.89 medium 格雷编码是一个二进制数字系统，在该系统中，两个连续的数值仅有一个位数的差异。
//给定一个代表编码总位数的非负整数 n，打印其格雷编码序列。格雷编码序列必须以 0 开头。
//关键是搞清楚格雷编码的生成过程, G(i) = i ^ (i/2);
vector<int> grayCode(int n) {
    int size = 1<<n;
    vector<int> res(size);
    int last = 0;
    for (int i = 0; i < size; i++) {
        last = res[i] = last ^ (((i ^ (i - 1)) + 1) >> 1);
    }
    return res;
}

struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     };
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p== nullptr&&q== nullptr)
        return true;
    if(p== nullptr||q== nullptr||p->val!=q->val)
        return false;
    return isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
}

//No.90 medium 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
void dfs(vector<int>& nums,int idx,vector<vector<int>>&res,vector<int>path){
    set <int>repeat;
    if(idx>=nums.size()) return;

    repeat.insert(nums[idx]);
    path.push_back(nums[idx]);
    res.push_back(path);

    dfs(nums,idx+1,res,path);
    path.pop_back();

    while(idx<nums.size()-1&&repeat.find(nums[idx+1])!=repeat.end()) idx++;
    dfs(nums,idx+1,res,path);
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> RES={{}};
    vector<int> path;
    sort(nums.begin(),nums.end());
    dfs(nums,0,RES,path);
    return RES;
}

//No.93 medium 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
//暴力求解
static vector<string> v3;
void all_address(string& str,int n,int i){
    if(n==4){
        v3.push_back(str);
        return ;}
    else if(n==1){
        auto size=str.size();
        for(int j=1;j<size-2;j++){
            str.insert(str.begin()+j,'.');
            all_address(str,n+1,j);
            str.erase(str.begin()+j);
        }
    }else{
        auto size=str.size();
        for(int j=i+2;j<size-3+n;j++){
            str.insert(str.begin()+j,'.');
            all_address(str,n+1,j);
            str.erase(str.begin()+j);
        }
    }
}

vector<string> str_split(string str,char ch){
    vector<string> v;
    auto i=0;
    while((str.find(ch,i))!=string::npos){
        auto x=str.find(ch,i);
        v.push_back(str.substr(i,x-i));
        i=x+1;
    }
    auto x=str.rfind('.');
    v.push_back(str.substr(x+1));
    return v;
}

bool judge_ip(string str){
    if(str.size()>3||stoi(str)>255||(str.size()>1&&str[0]=='0'))
        return false;
    return true;
}

vector<string> restoreIpAddresses(string s) {
    if(s.size()<4||s.size()>12)
        return vector<string>();
    all_address(s,1,0);
    vector<string> v1;
    for(auto x:v3) {
        bool flag=true;
        auto v = str_split(x,'.');
        for(auto xx:v){
            if(judge_ip(xx)== false) {
                flag= false;
                break;
            }
        }
        if(flag==true)
            v1.push_back(x);
    }
    return v1;
}

//No.92 medium 反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
//使用栈完成
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(head->next== nullptr)
        return head;
    if(m==n)
        return head;
    auto dis=n-m;
    auto p=head;
    while(dis--)
        p=p->next;
    auto pre=new ListNode(0);
    auto yy=pre;
    pre->next=head;
    auto x=m;
    while(x--!=1){
        pre=pre->next;
        head=head->next;
        p=p->next;
    }
    auto z=p->next;
    stack<ListNode*> s1;
    while(head!=p){
        s1.push(head);
        head=head->next;
    }
    s1.push(p);
    pre->next=s1.top();
    while(s1.size()!=1&&!s1.empty()){
        auto x=s1.top();
        s1.pop();
        auto y=s1.top();
        x->next=y;
    }
    s1.top()->next=z;
    return yy->next;
}

//vivo秋招提前批，找出数组A中存在而B中不存在的数
//思路：使用set去重然后在插入，如果set的size增加则说明这个数满足题意
vector<int> single(vector<int>& v1,vector<int>& v2){
    set<int> s1(v1.begin(),v1.end());
    set<int> s2(v2.begin(),v2.end());
    vector<int> v;
    for(auto xx:s1){
        auto size1=s2.size();
        s2.insert(xx);
        if(size1==(s2.size()-1))
            v.push_back(xx);
        else
            continue;
    }
    return v;
}

//No.98 medium 给定一个二叉树，判断其是否是一个有效的二叉搜索树。
//中序遍历为升序就是符合条件的二叉搜索树
int *last=nullptr;
bool isValidBST(TreeNode* root) {
    if (root){
        if(!isValidBST(root->left)) return false;
        if (last && *last>=root->val) return false;
        last = &root->val;
        if(!isValidBST(root->right)) return false;
        return true;
    }else return true;
}

//test
int main(){
    vector<int> v1{1,2,3,5};
    vector<int> v2{2,3,4};
    auto x=single(v1,v2);
    for(auto xx:x){
        cout<<xx<<endl;
    }
}
