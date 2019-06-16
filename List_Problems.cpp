//
// Created by 杨炜 on 2019/3/15.
//
#include <iostream>
#include <memory>
#include<stack>
#include <vector>

template <typename T>
class ListNode {
public:
    ListNode(T x,ListNode* y=NULL):
    data(x),next(y){}
    ListNode()= default;
    T data;
    ListNode<T>* next;
};
template <typename T>
class List{
public:
    ListNode<T>* head;
    List(ListNode<T>* x):
    head(x){}
    List():
    head(NULL){}
    bool empty(){
        return head== nullptr;
    }
    void addtotail(ListNode<T>* node){
        auto x=head;
        if(x==NULL){
            head=node;
        } else if(x->next!=NULL){
            while (x->next != NULL) {
                x = x->next;
            }
            x->next = node;
        }else{
            x->next=node;
        }
    }
    void deletefrom(T v) {
        if (head == NULL) {
            std::cerr<<"this list is empty"<<std::endl;
        } else {
            auto x = head;
            auto y = head->next;
            if (x->data == v) {
                head = y;
                delete x;
            }
            while (y != NULL) {
                if (y->data == v) {
                    x->next = y->next;
                    delete y;
                    break;
                }
                x = y;
                y = y->next;
            }
            if (y == NULL) {
                std::cerr << "this list does not have value " << v << std::endl;
            }
        }
    }
};

//reverse output list from tail to head with stack
template <typename T>
void reverse_output_list_with_stack(List<T> l){
    std::stack<ListNode<T>*> s;
    auto x=l.head;
    while(x!=NULL){
        s.push(x);
        x=x->next;
    }
    while(!s.empty()){
        std::cout<<s.top()->data<<" ";
        s.pop();
    }
}

//reverse output list from tail to head with stack without stack with recursive
template <typename T>
void reverse_output_list(ListNode<T>* node){
    if(node==NULL)
        std::cerr<<"list is empty"<<std::endl;
    else {
        if (node->next == NULL){
            std::cout<<node->data<<" ";
        }else{
            reverse_output_list(node->next);
            std::cout<<node->data<<" ";
        }
    }
}

template <typename T>
void find_last_k(ListNode<T>* node,std::size_t k){
    if(k<=0){
        std::cerr<<"the number k must bigger than 0"<<std::endl;
    }else{
        auto x=node;
        std::cout<<std::endl;
        for(;k>1&&x!=NULL;x=x->next,k--){
            //std::cout<<k<<std::endl;
        }
        if(k>1){
            std::cerr<<"the number of this list's nodes is smaller than k"<<std::endl;
        }else{
            //std::cout<<"here"<<std::endl;
            while(x->next!= nullptr){
                node=node->next;
                x=x->next;
            }
            std::cout<<node->data<<std::endl;
        }
    }
}

template <typename T>
void delete_node(ListNode<T>* &node,ListNode<T>* k){
    if(node== nullptr||k== nullptr){
        std::cerr<<"empty list or the node needed to be deleted is nullptr"<<std::endl;
    }else{
        if(node->data==k->data&&node->next== nullptr){
            node= nullptr;
        }else{
            if(node->data==k->data){
                auto x=node;
                node=node->next;
                //std::cout<<node->data<<std::endl;
                delete x;
                return ;
            }
            //std::cout<<"hh"<<std::endl;
            if(node->data!=k->data&&node->next== nullptr){
                std::cerr<<"can't find this node in this list"<<std::endl;
            } else{
                auto x=node;node=node->next;
                //std::cout<<1<<std::endl;
            while(node!= nullptr){
                if(node->data==k->data){
                    x->next=node->next;
                    //std::cout<<node->data<<std::endl;
                    delete node;
                    break;
                }
                x=node;
                node=node->next;
            }
                //std::cout<<(node== nullptr)<<std::endl;
            if(node== nullptr){
                std::cerr<<"can't find this node in this list"<<std::endl;
            }

            }
        }
    }
}

template <typename T>
void delete_repeat_ListNode(List<T> &l){
    auto x=l.head;
    if(x->next== nullptr){
        //std::cout<<x->data<<std::endl;
        ;
    }else{
        auto pre=new ListNode<T>();pre->next=x;
        auto z=pre;
        auto cur=x;auto nex=cur->next;
        while(nex!= nullptr){
            while(cur->data==nex->data&&nex!= nullptr){
                nex=nex->next;
            }
            if(cur->next!=nex){
                while(cur!=nex){
                    pre->next=cur->next;
                    delete cur;
                    cur=pre->next;
                }
                if(nex!= nullptr)
                    nex=nex->next;
            }else{
                pre=cur;
                nex=nex->next;
                cur=cur->next;
            }
        }
        l.head=z->next;
    }
}

//递归翻转链表并返回翻转后的头指针
template <typename T>
ListNode<T>* recursive_reverse_list(ListNode<T>* node){
    static auto head=node;
    if(node== nullptr){
        return nullptr;
    } else{
    if(node==head&&node->next!= nullptr){
        recursive_reverse_list(node->next)->next=node;
        node->next= nullptr;
        return head;
    }
    else if(node->next!= nullptr){
        recursive_reverse_list(node->next)->next=node;
        return node;
    }else{
        head =node;
        return node;
    }
    }
}

//判断链表是否存在环路，使用快慢指针，当快慢指针相遇时即认为链表有环路,返回相遇结点
template <typename T>
ListNode<T>* has_circle(ListNode<T>* node){
auto slowptr=node;auto fastptr=node->next;bool flag=0;
while (slowptr!= nullptr&&fastptr!= nullptr){
    if(slowptr==fastptr){
        flag=1;break;
    }
    slowptr=slowptr->next;fastptr=fastptr->next;
    if(fastptr!= nullptr)
        fastptr=fastptr->next;
}
if(flag==1)
    return slowptr;
return nullptr;
}

//要求链表环路入口，可以先求出环路的长度，由相遇结点肯定在环路内可以得出
// 等到他下次再走到这个结点时就是环路长度
template <typename T>
size_t circle_length(ListNode<T>* node){
    auto x=has_circle(node);
    if(x!= nullptr){
        auto y=x->next;size_t count=0;
        while(y!=x){
            y=y->next;
            count++;
        }
        count+=1;
        return count;
    }else{
        return 0;
    }

}

template <typename T>
ListNode<T>* circle_entrance(ListNode<T>* node){
    auto n=circle_length(node);
    if(n){
    auto first=node;auto last=first;
    while(n--){
        last=last->next;
    }
    while(last!=first){
        first=first->next;last=last->next;
    }
    return first;
    } else{
        return nullptr;
    }
}

template <typename T>
ListNode<T>* merge_sorted_list(ListNode<T>* node1,ListNode<T>* node2){
    if(node1== nullptr&&node2!= nullptr)
        return node2;
    if(node2== nullptr&&node1!= nullptr)
        return node1;
    if(node2== nullptr&&node1 ==nullptr)
        return nullptr;
    auto head=node1;
    //std::cout<<node1->data<<" "<<node2->data<<std::endl;
    if(node1->data<node2->data){
        //std::cout<<"hh"<<std::endl;
        head->next=merge_sorted_list(node1->next,node2);
    }else{
        head=node2;
        //std::cout<<"yy"<<std::endl;
        head->next=merge_sorted_list(node1,node2->next);
    }
    return head;
}

//复杂链表数据结构，除了节点值和指向下一个节点的指针外，还有一个指向随机节点的指针
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

//复制复杂链表，主要思路除了复制完节点后还要复制指向下一个节点的指针和指向随机节点的指针
//解决方法复制完节点后再一个个找到其对应的随机节点，每个节点时间复杂度为O(n)，总的时间复杂度为O(n^2)
//另一种解决方法就是将复制完的节点放在复制节点的后面，此时复制后节点对应的随机节点位置就是原对应随机节点的next节点
//即可在O(n)的时间复杂度来完成复制
RandomListNode* Clone(RandomListNode* pHead)
{
    auto p=pHead,y=pHead,z=pHead;
    while(p!= nullptr){
        auto x=new RandomListNode(0);
        x->label=p->label;
        x->next=p->next;
        p->next=x;
        p=x->next;
    }
    while(y!= nullptr){
        //std::cout<<y->label<<" "<<y->random->label<<std::endl;
        y->next->random=y->random->next;
        y=y->next->next;
        //std::cout<<y->label<<std::endl;
    }
    //std::cout<<2<<std::endl;
    pHead=pHead->next;
    while(pHead!= nullptr){
        std::cout<<pHead->label<<std::endl;
        if(pHead->next!= nullptr) {
            pHead->next = pHead->next->next;
            pHead = pHead->next;
        }else{
            pHead=pHead->next;
        }
    }
    if(z){
    return z->next;}
    else{
        return nullptr;
    }
}

//求两个链表的第一个公共结点
//思路：求出两个链表的长度，然后长的链表先走它俩的长度差然后它俩同时走，相同的节点值和next值就为第一个公共结点
template <typename T>
ListNode<T>* FindFirstCommonNode(ListNode<T>* h1,ListNode<T>* h2){
    int size1=0,size2=0;
    auto x=h1,y=h2;
    while(h1!= nullptr){
        size1++;h1=h1->next;
    }
    while (h2!= nullptr){
        size2++;h2=h2->next;
    }
    if(size1>=size2){
        auto distance=size1-size2;
        while(distance--){
            x=x->next;
        }
        while(size2--){
            if(x->data==y->data&&x->next==y->next)
                break;
            x=x->next;y=y->next;
        }
        return x;
    } else{
        auto distance=size2-size1;
        while(distance--){
            y=y->next;
        }
        while(size1--){
            if(x->data==y->data&&x->next==y->next)
                break;
            x=x->next;y=y->next;
        }
        return x;
    }
}

template <typename T>
ListNode<T>* swapPairs(ListNode<T>* head){
    if(head== nullptr||head->next== nullptr)
        return head;
    auto y=head->next->next;
    auto x=head;
    auto z=head->next;
    head=head->next;
    head->next=x;
    x->next=swapPairs(y);
    return z;
}

template <typename T>
ListNode<T>* addTwoNumbers(ListNode<T>* l1, ListNode<T>* l2){
    std::vector<T> v1;std::vector<T> v2;
    while(l1!= nullptr){
        v1.push_back(l1->data);l1=l1->next;
    }
    while(l2!= nullptr){
        v2.push_back(l2->data);l2=l2->next;
    }
    auto m=v1.size();auto n=v2.size();
    std::vector<T> v(std::max(m,n)+1,0);
    //auto z=v.size()-1;
    int i=0,j=0,k=0;
    for(;i<=m-1&&j<=n-1;i++,j++,k++){
        auto x=v1[i]+v2[j]+v[k];
        if(x>=10){
            v[k+1]+=1;
            v[k]=(x-10);
        }else{
            v[k]=x;
        }
    }
    if(i<=m-1){
        while(i!=m) {
            v[k]+=v1[i];
            if(v[k]>=10){
                v[k+1]+=1;
                v[k]-=10;
            }
            k++;i++;
        }
    }
    if(j<=n-1){
        while(j!=n){
            v[k]+=v2[j];
            if(v[k]>=10){
                v[k+1]+=1;
                v[k]-=10;
            }
            k++;j++;
        }
    }
    int zz=0;
    ListNode<T>* p=new ListNode<T>(v[zz]);
    auto pp=p;
    int y=v.size()-1;
    if(v[v.size()-1]==0)
        y-=1;
    while(zz<y){
        p->next=new ListNode<T>(v[zz+1]);
        p=p->next;
        zz++;
    }
    p->next= nullptr;
    return pp;
}

//给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
//使用双指针，一个指针指向头指针，另一个指针指向头结点后n-1个元素
//然后两个指针一起移动当后面指针指向尾元素的时候则前一个指针就指向倒数第n个节点
template <typename T>
ListNode<T>* removeNthFromEnd(ListNode<T>* head, int n){
    auto x=head;auto z=head;
    while(n!=1&&head!= nullptr){
        x=x->next;n--;
    }
    if(n>1)
        return nullptr;
    auto y=new ListNode<T>();
    y->next=head;
    //x=x->next;head=head->next;
    while(x->next!= nullptr){
        y=y->next;
        head=head->next;x=x->next;
    }
    if(head==z)
        return head->next;
    y->next=head->next;delete head;
    return z;
}

//输入一个链表，输出该链表中倒数第k个结点。
//方法1：可以利用栈这个数据结构
template <typename T>
ListNode<T>* FindKthToTail(ListNode<T>* pListHead, unsigned int k) {
    std::stack<ListNode<T>*> s1;
    while(pListHead!= nullptr){
        s1.push(pListHead);
        pListHead=pListHead->next;
    }
    if(s1.size()<k)
        return nullptr;
    else{
        auto x=pListHead;
        while(k--){
            x=s1.top();
            s1.pop();
        }
        return x;
    }
}

//输入一个链表，输出该链表中倒数第k个结点。
//方法2：利用快慢指针遍历
template <typename T>
ListNode<T>* FindKthToTail_pt(ListNode<T>* pListHead, unsigned int k) {
    auto fast=pListHead;
    while(k--&&fast!= nullptr){
        fast=fast->next;
    }
    if(k!=-1)
        return nullptr;
    while(fast!= nullptr){
        pListHead=pListHead->next;
        fast=fast->next;
    }
    return pListHead;
}

//输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。
//思路1：使用栈数据结构
template <typename T>
std::vector<int> printListFromTailToHead(ListNode<T>* head) {
    std::stack<ListNode<T>*> s1;
    while(head!= nullptr){
        s1.push(head);
        head=head->next;
    }
    std::vector<int> v;
    while(!s1.empty()){
        auto x=s1.top();
        v.push_back(x->data);
        s1.pop();
    }
    return v;
}

//输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。
//思路2：使用递归
template <typename T>
void recursive_add_from_tail_head(std::vector<int>& v,ListNode<T>* head){
    if(head== nullptr)
        return ;
    else {
        recursive_add_from_tail_head(v, head->next);
        v.push_back(head->data);
    }
}

template <typename T>
std::vector<int> printListFromTailToHead_recursive(ListNode<T>* head){
    std::vector<int> v;
    recursive_add_from_tail_head(v,head);
    return v;
}



int main(){
    ListNode<int> n1(1);
    n1.next=new ListNode<int>(2);
    n1.next->next=new ListNode<int>(3);
    n1.next->next->next=new ListNode<int>(4);
    n1.next->next->next->next=new ListNode<int>(5);
    auto x=removeNthFromEnd(&n1,5);
    while(x!= nullptr){
        std::cout<<(*x).data<<std::endl;
        x=x->next;
    }
}
