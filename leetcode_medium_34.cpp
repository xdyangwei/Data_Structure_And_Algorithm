//
// Created by 杨炜 on 2019/4/27.
//
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
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

int main(){
    vector<int> v{10,1,2,7,6,1,5};
    auto x=combinationSum2(v,8);
    for(auto xx:x){
        for(auto xxx:xx)
            cout<<xxx<<" ";
        cout<<endl;
    }
}
