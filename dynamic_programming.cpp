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

int main(){
    cout<<longestPalindrome("aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa");
}