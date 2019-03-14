#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <list>

using namespace std;
//插入排序：算法复杂度为O(n^2)，稳定排序
//对于前几项已有序的序列不会重排但不能保证每个位置是在自己的最终位置上因为在最后一次
//外围for循环前每次都是局部的排序，只有最后排完n-1次后才能最终保证每个位置都是有序的
void insert_sort(vector<int> &v){
    for (int i = 1; i <v.size() ; ++i) {
        for(int j=i;j>0;j--){
            if(v[j]<v[j-1]){
                auto temp=v[j];
                v[j]=v[j-1];
                v[j-1]=temp;
            }
        }
    }
}

//选择排序，算法复杂度O(n^2),稳定排序
//外围for循环为n次，每个内围for循环找出当前最小的项，n次过后就排完了
void select_sort(vector<int> &v){
    for (int i = 0; i <v.size() ; ++i) {
        auto tmp=i;
        for (int j = i+1; j <v.size() ; ++j) {
            v[j]<v[tmp]?tmp=j:tmp=tmp;
        }
        auto x=v[i];
        v[i]=v[tmp];v[tmp]=x;
    }
}

//冒泡排序，复杂度O(n^2)，稳定排序
//每次通过n次比较，交换两个逆序数的位置，每一个得到一个当前最小值
//n次过后就有序了
void bubble_sort(vector<int> &v){
    for (int i = 0; i <v.size() ; ++i) {
        for (int j = 1; j <v.size() ; ++j) {
            if(v[j]<v[j-1]){
                auto tmp=v[j];
                v[j]=v[j-1];
                v[j-1]=tmp;
            }
        }
    }
}

//改进的冒泡排序，增加一个flag，时间复杂度依旧为O(n^2)
//每进入一次内层for循环就将flag置为false，然后内层每进行一次交换将其设为true
//当外层检测到flag为false时则表明内层未作任何交换，即这个数组已经有序，因此外层for循环也就可以直接结束了
void bubble_sort2(vector<int> &v){
    bool flag=true;
    for (int i = 0; i <v.size()&&flag ; ++i) {
        int j=1;
        for (j = 1,flag=false; j <v.size() ; ++j) {
            if(v[j]<v[j-1]){
                auto tmp=v[j];
                v[j]=v[j-1];v[j-1]=tmp;
                flag=true;
            }
        }
       // cout<<flag<<" "<<i<<endl;
    }
}

//梳排序，是基于改进冒泡排序而来的算法，在进行改进冒泡排序之前
//先将每隔step的元素排序保证相隔step的元素有序然后再进行改进后的冒泡排序
//使用这种算法最好情况下时间复杂度能到O(nlgn),由于第二阶段的改进冒泡排序最坏情况为O(n^2)
void comb_sort(vector<int> &v){
    auto n=v.size();
    while((n= static_cast<int>(n/1.3))>1){
        for (int i = 0; i <v.size() ; ) {
            if(v[i]>v[i+n]){
                auto tmp=v[i];
                v[i]=v[i+n];
                v[i+n]=v[i];
            }
            i+=n;
        }
        //cout<<n<<endl;
    }
    bubble_sort2(v);
}

//希尔排序，与梳排序类似的是将数组切分为n个子数组，然后将子数组进行排序后然后
//再进行切分数量更少的子数组进行排序直到最后子数组数量为1。切分的子数组放在一个辅助数组里面。
// 此时再排完整个数组就是有序的了
void shell_sort(vector<int> &v){
    auto n=v.size();vector<int> increase;int h;
    while((n=floor(n/3)+1)>1){
        increase.push_back(n);
    }
    increase.push_back(1);
    for (int i = 0; i <increase.size() ; ++i) {
        for (int j = 0; j <=v.size()-increase[i] ; j=j+increase[i]) {
            for (int k = j+increase[i]; k>0 ; k=k-increase[i]) {
                if(v[k]<v[k-increase[i]]){
                    auto tmp=v[k];v[k]=v[k-increase[i]];v[k-increase[i]]=tmp;
                }
            }
        }
    }
}


//快速排序：最坏时间复杂度为O(n^2)，平均时间复杂度为O(nlgn)
//主要思路在于在数组内每次选定一个基准值，比这个值小的放到他的左边，比这个值大的放到右边
//然后使用递归的思想在左边和右边的子数组再重复进行上述过程直到最后子数组大小为1为止
//编程注意点主要在于数组中交换元素时迭代的i值也要进行相应的变化，从左边移到右边时以及从右边移到左边i都需要-1
//因为数组中相应位置发生了变化，不-1的话会跳过数组中的下一个值
void quick_sort(vector<int> &v,size_t first,size_t last);
void quick_sort(vector<int> &v){
    auto n=v.size()/2;
    for (int i = 0; i <v.size() ; ++i) {
       // cout<<n<<endl;
        if(v[i]>v[n]&&i<n){
            v.insert(v.begin()+n+1,v[i]);
            v.erase(v.begin()+i);
            i--;n--;
        }
        if(v[i]<v[n]&&i>n){
            v.insert(v.begin(),v[i]);
            v.erase(v.begin()+i+1);
            i--;n++;
        }
    }
    quick_sort(v,0,n);
    quick_sort(v,n+1,v.size());
}

void quick_sort(vector<int> &v,size_t first,size_t last){
    //cout<<first<<" "<<last<<endl;
    if(last!=(first)) {
        auto n = (last + first) / 2;
        //cout<<n<<endl;
        for (int i = first; i < last; i++) {
            if (v[i] > v[n] && i < n) {
                v.insert(v.begin() + n+1, v[i]);
                v.erase(v.begin() + i);
                n--;i--;
            }
            if (v[i] < v[n] && i > n) {
                //与之前版本不同的是头迭代器需要加上first值不然又会往数组开头插入打乱顺序
                v.insert(v.begin()+first, v[i]);
                v.erase(v.begin() + i + 1);
                n++;i--;
            }
        }
        //cout<<n<<endl;
        quick_sort(v,first,n);
        quick_sort(v,n+1,last);
    }
}

//归并排序：将数组分为左右两个相同大小子数组，然后对子数组进行排序后再借助辅助数组将两个数组拼成有序大数组
//在排序过程中不断对子数组进行切分直到子数组数量为1为止
//数组复杂度为O(nlgn)
void merge(vector<int> &v,size_t first,size_t last);
void merge_sort(vector<int> &v,size_t first,size_t last){
if(first<last){
    if(v.empty()||first>last)
        return ;
    merge_sort(v,first,(last+first)/2);
    merge_sort(v,(last+first)/2+1,last);
    merge(v,first,last);
}
}
void merge(vector<int> &v,size_t first,size_t last){
    vector<int> v1;
    auto n=(last+first)/2;
    int i=first,j=n+1;
    while(i<=n&&j<=last){
        if(v[i]<=v[j]){
            v1.push_back(v[i]);
        i++;
        }
        else{
            v1.push_back(v[j]);
            j++;
        }}
        while(i<=n)
            v1.push_back(v[i++]);
        while(j<=last)
            v1.push_back(v[j++]);
        for(size_t k=0;k<v1.size();k++)
            v[k+first]=v1[k];
    }


int main() {
    vector<int> v{2,5,9,3,1,6,7,10,8,8,9,6,7};
    merge_sort(v,0,12);
    for(auto &x:v)
        cout<<x<<" ";
    //cout<<3/2<<endl;
    return 0;
}