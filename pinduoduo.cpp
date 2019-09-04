//
// Created by 杨炜 on 2019/9/4.
//
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

struct BinaryNode{
    int data;
    BinaryNode* left_child;
    BinaryNode* right_child;
};
int Max_width(BinaryNode* root){
    std::queue<BinaryNode*> q;
    if(!root)
        return 0;
    q.push(root);
    int max_width=1;
    while(!q.empty()){
        decltype(q) q1;
        while(!q.empty()){
            auto x=q.front();
            if(x->left_child) {
                q1.push(x->left_child);
            }
            if(x->right_child){
                q1.push(x->right_child);
            }
            q.pop();
        }
        max_width=max(max_width,(int)q1.size());
        while(!q1.empty()){
            auto x=q1.front();
            q.push(x);q1.pop();
        }
    }
    return max_width;
}
int main(){
    BinaryNode* root=new BinaryNode;
    root->data=1;root->right_child= nullptr;root->left_child= nullptr;
    cout<<Max_width(root)<<endl;
}