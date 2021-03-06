//
// Created by 杨炜 on 2019/4/27.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

//No.34 medium 给定一个按照升序排列的整数数组 nums，和一个目标值 target。
//找出给定目标值在数组中的开始位置和结束位置。如果不存在则返回[-1,-1]
//你的算法时间复杂度必须是 O(log n) 级别。
//思路：使用二分查找找到第一个和最后一个位置，第一个位置当前下标下值=target，前一个!=target
//最后一个当前=target，后一个不等于target
int find_first(vector<int>& nums, int target){
    int end=nums.size()-1;
    int start=0;
    int x=-1;
    while(start<=end){
        auto middle=(start+end)/2;
        if(nums[middle]==target){
            if(middle==0){
                x=0;
                break;
            }else{
                if(nums[middle-1]!=target){
                    x=middle;
                    break;
                } else{
                    end=middle-1;
                }
            }
        }else if(nums[middle]>target){
            if(middle>=1)
            end=middle-1;
            else
                break;
        }
        else {
            if(middle<nums.size()-1)
            start = middle + 1;
            else
                break;
        }
    }
    return x;
}

int find_last(vector<int>& nums, int target){
    int end=nums.size()-1;
    int start=0;
    int x=-1;
    while(start<=end){
        auto middle=(start+end)/2;
        if(nums[middle]==target){
            if(middle==nums.size()-1){
                x=middle;
                break;
            }else{
                if(nums[middle+1]!=target){
                    x=middle;
                    break;
                } else{
                    start=middle+1;
                }
            }
        }else if(nums[middle]>target){
            if(middle>=1)
                end=middle-1;
            else
                break;
        }
        else {
            if(middle<nums.size()-1)
                start = middle + 1;
            else
                break;
        }
    }
    return x;
}

vector<int> searchRange(vector<int>& nums, int target) {
    auto x=find_first(nums,target);
    auto y=find_last(nums,target);
    vector<int> v;v.push_back(x);v.push_back(y);
    return v;
}

//No.35 easy 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
//如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
//思路：使用二分查找如果找到就返回下标，如果查找完后未有有效下标则查找其插入位置
int searchInsert(vector<int>& nums, int target) {
    if(nums.empty())
        return 0;
    auto end=nums.size()-1;
    auto start=0;auto x=-1;
    while(start<=end){
        auto middle=(start+end)/2;
        if(nums[middle]==target){
            x=middle;break;
        }else if(nums[middle]<target){
            if(middle<nums.size()-1) {
                if (nums[middle+1]>target){
                    x=middle+1;break;
                }else{
                    start=middle+1;
                }
            } else{
                x=nums.size();
                break;
            }
        }else{
            if(middle>=1){
                if(nums[middle-1]<target){
                    x=middle;break;
                } else{
                    end=middle-1;
                }
            }else{
                x=0;
                break;
            }
        }
    }
    return x;
}

//No.36 medium 判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
//数字 1-9 在每一行只能出现一次。数字 1-9 在每一列只能出现一次。
//数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
//思路：使用map来判断是否有重复元素，有则跳出循环返回失败
bool isValidSudoku(vector<vector<char>>& board) {
    bool flag= true;
    for(int i=0;i<board.size();i++){
        auto x=board[i];std::map<char,int> m;
        for(auto xx:x){
            if(xx!='.'){
                if(m[xx]!=0){
                    flag= false;
                    break;
                }else{
                    m[xx]+=1;
                }
            }
        }
        if(flag== false)
            break;
    }
    if(flag== false)
        return false;
    for(int j=0;j<board[0].size();j++){
        map<char,int> m;
        for(int i=0;i<board.size();i++){
            if(board[i][j]!='.'){
                if(m[board[i][j]]!=0){
                    flag= false;
                    break;
                }else{
                    m[board[i][j]]+=1;
                }
            }
        }
        if(flag== false)
            break;
    }
    if(flag== false)
        return false;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            map<char,int> m;
            for(int k=0;k<3;k++){
                for(int m1=0;m1<3;m1++) {
                    if(board[k + 3 * i][m1 + 3 * j]!='.'){
                        if (m[board[k + 3 * i][m1 + 3 * j]] != 0) {
                            flag = false;
                            break;
                        } else {
                            m[board[k + 3 * i][m1 + 3 * j]] += 1;
                        }
                    }
                }
            }
            if(flag==false)
                break;
        }
        if(flag== false)
            break;
    }
    if(flag== false)
        return false;
    return flag;
}

//No.38 easy 报数序列是一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。
//思路：使用循环根据前一个序列得到下一个序列
string countAndSay(int n) {
    vector<string> v(n+1,"");
    v[1]="1";
    for(int i=2;i<=n;i++){
        auto x=v[i-1];
        auto y=x[0];
        int start=0;
        auto it=x.find_first_not_of(y);
        string s="";
        if(it==string::npos){
            s+=string(1,v[i-1].size()+'0');
            s+=y;
        }
        while(it!=string::npos){
            s+=string(1,it-start+'0');
            s+=x[it-1];
            start=it;
            it=x.find_first_not_of(x[it],it);
        }
        auto it1=x.find_last_not_of(x[x.size()-1]);
        if(it1!=string::npos) {
            s += string(1, x.size() - 1 - it1 + '0');
            s += x[x.size()-1];
        }
        v[i]=s;
    }
    return v[n];
}

//No.39 medium 给定一个无重复元素的数组 candidates 和一个目标数 target ，
//找出 candidates 中所有可以使数字和为 target 的组合。candidates 中的数字可以无限制重复被选取。
//思路：使用递归的思想，遍历原数组过程中将target减去当前的值，接着寻找此时有没有对应差值的组合
//有的话就直接进行插入，没的话就进行递归
static vector<vector<int>> v1;
void recursive_sum(vector<int>& v,vector<int>& candidates,int target,int pos){
    for(int i=pos; i<candidates.size(); i++)
    {
        if(target-candidates[i]==0){
            v.push_back(candidates[i]);
            v1.push_back(v);
            v.pop_back();
        }
        if(target-candidates[i]>0){
            v.push_back(candidates[i]);
            recursive_sum(v,candidates, target-candidates[i],i);
            v.pop_back();
        }
    }
}

void recursive_sum1(vector<int>& v,vector<int>& candidates,int target,int pos){
    if(target==0){
        v1.push_back(v);
    }
    if(target>0){
        for(int i=pos;i<candidates.size();i++){
            v.push_back(candidates[i]);
            recursive_sum1(v,candidates,target-candidates[i],i);
            v.pop_back();
        }
    }

}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    if(candidates.empty())
        return vector<vector<int>>();
    sort(candidates.begin(),candidates.end());
    if(candidates[0]>target)
        return vector<vector<int>>();
    vector<int> v;
    recursive_sum1(v,candidates,target,0);
    set<vector<int>> ss;
    for(auto &xx:v1){
        sort(xx.begin(),xx.end());
        ss.insert(xx);
    }
    return vector<vector<int>>(ss.begin(),ss.end());
}

//No.40 medium 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
//candidates 中的每个数字在每个组合中只能使用一次。
//思路：使用递归，遍历原数组过程中将target减去当前的值，接着寻找此时有没有对应差值的组合，与上一题区别在于不能包含重复的元素
//这一点可以每次找自己身后的元素或者每次递归都将本元素从数组中删除
static vector<vector<int>> v2;
void recursive_sum2(vector<int>& v,vector<int>& candidates,int target,int pos){
    if(target==0)
        v2.push_back(v);
    if(target>0){
        for(int i=pos;i<candidates.size();i++){
            v.push_back(candidates[i]);
            recursive_sum2(v,candidates,target-candidates[i],i+1);
            v.pop_back();
        }
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    if(candidates.empty())
        return vector<vector<int>>();
    sort(candidates.begin(),candidates.end());
    if(candidates[0]>target)
        return vector<vector<int>>();
    vector<int> v;
    recursive_sum2(v,candidates,target,0);
    set<vector<int>> ss;
    for(auto &xx:v2){
        sort(xx.begin(),xx.end());
        ss.insert(xx);
    }
    return vector<vector<int>>(ss.begin(),ss.end());
}

//No.43 medium 给定两个以字符串形式表示的非负整数 num1 和 num2，
//返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
//思路：使用每一位相乘的原则，然后再将结果相加
string eachmultiply(string num1,char c){
    auto n=num1.size();
    string s(n+1,'0');
    for(int i=n-1;i>=0;i--){
        auto x=(c-'0')*(num1[i]-'0');
        auto z=s[i+1]+x-'0';
        s[i+1]=((z)%10+'0');
        s[i]+=z/10;
    }
    auto x=find_if(begin(s),end(s),[](char a){
       return  a!='0'? true: false;
    });
    return string(x,s.end());
}

string plusstring(string s1,string s2){
    //s2.push_back('0');
    auto m=s1.size();auto n=s2.size();
    string s(max(m,n)+1,'0');
    auto z=s.size()-1;
    int i=m-1,j=n-1,k=z;
    for(;i>=0&&j>=0;i--,j--,k--){
        auto x=s1[i]-'0'+s2[j]-'0';
        auto y=x+s[k]-'0';
        s[k]=y%10+'0';
        s[k-1]+=y/10;
    }
    if(i>=0){
        for(;i>=0;i--,k--) {
            auto x=s[k]-'0'+s1[i]-'0';
            s[k] =(x%10)+'0';
            s[k-1]+=x/10;
        }
    }
    if(j>=0){
        for(;j>=0;j--,k--){
            auto x=s[k]-'0'+s2[j]-'0';
            s[k] =(x%10)+'0';
            s[k-1]+=x/10;
        }
    }
    auto x=find_if(begin(s),end(s),[](char a){
        return  a!='0'? true: false;
    });
    return string(x,s.end());
}
string multiply(string num1, string num2) {
    if(num1.empty()||num2.empty())
        return "";
    if(num1[0]=='0'||num2[0]=='0')
        return "0";
    auto n=num2.size();
    string s=eachmultiply(num1,num2[n-1]);
    for(int i=n-2;i>=0;i--){
        auto x=eachmultiply(num1,num2[i]);
        auto y=n-1-i;
        while(y--){
        x.push_back('0');}
        s=plusstring(s,x);
    }
    return s;
}

//No.46 medium 给定一个没有重复数字的序列，返回其所有可能的全排列。
//思路：使用递归
static vector<vector<int>> v3;
void recursive_permute(vector<int>& v,vector<int>& nums,int pos){
    if(pos==nums.size()){
        v3.push_back(v);
    }else {
        for (int i = 0; i < nums.size(); i++) {
            if(find(v.begin(),v.end(),nums[i])==v.end()){
            v[pos]=nums[i];
            recursive_permute(v,nums,pos+1);
            }
            v[pos]=INT32_MIN;
        }
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<int> v(nums.size(),INT32_MIN);
    recursive_permute(v,nums,0);
    return v3;
}

//No.47 medium 给定一个可包含重复数字的序列，返回所有不重复的全排列。
//思路：使用递归，每次都去掉当前加入序列的元素进行下一次递归，然后再将其添加回来,然后使用set去重
static vector<vector<int>> v4;
void recursive_permuteUnique(vector<int>& v,vector<int>& nums,int pos,int n){
    if(pos==n){
        v4.push_back(v);
    } else{
        for(int i=0;i<nums.size();i++){
            v[pos]=nums[i];
            nums.erase(nums.begin()+i);
            recursive_permuteUnique(v,nums,pos+1,n);
            nums.insert(nums.begin()+i,v[pos]);
        }
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<int> v(nums.size(),INT32_MIN);
    recursive_permuteUnique(v,nums,0,nums.size());
    set<vector<int>> s(v4.begin(),v4.end());
    vector<vector<int>> v1(s.begin(),s.end());
    return v1;
}

//No.49 medium 给定一个字符串数组，将字母异位词组合在一起。
// 字母异位词指字母相同，但排列不同的字符串。
//思路：使用unordered_map去重
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> result;
    unordered_map<string, vector<string>> p;
    string s;
    for (auto it= strs.begin(); it !=strs.end(); it ++)
    {
        s= *it;
        sort(s.begin(), s.end());
        p[s].push_back(*it);

    }
    for (auto it: p)
    {
        result.push_back(it.second);
    }
    return result;
}

//No.50 medium 实现 pow(x, n) ，即计算 x 的 n 次幂函数。
//思路：使用折半计算，每次将n除以2，然后x本身乘以x变为原来的平方在进行计算
//奇数时需要将结果先乘以自身直至n为0
double myPow(double x, int n) {
    double res = 1.0;
    for(int i = n; i != 0; i /= 2){
        if(i % 2 != 0){
            res *= x;
        }
        x *= x;
    }
    return  n < 0 ? 1 / res : res;
}

//递归解法
double recursive_myPow(double x,int n,double res){
    if(n==0)
        return res;
    if(n%2==0){
        return recursive_myPow(x*x,n/2,res);}
    if(n%2!=0){
        res*=x;
    return recursive_myPow(x*x,n/2,res);}
}

double myPow1(double x, int n){
    double res=1.0;
    if(n==0)
        return 1;
    if(x==1.0)
        return 1.0;
    if(n>0){
        return recursive_myPow(x,n,res);}
    if(n<0){
        long y=abs((long)n);
        return 1/recursive_myPow(x,y,res);
    }
    return 0;
}

