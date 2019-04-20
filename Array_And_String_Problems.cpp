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
auto m=ceil(n/(double)numRows);
vector<string> v(numRows,string(m,' '));
for(int i=0;i<=n-1;i+=(2*numRows-2)){
    int j=i;
    while(j<numRows){
        
    }
}
}

int main(){
    string s="abcabcbb";
    cout<<ceil(41/4.0);
    return 0;
}
