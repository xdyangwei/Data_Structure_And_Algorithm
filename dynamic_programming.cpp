//
// Created by 杨炜 on 2019/4/22.
//
#include <iostream>
#include <vector>
#include <functional>
#include <map>
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

int main(){
    cout<<intToRoman(3);
}