#ifndef LIST_BINARYSEARCHTREE_H
#define LIST_BINARYSEARCHTREE_H

#include <iostream>
using namespace std;

template <class Type>
class BinarySearchTree{
private:
    struct BinaryNode{
        Type data;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Type&thedata,BinaryNode*lt,BinaryNode*rt):data(thedata),left(lt),right(rt){}
    };

    BinaryNode* root;
    void insert(const Type&x,BinaryNode*&t){
        if(t==NULL)
            t = new BinaryNode(x,NULL,NULL);
        else if(x<t->data)
            insert(x,t->left);
        else if(t->data<x)
            insert(x,t->right);
    }
    void remove(const Type&x,BinaryNode*&t){
        if(t==NULL)return;
        if(x<t->data) remove(x,t->left);
        else if(t->data<x) remove(x,t->right);
        else if(t->left!=NULL&&t->right!=NULL){
            BinaryNode*tmp=t->right;
            while(tmp->left!=NULL)tmp=tmp->left;
            t->data=tmp->data;
            remove(t->data,t->right);
        }
        else{
            BinaryNode* oldNode=t;
            t=(t->left!=NULL)?t->left:t->right;
            delete oldNode;
        }

    }
    bool find(const Type&x,BinaryNode*t)const{
        if(t==NULL)
            return false;
        else if(x<t->data)
            return find(x,t->left);
        else if(t->data<x)
            return find(x,t->right);
        else return true;
    }
    void makeEmpty(BinaryNode*&t){
        if (t == NULL) return;
        if (t->left)
            makeEmpty(t->left);
        if (t->right)
            makeEmpty(t->right);
        delete t;
        t = NULL;

    }

public:
    BinarySearchTree(BinaryNode*t=NULL){root=t;}
    ~BinarySearchTree(){
        makeEmpty(root);
    }
    bool find(const Type&x)const {
        return find(x,root);
    }
    void insert(const Type&x){
        insert(x,root);
    }
    void remove(const Type&x){
        remove(x,root);
    }

};




#endif //LIST_BINARYSEARCHTREE_H
