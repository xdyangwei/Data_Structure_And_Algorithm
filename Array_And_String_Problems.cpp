//
// Created by 杨炜 on 2019/3/31.
//
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <ctime>
#include <set>
#include <algorithm>
#include <functional>
#include <cmath>
#include <memory>
#include <bits/shared_ptr.h>
#include <bitset>
#include <stack>
#include <sstream>
#include <queue>

using namespace std;
//找出数组中出现次数超过数组长度一半的数字
//然后输出，如果没有就输出0
//思路：使用暴力法不断count时间复杂度很高，而排序完了再找时间复杂度也为O(nlgn)
//因此我们可以使用快排法，已知在题目条件下这个数字必定在已排序数组的中间，因此转换为求中位数的问题
// 随机选择一个基准值快排，当排完后这个数字在n/2的下标的时候说明就是这个数字，大于n/2左边找，小于n/2右边找
int partion(vector<int> &numbers,int start,int end){
    srand(int(time(0)));
    auto random=rand()%(end-start)+start;
    auto x=numbers[random];
    //auto y=random;
    for(int i=start;i<=end;i++){
        if(numbers[i]>x&&i<random){
            auto z=numbers[i];
            numbers.erase(numbers.begin()+i);
            numbers.insert(numbers.begin()+random,z);
            i--;random--;
        }
        if(numbers[i]<x&&i>random){
            auto z=numbers[i];
            numbers.erase(numbers.begin()+i);
            numbers.insert(numbers.begin()+random,z);
            random++;
        }
    }
    return random;
}

int more_than_half(vector<int> numbers){
    if(numbers.empty())
        return 0;
    auto n=numbers.size();
    auto x=partion(numbers,0,n-1);
    while(x!=(n/2)){
        if(x<n/2){
            x=partion(numbers,x,n-1);
        }else{
            x=partion(numbers,0,x);
        }
    }
    auto count=0;
    for(auto xx:numbers){
        if(xx==numbers[x])
            count++;
    }
    if(count>n/2)
        return numbers[x];
    return 0;
}

//上题另外一种解题思路：空间换时间
//建立一个辅助map用于存放数组中每个数及其出现的次数
//遍历完一遍原数组结果就出来了
int more_than_half_with_map(vector<int> numbers){
    map<int,int> m;
    for(auto xx:numbers){
        if(m.find(xx)==m.end()){
            m.insert(make_pair(xx,1));
        } else{
            m[xx]+=1;
        }
    }
    auto n=numbers.size();
    auto x=0;bool flag= false;
    for(auto xx:m){
        if(xx.second>(n/2)){
            x=xx.first;
            flag= true;
            break;
        }
    }
    if(flag== true)
        return x;
    return 0;
}

//第三种解法，由于有一个数出现次数大于n/2，因此其余数出现次数都小于n/2
//遍历数组，当遍历到一个数字时使用一个count计数，遍历到相同数字就+1
// 当遍历到一个不是他本身的数字时-1，当count计数为0时就将count用来计数当前数字
//直到最后使得count不为0的数字
int more_than_half_with_count(vector<int> numbers){
    auto x=make_pair(numbers[0],1);
    auto n=numbers.size();
    for (int i = 1; i <=n-1 ; ++i) {
        if(numbers[i]==x.first)
            x.second+=1;
        else{
            x.second-=1;
            if(x.second==0) {
                x.first = numbers[i];
                x.second=1;
            }
        }
    }
    auto count=0;
    for(auto xx:numbers){
        if(xx==x.first)
            count++;
    }
    if(count>n/2)
        return x.first;
    return 0;
    //return x.first;
}

//找出数组中最小的K个数，与上述找出第n/2个数相似
vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
    if(input.empty()||k==0)
        return vector<int>();
    auto n=input.size();
    if(k=n)
        return input;
    if(k>n)
        return vector<int>();
    auto x=partion(input,0,n-1);
    while(x!=k-1){
        if(x>k-1){
            x=partion(input,0,x);
        }else{
            x=partion(input,x,n-1);
        }
    }
    vector<int> v;
    for(int i=0;i<=x;i++)
        v.push_back(input[i]);
    return v;
}
//第二种方案使用multiset存储k个值，当其中包含元素数量少于k时插入，当等于k时
//将遍历的当前元素与multiset中的最后一个元素比较，当比最后一个元素小时则将其插入将原来的移除
//最后便历完得到的multiset里的k个值就是我们需要的最小的k个数。
vector<int> GetLeastNumbers_Solution_with_multiset(vector<int> input, int k){
    multiset<int> s;
    for(auto xx:input){
        if(s.size()<k){
            s.insert(xx);
        }else{
            auto z=*s.rbegin();
            if(xx<z){
                s.erase(--s.end());
                s.insert(xx);
            }
        }
    }
    vector<int> v;
    for(auto xx:s)
        v.push_back(xx);
    return v;
}

//求数据流的中位数，数据个数为奇数就是中间数，偶数就是中间两个数取平均值
//暴力解法：放入一个数组中，每次排序再取中位数
static vector<int> v;
void Insert_voilent(int num){
    v.push_back(num);
}

double GetMedian_voilent(){
    sort(v.begin(),v.end());
    auto n=v.size();
    if(n&1)
        return v[n/2];
    return (v[n/2]+v[n/2-1])/2.0;
}

//快排思路：使用快排思路找出中位数，平均时间为O(lgn)，最坏时间为O(n)
// 实现代码上述已写，在此不再赘述
// 利用堆的思路：将原数组分为两个相同个数或者数量相差为1的子数组
// 前面为最大堆，后面为最小堆，构造完成后数组数量为奇数中位数就是其中某一个,向最小堆插入
//为偶数的话就是二者相加取平均值，向最大堆插入，如果发现此时数比最小堆中的值大就将其插入最小堆，把原先最小堆的堆顶元素插入最大堆
vector<int> min_heap;
vector<int> max_heap;
void Insert_heap(int num){
    //cout<<min_heap.size()+max_heap.size()<<endl;
    if(((min_heap.size()+max_heap.size())&1)==0){
        //cout<<"here1";
        if(!max_heap.empty()){
            auto x=max_heap[0];
            if(num<x){
                min_heap.push_back(x);
               // max_heap.erase(max_heap.begin());
               pop_heap(max_heap.begin(),max_heap.end());
               max_heap.pop_back();
                max_heap.push_back(num);
                push_heap(max_heap.begin(),max_heap.end());
                push_heap(min_heap.begin(),min_heap.end(),greater<int>());
            }else{
                min_heap.push_back(num);
                push_heap(min_heap.begin(),min_heap.end(),greater<int>());
            }
        } else{
            //cout<<"here2";
            min_heap.push_back(num);
            push_heap(min_heap.begin(),min_heap.end(),greater<int>());
        }
    }else{
            auto x = min_heap[0];
            if (num > x) {
                max_heap.push_back(x);
                //min_heap.erase(min_heap.begin());
                pop_heap(min_heap.begin(),min_heap.end(),greater<int>());
                min_heap.pop_back();
                min_heap.push_back(num);
                push_heap(max_heap.begin(), max_heap.end());
                push_heap(min_heap.begin(), min_heap.end(), greater<int>());
            } else {
                max_heap.push_back(num);
                push_heap(max_heap.begin(), max_heap.end());
            }
    }
}

double GetMedian_heap(){
    if(min_heap.size()+max_heap.size()==0)
        return 0;
    if((min_heap.size()+max_heap.size())&1){
        //cout<<min_heap[0]<<endl;
        return min_heap[0];
    }else{
        /*cout<<max_heap.size()<<" "<<min_heap.size()<<endl;
        cout<<max_heap[0]<<" "<<min_heap[0]<<endl;*/
        return (min_heap[0]+max_heap[0])/2.0;
    }
}

//求和为s的连续正数序列
//思路：使用一前一后双下标，当前范围内的值小于所给值的话，后面一个下标就+1
//若大于则前面一个下标+1，当相等时就将其两个下标保存下来
vector<vector<int> > FindContinuousSequence(int sum) {
    int j=1,k=2;
    vector<vector<int>> v;
    for(j=1;k<=sum+1&&j<k;){
        auto summ=0;
        for(int i=j;i<k;i++){
            summ+=i;
        }
        if(summ>sum)
            j++;
        if(summ<sum)
            k++;
        if(summ==sum){
            if(j!=k-1){
            vector<int> v1;
            for(int z=j;z<k;z++){
                v1.push_back(z);
            }
            v.push_back(v1);}
            k++;
        }
    }
    return v;
}

//计算从1到n整数中1出现的次数
//思路：从最高位开始计算，然后次高位最后到个位,使用string会使得获取每一位的数更为方便
//出现规律：如果第 i 位(自右向左，从1开始标号)上的数字是0，则第 i 位可能出现 1 的次数由更高位决定(若没有高位，则视高位为0)，等于更高位数乘以当前位数的权重(10^i-1)
//如果第 i 位上的数字为 1，则第 i 位上出现 1 的次数不仅受更高位影响，还受低位影响(若没有低位，视低位为0)，等于更高位数乘以当前位数的权重 (10^i-1) + (低位数 + 1)
//如果第 i 位上的数字大于 1，则第 i 位上可能出现 1 的次数仅由更高位决定(若没有高位，视高位为0)，等于(更高位数 + 1)乘以当前位数的权重 (10^i-1)
int NumberOf1(string s);
int NumberOf1Between1AndN_Solution(int n)
{
    auto str=to_string(n);
    return NumberOf1(str);
}

int NumberOf1(string s){
    auto x=s.size();
    double count=0;
    if(s[0]>='2'){
        count+=pow(10,x-1);
    }else{
        count+=(stoi(s.substr(1,s.size()))+1);
    }
    int i=1;
    while(i<(x-1)){
        if(s[i]==0){
            count+=(s[i-1]*pow(10,x-i-1));
        }else if(s[i]==1){
            count+=(s[i-1]*pow(10,x-i-1)+stoi(s.substr(i+1,x))+1);
        } else{
            count+=((s[i-1]+1)*pow(10,x-i-1));
        }
    }
    if(x>=2){
    count+=(s[x-2]-'0'+1);}
    return count;
}

//请实现一个函数用来找出字符流中第一个只出现一次的字符。
// 例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。
// 当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。
//思路：使用一个顺序容器保存每个字符，然后关联容器保存字符及其出现的个数，然后找到第一个字符出现数为1的字符
static vector<char> v1;
static map<char,int> m1;
void Insert(char ch)
{
    v1.push_back(ch);
    if(m1[ch]==0){
        m1[ch]=1;
    }else{
        m1[ch]+=1;
    }
}

char FirstAppearingOnce()
{
    char a='#';
    for(auto xx:v1){
        if(m1[xx]==1)
        {a= xx;break;}
    }
    return a;
}

//0~n-1排序数组中缺失的数字
//排序好的数组使用二分查找法，首先判断中间数组下标与自身值是否一致，若一致说明缺失数字在右边，继续在右边查找
//若不一致且左边一个数值也是不一致的，说明在左边，否则说明缺少的就是该数字前一个数字
int missing_number(vector<int> v){
    auto n=v.size();
    int start=0;
    int end=n-1;
    int flag=-1;
    while(start<=end){
        int middle=(start+end)/2;
        if(v[middle]==middle)
            start=middle+1;
        else{
            if(v[middle-2]==(middle-2))
            {flag=middle-1;break;}
            else{
                end=middle-1;
            }
        }
    }
    return flag;
}

//单调递增数组中下标和数值相等的元素
//由单调递增可知使用二分查找，当所查找元素数值与下标相等时符合要求
//当数值比下标大时由单调递增可知此数值右边所有数值均大于下标，查找左边
//当数值比下标小时由单调递增可知此数值左边所有数值均小于下标，查找右边
int equal_number(vector<int> v){
    auto n=v.size();
    int start=0;
    int end=n-1;
    int x=-1;
    while(start<=end){
        int middle=(start+end)/2;
        if(middle==v[middle])
        {x=middle;break;}
        else if(middle<v[middle])
            end=middle-1;
        else{
            start=middle+1;
        }
    }
    return x;
}

//数组中除了1个数字外其余数字都出现了两次，请找出这两个只出现一次的数字
//思路：两个相同的数异或结果肯定为0，因为只有一个数字出现一次，其余都出现两次
//因此所有的数异或结果就是我们所需要找出的数字
void FindNumsAppearOnce_One(vector<int> data,shared_ptr<int> num){
    int temp=data[0];
    vector<int> data2(data.begin()+1,data.end());
    for(auto x:data2){
        temp^=x;
    }
    *num=temp;
}

//数组中除了两个数字外其余数字都出现了两次，请找出这两个只出现一次的数字
//思路：从上一题可知有两个数字出现一次，其余都出现两个因此所有数字异或完之后是这两个数字的结果
//由于这两个数字不相同，所以异或出的结果中二进制必定有一位是1，根据这一位是1或0将数组中的数分为两个子数组
//这两个不同的数肯定出现在不同子数组，而其余相同的数也将会两两出现在同一数组然后对两个子数组分别进行异或就能得到我们想要的两个数字
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2){
    int temp=data[0];
    for(auto it=data.begin()+1;it!=data.end();it++){
        temp^=(*it);
    }
    bitset<32> b(temp);
    //cout<<b.test(0)<<endl;
    int count=0;
    while(count<32){
        //cout<<count<<endl;
        if(b[count]==1){
            break;
        }
        count++;
    }
    //cout<<count<<endl;
    vector<int> v1,v2;
    for(auto x:data){
        bitset<32> b1(x);
        if(b1[count]==1)
            v1.push_back(x);
        else
            v2.push_back(x);
    }
    int temp1=v1[0];
    for(auto it=v1.begin()+1;it!=v1.end();it++)
        temp1^=(*it);
    //cout<<temp1<<endl;
    (*num1)=temp1;
    int temp2=v2[0];
    for(auto it=v2.begin()+1;it!=v2.end();it++)
        temp2^=(*it);
    (*num2)=temp2;
}

//数组中除了1个数字外其余数字都出现了三次，请找出这个只出现一次的数字
//思路：由于其他数字出现了三次因此不能使用异或，而由于其余数字出现三次因此当出现一次的数字某二进制位为0时
//其余数字的二进制位相加肯定是能被3整除的，而出现一次的数字某二进制位为1时无法被3整除，所以我们可以确定
//只出现一次的数字哪些二进制位为1，哪些二进制为0，同时也就确定了这个数字
void FindNumsAppearOnce_Of_Three(vector<int> data,shared_ptr<int> num){
    vector<int> v(32,0);
    for(auto x:data){
        bitset<32> b(x);
        for(int i=0;i<32;i++){
            if(b[i]==1)
                v[i]+=1;
        }
    }
    bitset<32> b1;
    for(int i=0;i<32;i++){
        if(v[i]%3==1)
            b1.set(i);
    }
    auto z=b1.to_ulong();
    *num=z;
}

//翻转单词顺序列,将“student. a am I”翻转为“I am a student.”
//思路：使用一个栈，栈里面存的是顺序容器，顺序容器中存的是每个单词，当每个单词读完再加上空格
string ReverseSentence(string str) {
    int start=0;
    auto it=str.find(' ');
    //cout<<it<<endl;
    stack<string> s1;
while(it!=str.npos){
    string s(str.begin()+start,str.begin()+it);
    start=it+1;
    it=str.find(' ',it+1);
    s1.push(s);
}
auto it1=str.rfind(' ');
s1.push(string(str.begin()+it1+1,str.end()));
string temp="";
while(s1.size()>1){
    auto x=s1.top();
    s1.pop();
    temp+=x;
    temp+=" ";
}
auto x=s1.top();
temp+=x;
return temp;
}

//给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值
//思路：记录下当前滑动窗口最大值和次大值的下标，然后删除的数不是当前最大值就将最大值与新添加的数进行比较
//如果删除的是最大值，就与次大值进行比较，若比次大值大则下一个滑动窗口最大值就是新加的数，否则最大值是之前的次大值
vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
    vector<int> v;
    vector<int> v1;
    if(size==0||num.size()==0||size>num.size())
        return v1;
    int max_1=0;
    for(int i=0;i<size;i++)
        max_1=(max(num[max_1],num[i])==num[i])?i:max_1;
    v.push_back(max_1);
    v1.push_back(num[max_1]);
    for(int i=1;i<num.size()-size+1;i++){
        if(v[i-1]!=(i-1)){
            if(num[v[i-1]]<num[i+size-1]){
            v.push_back(i+size-1);
            v1.push_back(num[i+size-1]);
            }
            else{
                v.push_back(v[i-1]);
                v1.push_back(num[v[i-1]]);
            }
        }else {
            int max=i;
            for (int j = i; j < (i + size); j++) {
              max=(num[j]>=num[max])?j:max;
            }
            v.push_back(max);
            v1.push_back(num[max]);
        }
    }
    return v1;
}

//给定一个字符串，请你找出其中不含有重复字符的最长子串的长度。
int lengthOfLongestSubstring(string s) {
    auto n=s.size();
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    vector<int> v(n+1,0);
    v[1]=1;v[2]=(s[0]==s[1])?1:2;
    for(int i=2;i<n;i++){
        auto x=v[i];
        auto it=s.substr(i-x,x).find(s[i]);
        auto it1=i-x+it;
        if(it1==string::npos)
            v[i+1]=v[i]+1;
        else{
            v[i+1]=i-it1;
        }
    }
    int MAX=0;
    for(auto xx:v)
        MAX=max(xx,MAX);
    return MAX;
}

//Z字变换，将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
string convert(string s, int numRows) {
auto n=s.size();
if(n==0||numRows==0)
    return "";
vector<string> v(numRows,string(n,' '));
for(int i=0,j=0;i<=n-1;){
    int k=0;
    while(k<numRows&&i<=n-1){
        v[k][j]=s[i];
        i++;k++;
    }
    //cout<<i<<endl;
    auto x=numRows-1;
    while(--x>0&&i<=n-1){
        v[x][++j]=s[i];
        i++;
    }
    j++;
    //cout<<i<<endl;
}
string ss="";
for(auto xx:v){
    ss+=xx;
}
string str="";
stringstream f(ss);
string sss;
while(f>>sss)
    str+=sss;
return str;
}

int reverse(int x){
    string s=to_string(x);
    if(s[0]>'9'||s[0]<'0')
        reverse(s.begin()+1,s.end());
    else
        reverse(s.begin(),s.end());
    int start=0;
    if(s[0]>'9'||s[0]<'0')
        start=1;
    auto it=s.find_first_not_of("0",start);
    if(it!=string::npos)
    s.erase(start,it-start);
    auto y=stol(s);
    if(y>INT32_MAX||y<INT32_MIN){
        cout<<"yes"<<endl;
        return 0;}
    return y;
}

//请你来实现一个 atoi 函数，使其能将字符串转换成整数
//首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。
//当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；
//假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
//该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。
//注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
//在任何情况下，若函数不能进行有效的转换时，请返回 0。
int myAtoi(string str) {
    if(str.empty())
        return 0;
    auto start=str.find_first_not_of(" ");
    if(start==string::npos)
        return 0;
    auto i=start;
    if(str[i]=='+'||str[i]=='-')
        i=start+1;
    while(str[i]>='0'&&str[i]<='9')
        i++;
    auto s=str.substr(start,i-start);
    if(s.empty())
        return 0;
    if(s[0]=='+'||s[0]=='-'){
        auto x=s.find_first_not_of("0",1);
        if(x!=string::npos){
        auto ss=s.substr(x);
        s=s[0]+ss;} else{
            return 0;
        }
    } else{
        auto x=s.find_first_not_of("0");
        if(x!=string::npos) {
            auto ss = s.substr(x);
            s = ss;
        }else{
            return 0;
        }
    }
    if(s[0]!='+'&&s[0]!='-'&&(s[0]>'9'||s[0]<'0'))
        return 0;
    if(s[0]=='+'||s[0]=='-'){
        if(s.size()==1||(s[1]>'9'||s[1]<'0'))
            return 0;
    }
    if(s.size()>11){
        if(s[0]=='-')
            return INT32_MIN;
        else{
            return INT32_MAX;
        }
    }
    auto z=s.find_first_not_of(" ");
    if(z==string::npos)
        return 0;
    auto y=stol(s);
    if(y>INT32_MAX)
        return INT32_MAX;
    if(y<INT32_MIN)
        return INT32_MIN;
    return y;
}

//判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
//不将整数转换为字符串来解决这个问题
bool isPalindrome(int x) {
    if(x<0)
        return false;
    stack<int> s;
    queue<int> q;
    while(x>0){
        auto y=x%10;
        s.push(y);
        q.push(y);
        x=(x-y)/10;
    }
    bool flag=true;
    while(!s.empty()){
        auto i=s.top();
        auto j=q.front();
        if(i!=j){
            flag= false;
            break;}
        s.pop();q.pop();
    }
    return flag;
}

//罗马数字转整数
int romanToInt(string s) {
    int num=0;
    vector<string> v1{"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    vector<int> v{1000,900,500,400,100,90,50,40,10,9,5,4,1};
    map<string,int> m;
    for(int i=0;i<v.size();i++){
        m.insert(pair<string,int>(v1[i],v[i]));
    }
    if(s.size()==1)
        return m[string(1,s[0])];
    for(int i=0;i<s.length();){
        if(s[i]!='I'&&s[i]!='X'&&s[i]!='C'){
            num+=m[string(1,s[i])];i++;
        } else{
            if(s[i+1]=='X'||s[i+1]=='C'||s[i+1]=='M'||s[i+1]=='V'||s[i+1]=='L'||s[i+1]=='D') {
                string s1(1,s[i]);string s2(1,s[i+1]);
                s1+=s2;
                if(m[s1]==0){
                    num+=m[string(1,s[i])];i++;
                    m.erase(s1);
                } else{
                num += m[s1];i+=2;}
            }else{
                num+=m[string(1,s[i])];i++;
            }
        }
    }
    return num;
}

//编写一个函数来查找字符串数组中的最长公共前缀。
//如果不存在公共前缀，返回空字符串 ""。
string longestCommonPrefix(vector<string>& strs) {
    if(strs.empty())
        return "";
    auto s=strs[0];int Min=s.size();
    for(auto xx:strs){
        Min=min((int)xx.size(),Min);
    }
    int Max=0;
    for(int i=0;i<Min;i++){
        bool flag=1;
        for(int j=1;j<strs.size();j++){
            if(s[i]!=strs[j][i]){
                flag=0;break;
            }
        }
        if(flag==1)
            Max++;
        else
            break;
    }
    if(Max==0)
        return "";
    return s.substr(0,Max);
}

//三数之和：给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
// 使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
//下面的是暴力做法，无法通过100%的case
vector<vector<int>>twoSum(vector<int>& nums,int num){
    vector<vector<int>> v1;
    for(int i=0;i<nums.size();i++){
        auto x=nums;x.erase(x.begin()+i);
        auto it=find(x.begin(),x.end(),num-nums[i]);
        while(it!=x.end()){
            vector<int> v;
            v.push_back(nums[i]);v.push_back(*it);
            v1.push_back(v);
            it=find(it+1,x.end(),num-nums[i]);
        }
    }
    return v1;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    auto n=nums.size();
    if(n<3)
        return vector<vector<int>>();
    vector<vector<int>> s1;
    for(auto i=nums.begin();i!=nums.end();i++){
        auto nums1=nums;
        nums1.erase(nums1.begin()+(i-nums.begin()));
        auto v=twoSum(nums1,0-(*i));
        for(auto xx:v){
            xx.push_back(*i);
            s1.push_back(xx);
        }
    }
    set<vector<int>> s2;
    for(auto &xx:s1){
        sort(xx.begin(),xx.end());
        s2.insert(xx);
    }
    s1.clear();
    for(auto xx:s2){
        s1.push_back(xx);
    }
    return s1;
}

//使用双指针的方法，先对整个进行排序，接着将自身排除产生一个新的数组，
// 然后前指针指向第一个数，后指针指向最后一个数，三者之和要是小于我们的之和则前指针向后推，大于则后指针向前推
vector<vector<int>> twosum_1(vector<int>& nums,int num){
    vector<vector<int>> v;
    auto n=nums.size();
    for(int i=0,j=n-1;i<j;){
        if(nums[i]+nums[j]==num){
            vector<int> v1;v1.push_back(nums[i]);v1.push_back(nums[j]);v.push_back(v1);
            i++;j--;
        } else if(nums[i]+nums[j]<num)
            i++;
        else
            j--;
    }
    return v;
}

vector<vector<int>> threeSum_1(vector<int>& nums) {
    auto n=nums.size();
    if(n<3)
        return vector<vector<int>>();
    sort(nums.begin(),nums.end());
    if(nums[0]>0||nums[n-1]<0)
        return vector<vector<int>>();
    if(find_if_not(nums.begin(),nums.end(),[](int a){return a==0?true:false;})==nums.end())
        return vector<vector<int>>{{0,0,0}};
    vector<vector<int>> s1;
    map<int,int> m;
    for(auto i=nums.begin();i!=nums.end();i++){
        auto nums1=nums;
        if(m[*i]==0)
            m[*i]+=1;
        else
            continue;
        nums1.erase(nums1.begin()+(i-nums.begin()));
        auto v=twosum_1(nums1,0-(*i));
        for(auto xx:v){
            xx.push_back(*i);
            s1.push_back(xx);
        }
    }
    set<vector<int>> s2;
    for(auto &xx:s1){
        sort(xx.begin(),xx.end());
        s2.insert(xx);
    }
    s1.clear();
    for(auto xx:s2){
        s1.push_back(xx);
    }
    return s1;
}


//给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，
// 使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
//思路：还是使用双指针，将排序后的数组一个指针指向第一个数，一个指针指向最后一个数，然后计算哪两个数之和与target与当前数之差最接近则输出这对组合
struct res{
    int difference;
    int a;
    int b;
    int c;
};
res* twoSumClosest(vector<int>& nums, int target){
    auto n=nums.size();
    auto x=new res;
    (*x).difference=INT32_MAX;(*x).a=INT32_MAX;(*x).b=INT32_MAX;
    for(int i=0,j=n-1;i<j;){
        if(abs(nums[i]+nums[j]-target)<(*x).difference){
            (*x).difference=abs(nums[i]+nums[j]-target);
            (*x).a=nums[i];(*x).b=nums[j];
        }
        if(nums[i]+nums[j]<target)
            i++;
        else
            j--;
    }
    return x;
}

int threeSumClosest(vector<int>& nums, int target) {
    vector<res*> v;
    sort(nums.begin(),nums.end());
    for(int i=0;i<nums.size();i++){
        auto nums1=nums;
        nums1.erase(nums1.begin()+i);
        auto x=twoSumClosest(nums1,target-nums[i]);
        x->c=nums[i];
        v.push_back(x);
    }
    sort(v.begin(),v.end(),[](res* a,res*b){
        return abs(a->difference)<abs(b->difference)?true: false;
    });
    auto z=v[0]->a+v[0]->b+v[0]->c;
    return z;
}

//给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
//思路：字母的全组合
static map<int,string> m3;
static vector<string> v3;
void init_m3(){
    vector<string> v2{"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
     vector<int> v3{2,3,4,5,6,7,8,9};
    for(int i=0;i<v3.size();i++){
        m3.insert(make_pair(v3[i],v2[i]));
    }
}
void recuresive_number(string s,int i,int n,string& str1){
    if(s.empty()){
        v3.push_back(str1);
    }
    auto x=m3[s[0]-'0'];
    auto n1=x.size();
    for(int j=0;j<n1;j++){
        str1[i]=x[j];
        recuresive_number(s.substr(1),i+1,n,str1);
    }
}

vector<string> letterCombinations(string digits) {
    auto n=digits.size();
    if(n==0)
        return vector<string>();
    string str1(n,' ');
    vector<string> v;
    auto x=digits[0]-'0';
    init_m3();
    for(int i=0;i<m3[x].size();i++){
        str1[0]=m3[x][i];
        recuresive_number(digits.substr(1),1,n,str1);
    }
    return v3;
}

//给定一个包含 n 个整数的数组 nums 和一个目标值 target，
// 判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？
// 找出所有满足条件且不重复的四元组。
//思路：固定双元素后使用双指针
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    auto n=nums.size();
    if(n<4)
        return vector<vector<int>>();
    sort(nums.begin(),nums.end());
    vector<vector<int>> v;
    for(int i=0;i<nums.size()-3;i++)
        for(int j=i+1;j<nums.size()-2;j++){
            auto t1=target-nums[i]-nums[j];
            auto start=j+1;
            auto end=nums.size()-1;
            while(start<end){
                if(nums[start]+nums[end]==t1){
                    vector<int> v1;
                    v1.push_back(nums[i]);v1.push_back(nums[j]);
                    v1.push_back(nums[start]);v1.push_back(nums[end]);
                    v.push_back(v1);
                    start++;end--;}
                else if(nums[start]+nums[end]<t1)
                     start++;
                else
                    end--;
            }
        }
    set<vector<int>> s2;
    for(auto &xx:v){
        sort(xx.begin(),xx.end());
        s2.insert(xx);
    }
    v.clear();
    for(auto xx:s2){
        v.push_back(xx);
    }
    return v;
}

//给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
//有效字符串需满足：左括号必须用相同类型的右括号闭合。
//左括号必须以正确的顺序闭合。注意空字符串可被认为是有效字符串
//思路：使用栈，若当前输入字符与栈顶字符匹配，则将栈顶元素pop，如果最后栈为空则为true，否则为false
bool isValid(string s) {
    stack<char> s1;
    if(s.empty())
        return true;
    s1.push(s[0]);
    bool flag=true;
    for(int i=1;i<s.size();i++){
        if(s[i]=='('||s[i]=='{'||s[i]=='['){
            s1.push(s[i]);
            continue;
        }else{
            if((s[i]==')'||s[i]=='}'||s[i]==']')&&s1.empty()){
                flag= false;break;
            }
            auto x=s1.top();
        if((x=='('&&s[i]==')')||(x=='['&&s[i]==']')||(x=='{'&&s[i]=='}')){
            s1.pop();
        }
        else
            s1.push(s[i]);
        }
    }
    if(s1.empty())
        return flag;
    return false;
}

//给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
vector<string> generateParenthesis(int n) {
    auto n1=n;
    vector<char> v;
    while(n1--){
        v.push_back('(');
        v.push_back(')');
    }
    sort(v.begin(),v.end());
    string str(v.begin(),v.end());
    vector<string> v1;
    if(isValid(str)==true)
        v1.push_back(str);
    while(next_permutation(v.begin(),v.end())){
        string str1(v.begin(),v.end());
        if(isValid(str1)==true)
            v1.push_back(str1);
    }
    return v1;
}

//给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
//返回被除数 dividend 除以除数 divisor 得到的商。
int divide(int dividend, int divisor) {
    int i=31;bool flag=true;
    if((dividend^divisor)<0)
        flag= false;
    long long x=abs(static_cast<long long>(dividend));
    long long y=abs(static_cast<long long>(divisor));
    if(x<y)
        return 0;
    while(i>=0){
        if((x>>i)<y)
            i--;
        else{
            break;
        }
    }
    //auto x=i;
   x-=(y<<i);
   //cout<<(divisor<<i)<<endl;
    auto z=pow(2,i);
    while(x>=y){
        x-=y;
        z++;
    }
    if(!flag)
        if(z-1>(INT32_MAX)||z<INT32_MIN)
            return INT32_MAX;
        else
            return 0-z;
    if(z>INT32_MAX||z<INT32_MIN)
        return INT32_MAX;
    else
        return z;
}

//假设按照升序排序的数组在预先未知的某个点上进行了旋转。
//( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
//搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
//你可以假设数组中不存在重复的元素。
//你的算法时间复杂度必须是 O(log n) 级别。
//思路：使用二分查找，先找出翻转后原有序数组的第一个数的位置，然后以这个点为初始值进行二分查找，
// 如果在其与数组最后一个值之间就在右边，反之在其之前一个数与第一个数之间就在左边寻找
int find_start(vector<int>& nums){
    auto end=nums.size()-1;
    auto start=0;auto x=0;
    while(start<=end){
        auto middle=(start+end)/2;
        if(nums[middle]>nums[middle+1])
        {
            x=middle+1;
            break;
        }else if(nums[middle]<nums[0]){
            end=middle-1;
        }else if(nums[middle]>nums[nums.size()-1])
            start=middle+1;
        else{
            x=-1;
            break;
        }
    }
    return x;
}

int binary_search1(vector<int>& nums,int start,int end,int target);

int search(vector<int>& nums, int target) {
    if(nums.empty())
        return -1;
    if(nums.size()==1){
        if(nums[0]==target)
            return 0;
        else{
            return -1;
        }
    }
    auto x=find_start(nums);
    if(x==-1)
        return binary_search1(nums,0,nums.size()-1,target);
    if(nums[x]==target)
        return x;
    else{
        if(nums[x]<target){
            if(x==nums.size()-1)
                return binary_search1(nums,0,x-1,target);
            if(target<=nums[nums.size()-1])
                return binary_search1(nums,x+1,nums.size()-1,target);
            else if(target<=nums[x-1])
                return binary_search1(nums,0,x-1,target);
            else
                return -1;
        }
        if(target<nums[x-1]){
            return -1;
        }
    }
}

int binary_search1(vector<int>& nums,int start,int end,int target){
    auto x=-1;
    while(start<=end){
        auto middle=(start+end)/2;
        if(nums[middle]==target){
            x=middle;break;
        }
        if(nums[middle]>target){
            end=middle-1;
        }
        if(nums[middle]<target)
            start=middle+1;
    }
    return x;
}

int main(){
    //cout<<(2147483647>>30)<<endl;
    vector<int> v{5,1,3};
    cout<<search(v,0);
    return 0;
}
