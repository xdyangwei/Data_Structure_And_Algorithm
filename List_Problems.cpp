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
void delete_node(ListNode<T>* node,ListNode<T>* k){
    if(node== nullptr||k== nullptr){
        std::cerr<<"empty list or the node needed to be deleted is nullptr"<<std::endl;
    }else{
        if(node->data==k->data&&node->next== nullptr){
            node= nullptr;
        }else{
            if(node->data==k->data){
                delete node;
                return ;
            }
            if(node->data!=k->data&&node->next== nullptr){
                std::cerr<<"can't find this node in this list"<<std::endl;
            } else{
                auto x=node;node=node->next;
            while(node!= nullptr){
                if(node->data==k->data){
                    x->next=node->next;
                    delete node;
                    break;
                }
                x=node;
                node=node->next;
            }
            if(node== nullptr){
                std::cerr<<"can't find this node in this list"<<std::endl;
            }
                return ;
            }
        }
    }
}

int main(){
    List<int> l;
    //l.deletefrom(1);
    //reverse_output_list(l.head);
    for(auto i=0;i<10;i++){
        auto x=new ListNode<int>(i);
        l.addtotail(x);
    }
    auto z=l.head;
    while(z!=NULL) {
        std::cout << z->data << " ";
        z=z->next;
    }
    auto zz=l.head;
    delete(new ListNode<int>(2));
    while(zz!=NULL) {
        std::cout << z->data << " ";
        z=z->next;
    }
}
