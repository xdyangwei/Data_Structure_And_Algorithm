//
// Created by 杨炜 on 2019/3/17.
//
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <string>
template <typename T>
struct Binary_Node{
    T data;
    Binary_Node<T>* left_child;
    Binary_Node<T>* right_child;
    Binary_Node(T v):
    data(v),left_child(nullptr),right_child(nullptr){}
    Binary_Node()= default;

};

//preorder_traversal_with_recursive
template <typename T>
void preorder_traversal_with_recursive(Binary_Node<T>* node){
    if(node!= nullptr){
    std::cout<<node->data<<std::endl;}
    if(node->left_child!= nullptr){
    preorder_traversal_with_recursive(node->left_child);}
    if(node->right_child){
    preorder_traversal_with_recursive(node->right_child);}
}

//非递归版本前序遍历，使用栈保存访问过的结点
template <typename T>
void preorder_traversal_without_recursive(Binary_Node<T>* node){
    if(node!= nullptr){
        std::stack<Binary_Node<T>*> s;
        if(node->left_child!= nullptr){
          while(node!= nullptr||!s.empty()){
              while(node!= nullptr){
                  std::cout<<node->data<<std::endl;s.push(node);node=node->left_child;
              }
              if(!s.empty()){
                  auto x=s.top();
                  s.pop();
                  node=x->right_child;
              }
          }
        } else{
            std::cout<<node->data<<std::endl;
            return ;
        }
    } else{
        std::cerr<<"empty binary tree"<<std::endl;
    }
}

//递归中序遍历

template <typename T>
void inorder_traversal_with_recursive(Binary_Node<T>* node){
    if(node!= nullptr){
        if(node->left_child!= nullptr)
            inorder_traversal_with_recursive(node->left_child);
        std::cout<<node->data<<std::endl;
        if(node->right_child!= nullptr)
            inorder_traversal_with_recursive(node->right_child);
    }else{
        std::cerr<<"empty binary tree"<<std::endl;
    }
}

//非递归版本中序遍历，使用栈保存访问过的结点
template <typename T>
void inorder_traversal_without_recursive(Binary_Node<T>* node){
    if(node!= nullptr){
std::stack<Binary_Node<T>*> s;
    while(node!= nullptr||!s.empty()){
        while(node!= nullptr){
            s.push(node);
            node=node->left_child;
        }
        if(!s.empty()){
            auto x=s.top();s.pop();
            std::cout<<x->data<<std::endl;
            node=x->right_child;
        }
    }
    }else{
        std::cerr<<"empty binary tree"<<std::endl;
    }
}

//递归后续遍历
template <typename T>
void postorder_traversal_with_recursive(Binary_Node<T>* node){
    if(node!= nullptr){
        if(node->left_child!= nullptr)
            inorder_traversal_with_recursive(node->left_child);
        if(node->right_child!= nullptr)
            inorder_traversal_with_recursive(node->right_child);
        std::cout<<node->data<<std::endl;
    } else{
        std::cerr<<"empty binary tree"<<std::endl;
    }
}

//BFS:广度优先遍历，也就是二叉树的层序遍历
//借助队列将结点放入队列再将其子节点入队再弹出结点即可完成层序遍历
template <typename T>
void BFS(Binary_Node<T>* node){
std::queue<Binary_Node<T>*> q;
q.push(node);
    while(!q.empty()){
        auto x=q.front();
    std::cout<<x->data<<std::endl;
    if(x->left_child!= nullptr){
        q.push(x->left_child);
    }
    if(x->right_child!= nullptr){
        q.push(x->right_child);
    }
    q.pop();
}
}

//DFS:深度优先遍历,分为三种：前序、中序和后序遍历，其中每一种又分为递归与非递归版本
//借助递归先dfs左子树再dfs右子树，层层递归
template <typename T>
void DFS(Binary_Node<T>* node){
    if(node!= nullptr){
        std::cout<<node->data<<std::endl;
        if(node->left_child!= nullptr){
            DFS(node->left_child);
        }
        if(node->right_child!= nullptr){
            DFS(node->right_child);
        }
    }
}



int main(){
    Binary_Node<int> n1(1);Binary_Node<int> n2(2);Binary_Node<int> n3(3);
    Binary_Node<int> n4(4);Binary_Node<int> n5(5);Binary_Node<int> n6(6);Binary_Node<int> n7(7);
    Binary_Node<int> n8(8);Binary_Node<int> n9(9);Binary_Node<int> n10(10);
    n1.left_child=&n2;n1.right_child=&n3;n2.left_child=&n4;n2.right_child=&n5;n3.left_child=&n6;n3.right_child=&n7;
    n4.left_child=&n8;n4.right_child=&n9;n5.left_child=&n10;
    
}