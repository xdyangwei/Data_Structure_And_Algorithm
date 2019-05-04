//
// Created by 杨炜 on 2019/5/4.
//
#include <iostream>
#include <vector>
using namespace std;

//螺旋矩阵，给定一个包含 m x n 个元素的矩阵（m 行, n 列），
//请按照顺时针螺旋顺序，返回矩阵中的所有元素。
//思路：使用for循环输出
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if(matrix.empty())
        return vector<int>();
    auto m=matrix.size();
    auto n=matrix[0].size();
    vector<int> v;
    for(int i=0,j=0;i<=m-i-1&&j<=n-j-1;i++,j++) {
        for (int k=j; k < n - j;k++) {
            v.push_back(matrix[i][k]);
        }
        for(int l=i+1;l<m-i&&n-j-1>j;l++){
            v.push_back(matrix[l][n-j-1]);
        }
        for(int z=n-j-2;z>=j&&m-i-1>i;z--){
            v.push_back(matrix[m-i-1][z]);
        }
        for(int y=m-j-2;y>i;y--){
            v.push_back(matrix[y][j]);
        }
    }
    return v;
}
int main(){
    vector<vector<int>> v{{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    auto x=spiralOrder(v);
    for(auto xx:x)
        cout<<xx<<" ";
    cout<<endl;
}
