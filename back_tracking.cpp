//
// Created by 杨炜 on 2019/6/29.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
using namespace std;

//给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
//给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
//思路：使用回溯法求解
void recursive_letterCombinations(vector<string> &v,map<int,string>& m,string &combineation,string digits,int n){
    if(n==digits.size())
        v.push_back(combineation);
    if(n<=digits.size()-1){
        for(auto xx:m[digits[n]-'0']){
            combineation.push_back(xx);
            recursive_letterCombinations(v,m,combineation,digits,n+1);
            combineation.erase(combineation.begin()+n);
        }
    }
}

vector<string> letterCombinations(string digits) {
    map<int,string> m;
    char first='a',second='b',third='c';
    for(int i=2;i<=9;i++){
        string s="";
        s+=string(1,first);s+=string(1,second);s+=string(1,third);
        if(i==7){
        s+=string(1,third+1);
        m.insert(make_pair(i,s));
        first+=4;second+=4;third+=4;
            continue;
        }
        m.insert(make_pair(i,s));
        first+=3;second+=3;third+=3;
    }
    m[9]+=string(1,'z');
    vector<string> v;string s="";
    if(digits.empty())
        return v;
    recursive_letterCombinations(v,m,s,digits,0);
    return v;
}

//给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
//思路：使用回溯法，相当于使用三个(和三个)生成长度为6的字符串然后对其有效性进行判断
//此解法时间复杂度太高，无法100%ac
void recursive_generateParenthesis(vector<string>& v,vector<char> &parenthesis,string &str,int n,int m){
    if(n==m)
        v.push_back(str);
    if(n<m){
        for(int i=0;i<parenthesis.size();i++){
            auto xx=parenthesis[i];
            str.push_back(xx);
            parenthesis.erase(parenthesis.begin()+i);
            recursive_generateParenthesis(v,parenthesis,str,n+1,m);
            parenthesis.insert(parenthesis.begin()+i,xx);
            str.erase(str.begin()+n);
        }
    }
}

bool isValid(string s){
    stack<char> s1;
    bool flag=true;
    for(auto xx:s){
    if(xx=='(')
        s1.push(xx);
    else{
        if(s1.empty()) {
            flag = false;
            break;
        }else{
            auto pre=s1.top();
            if(pre=='(')
                s1.pop();
            else
                s1.push(xx);
        }
    }
    }
    if(!flag)
        return flag;
    else{
        if(s1.empty())
            return true;
        else
            return false;
    }
}

vector<string> generateParenthesis(int n) {
    vector<char> p;
    for(int i=0;i<n;i++){
        p.push_back('(');p.push_back(')');
    }
    vector<string> v;string s="";
    recursive_generateParenthesis(v,p,s,0,2*n);
    set<string> s1;
    for(int i=0;i<v.size();i++){
        if(isValid(v[i]))
            s1.insert(v[i]);
    }
    return vector<string>(s1.begin(),s1.end());
}

//再次使用回溯法，这次使用回溯法是在生成括号时判断能不能组成有效的括号对
//回溯法的关键：找到递归的出口； 本题的解法：只要在回溯的过程中满足左括号的数量一直大于等于右括号数量即可
void backtracing_generateParenthesis(string &str,int n,int &left,int &right,vector<string> &v){
    if(str.size()==2*n)
        v.push_back(str);
    if(left<n){
        str.push_back('(');
        left++;
        backtracing_generateParenthesis(str,n,left,right,v);
        left--;
        str.pop_back();
    }
    if(right<n&&right<left){
        str.push_back(')');
        right++;
        backtracing_generateParenthesis(str,n,left,right,v);
        right--;
        str.pop_back();
    }
}

vector<string> generateParenthesis_1(int n){
    vector<string> v;string s="";
    int left=0;int right=0;
    backtracing_generateParenthesis(s,n,left,right,v);
    return v;
}

int main(){
    auto x=generateParenthesis_1(5);
    cout<<x.size()<<endl;
    for(auto xx:x)
        cout<<xx<<endl;
    //cout<<isValid("()(())");
    return 0;
}

