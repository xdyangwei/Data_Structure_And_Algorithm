//
// Created by 杨炜 on 2019/3/15.
//
#include <iostream>
#include <memory>
#include<stack>
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

int main(){
    List<int> l;List<int> l1;
    //l.deletefrom(1);
    //reverse_output_list(l.head);
    for(auto i=0;i<2;i++){
        auto x=new ListNode<int>(2);
        l.addtotail(x);
        l1.addtotail(new ListNode<int>(1));
    }
    for(auto i=0;i<3;i++){
        auto x=new ListNode<int>(3);
        l.addtotail(x);
        l1.addtotail(new ListNode<int>(11));
    }
    l.addtotail(new ListNode<int>(4));
    l.addtotail(new ListNode<int>(5));
    l.addtotail(new ListNode<int>(5));
    l.addtotail(new ListNode<int>(6));
    l.addtotail(new ListNode<int>(8));
    l.addtotail(new ListNode<int>(8));
    l.addtotail(new ListNode<int>(9));
    l.addtotail(new ListNode<int>(9));
    l.addtotail(new ListNode<int>(10));
    //auto x=recursive_reverse_list(l.head);
    auto x=l.head;
    auto y=l1.head;
    auto z=merge_sorted_list(x,y);
    while(z!= nullptr){
        std::cout<<z->data<<" ";
        z=z->next;
    }
}
