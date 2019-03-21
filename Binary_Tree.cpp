//
// Created by 杨炜 on 2019/3/17.
//
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <string>
#include <typeinfo>
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


//判断一棵二叉树是否是另外一棵二叉树的子树，使用递归的思路
// 当树当前结点与所给结点符合时在递归判断二者的左右子树
template <typename T>
bool recursive_sub_tree(Binary_Node<T>* node1,Binary_Node<T>* node2){
    if(node1!= nullptr&&node2!= nullptr) {
        if (node1->data == node2->data) {
            return true && recursive_sub_tree(node1->left_child, node2->left_child) &&
                   recursive_sub_tree(node1->right_child, node2->right_child);
        } else {
            return false;
        }
    }else if((node1&&!node2)||(!node1&&!node2)){
        return true;
    }else{
        return false;
    }
}

template <typename T>
bool sub_tree(Binary_Node<T>* node1,Binary_Node<T>* node2){
    if(node1== nullptr||node2== nullptr)
        return false;
    bool x=false;
    if(node1->data==node2->data){
        x=(recursive_sub_tree(node1->left_child,node2->left_child)&&recursive_sub_tree(node1->right_child,node2->right_child));
    }else{
        x=(recursive_sub_tree(node1->left_child,node2)||recursive_sub_tree(node1->right_child,node2));
    }
    return x;
}

//镜像二叉树，使用递归交换每个结点的左右子节点的值
template <typename T>
Binary_Node<T>* binary_tree_mirror(Binary_Node<T>* node){
    if(node== nullptr)
        return nullptr;
    auto x=node->left_child;auto y=node->right_child;
    node->left_child=y;node->right_child=x;
    if(node->left_child!= nullptr)
        binary_tree_mirror(node->left_child);
    if(node->right_child!= nullptr)
        binary_tree_mirror(node->right_child);
    return node;
}

//镜像二叉树非递归版，使用栈或队列都行
template <typename T>
void binary_tree_mirror_without_recursive(Binary_Node<T>* node){
    std::stack<Binary_Node<T>*> s;
    if(node== nullptr)
        return ;
    s.push(node);
    while(!s.empty()){
        auto x=s.top();
        auto l=x->left_child;
        auto r=x->right_child;
        x->right_child=l;x->left_child=r;
        s.pop();
        if(x->left_child!= nullptr)
            s.push(x->left_child);
        if(x->right_child!= nullptr)
            s.push(x->right_child);
    }
}

//判断一棵二叉树是否是对称二叉树，只需要使用先访问根节点然后再依次访问
//右子节点和左子节点然后得出对称前序遍历的序列与前序遍历的序列相比较
//如果完全相同就是对称二叉树
void recursive_symmetry_binary_tree(std::vector<int> &v1,Binary_Node<int>* node,bool flag){
    if(node!= nullptr){
        v1.push_back(node->data);
        if(flag==1){
        recursive_symmetry_binary_tree(v1,node->left_child,1);
        recursive_symmetry_binary_tree(v1,node->right_child,1);} else{
            recursive_symmetry_binary_tree(v1,node->right_child,0);
            recursive_symmetry_binary_tree(v1,node->left_child,0);
        }
    }
    else
        v1.push_back(0);
}

bool Symmetry_binary_tree(Binary_Node<int>* node){
     std::vector<int> v1,v2;
    recursive_symmetry_binary_tree(v1,node,1);
    recursive_symmetry_binary_tree(v2,node,0);
    if(v1==v2){
        return true;
    }
    return false;
}

//根据二叉树前序遍历和中序遍历的结果重建该二叉树
//思路：前序遍历的首个结点是根结点，在中序遍历中找到该节点位置，排在其前面的就是
//根节点的左子树，后面的就是根节点的右子树，然后在左子树和右子树中递归找到子树的根节点即可
Binary_Node<int>* reConstructBinaryTree(std::vector<int> pre,std::vector<int> vin) {
    if(pre.size()>1){
    auto x=pre[0];
    auto it=std::find(vin.begin(),vin.end(),x);
    auto it1=it;
    auto pre_it=pre.end()-pre.begin();
    for(it=it+1;it<vin.end();it++){
        auto xx=std::find(pre.begin(),pre.end(),*it)-pre.begin();
        pre_it=std::min(xx,pre_it);
    }
    //std::cout<<pre_it<<" "<<(it1-vin.begin())<<std::endl;
    auto node=new Binary_Node<int>(x);
    node->left_child=reConstructBinaryTree(std::vector<int>(pre.begin()+1,pre.begin()+pre_it),std::vector<int>(vin.begin(),it1));
    node->right_child=reConstructBinaryTree(std::vector<int>(pre.begin()+pre_it,pre.end()),std::vector<int>(it1,vin.end()));
    return node;} else if(pre.size()==1){
        auto node=new Binary_Node<int>(pre[0]);
        //std::cout<<node->data<<std::endl;
        return node;
    } else{
        return nullptr;
    }
}

//给定一整数数组，判断其是否是某二叉搜索树的后序遍历序列
//二叉搜索树的性质：左子树上的所有结点的值都小于根节点的值，右子树上的所有节点的值都大于根节点的值
//思想：后序遍历的最后一项是根节点，根据二叉搜索树的性质找到左子树和右子树然后递归进行判断，最后将所有结果相与
//最终结果为true代表是某棵二叉搜索树的后序遍历序列，为false则表示不是
bool VerifySquenceOfBST(std::vector<int> sequence){
    if(sequence.size()>1) {
        auto x = sequence[sequence.size() - 1];
        bool flag= true;
        int i=0;
        for(;i<sequence.size()-1;i++){
            if(sequence[i]<x&&sequence[i+1]>x){
                break;
            }
        }
        if(i==sequence.size()-1){
                ;
        } else{
        for(int j=0;j<=i;j++){
            if(sequence[j]>x){
                flag= false;
                break;
            }
        }
        //std::cout<<flag<<std::endl;
        for (int j = i+1; j <sequence.size()-1 ; ++j) {
            if(sequence[j]<x){
                flag= false;
                break;
            }
        }}
        if(flag== true&&i!=sequence.size()-1){
            return true&&VerifySquenceOfBST(std::vector<int>(sequence.begin(),sequence.begin()+i+1))&&VerifySquenceOfBST(std::vector<int>(sequence.begin()+i+1,sequence.end()-1));
        } else if(flag== true&&i==sequence.size()-1){
            return true&&VerifySquenceOfBST(std::vector<int>(sequence.begin(),sequence.end()-1));
        }
        else{
        return false;
        }
    }else if(sequence.size()==1){
        return true;
    }else{
        return false;
    }
}

//之字形打印字符串
//思路：使用两个栈分别存储奇数层和偶数层的结点，这样就不会造成顺序混乱
template <typename T>
std::vector<std::vector<int> > Print(Binary_Node<T>* pRoot) {
    std::stack<Binary_Node<T>*> s1;std::stack<Binary_Node<T>*> s2;
    s1.push(pRoot);int i=1;
    std::vector<std::vector<T>> result;
    while(!s1.empty()||!s2.empty()){
        if(!s1.empty()){
            std::vector<T> data;
        while(i%2==1){
            auto x=s1.top();
            data.push_back(x->data);
            s1.pop();
            s2.push(x->right_child);
            s2.push(x->left_child);
            if(s1.empty())
                i++;
        }
        result.push_back(data);
        }
        if(!s2.empty())
        {
            std::vector<T> data;
            while(i%2==0) {
                auto x = s2.top();
                data.push_back(x->data);
                s2.pop();
                s1.push(x->left_child);
                s1.push(x->right_child);
                if (s2.empty())
                    i++;
            }
            result.push_back(data);
        }
    }
    return result;
}

int main(){
    Binary_Node<int> n1(1);Binary_Node<int> n2(2);Binary_Node<int> n3(3);
    Binary_Node<int> n4(4);Binary_Node<int> n5(5);Binary_Node<int> n6(6);Binary_Node<int> n7(7);
    Binary_Node<int> n8(8);Binary_Node<int> n9(9);Binary_Node<int> n10(10);
    n1.left_child=&n2;n1.right_child=&n3;n2.left_child=&n4;n2.right_child=&n5;n3.left_child=&n6;n3.right_child=&n7;
    n4.left_child=&n8;n4.right_child=&n9;n5.left_child=&n10;
    Binary_Node<int> m1(2);Binary_Node<int> m2(4);
    m1.left_child=&m2;
    std::vector<int> pre{1,2,4,7,3,5,6,8};
    std::vector<int> vin{4,7,2,1,5,3,8,6};
    std::vector<int> v{7,4,6,5};
    auto z=Print(&n1);
    for(auto x:z){
        for(auto xx:x)
            std::cout<<xx<<" ";
        std::cout<<std::endl;
    }
    //std::vector<int> v(vin.begin(),vin.begin());
    //std::cout<<v.size()<<std::endl;
   /*auto x=reConstructBinaryTree(pre,vin);
    BFS(x);*/
}