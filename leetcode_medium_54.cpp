//
// Created by 杨炜 on 2019/5/4.
//
#include <iostream>
#include <vector>
#include <deque>
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
int main(){
    vector<int> v{5,4,0,2,0,1,0,1,0};
    cout<<canJump(v)<<endl;
}
