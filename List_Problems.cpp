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

int main(){
    List<int> l;
    l.deletefrom(1);
    reverse_output_list(l.head);
    for(auto i=0;i<10;i++){
        auto x=new ListNode<int>(i);
        l.addtotail(x);
    }
    auto z=l.head;
    while(z!=NULL) {
        std::cout << z->data << " ";
        z=z->next;
    }
    std::cout<<std::endl;
    reverse_output_list(l.head);
}
