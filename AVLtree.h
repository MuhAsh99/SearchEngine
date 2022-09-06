//
// Created by Ross Garrett on 4/11/22.
//
//credit for AVLtree adapted from https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/AvlTree.h

#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H

#include <algorithm>
#include <iostream>

template <typename T>
class AVLtree{
public:
    AVLtree() : root{ nullptr } {}
    AVLtree(const AVLtree & passed) : root{nullptr} { *this = passed;}
    ~AVLtree() { makeEmpty();}
    void makeEmpty() {makeEmpty(root);}
    AVLtree<T>& operator=( const AVLtree<T>& passed);
    void insert(const T & x){ insert(x, root);}
    void print(){
        if(this->root == nullptr)
        {std::cout << "Empty Tree" << std::endl;}
        else{
            print(this->root);
        }
    }
    bool isEmpty() {return root == nullptr;}
    const T& findMin() {if(isEmpty()) {throw std::logic_error("empty tree");}
        else{return findMin(root)->data;}}
    const T& findMax() {if(isEmpty()) {throw std::logic_error("empty tree");}
        else{return findMax(root)->data;}}
    bool contains(T& passed){return contains(passed, root);}
    void remove( const T & x ) {remove( x, root );}
    T& find(T& passed){return find(passed, root);}
private:
    struct AVLnode{
        T data;
        AVLnode* left;
        AVLnode* right;
        int height;
        AVLnode( const T passed, AVLnode* lt, AVLnode* rt, int h = 0): data{ passed }, left{ lt }, right{ rt }, height { h } { }
    };
    AVLnode* root;
    int height(AVLnode*& t) { return t == nullptr? -1: t->height;}
    int max(int left, int right) const {return  left > right? left: right;}
    void  makeEmpty(AVLnode* & t);
    void rotateWithLeftChild(AVLnode*& k2);
    void rotateWithRightChild(AVLnode*& k1);
    void doubleWithLeftChild(AVLnode*& k3);
    void doubleWithRightChild(AVLnode*& k3);
    void balance(AVLnode*& t);
    void insert(const T& x, AVLnode*& t);
    void print(AVLnode*& passed);
    AVLnode* findMin(AVLnode*& t) const  {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }
    AVLnode* findMax( AVLnode *&t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    bool contains(T&, AVLnode* passed);
    void remove(const T& x, AVLnode*& passed );
    T& find(T&, AVLnode* passed);





};

template<typename T>
void AVLtree<T>::makeEmpty(AVLtree::AVLnode *&t) {
    if(t != nullptr){
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template<typename T>
AVLtree<T> &AVLtree<T>::operator=(const AVLtree<T> &passed) {
    AVLtree<T> copy = passed;
    std::swap(*this, copy);
    return *this;
}

template<typename T>
void AVLtree<T>::rotateWithLeftChild(AVLtree::AVLnode *&k2) {
    AVLnode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template<typename T>
void AVLtree<T>::rotateWithRightChild(AVLtree::AVLnode *&k1) {
    AVLnode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template<typename T>
void AVLtree<T>::doubleWithLeftChild(AVLtree::AVLnode *&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template<typename T>
void AVLtree<T>::doubleWithRightChild(AVLtree::AVLnode *&k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

template<typename T>
void AVLtree<T>::balance(AVLtree::AVLnode *&t) {
    if(t == nullptr)
        return;
    if(height(t->left) - height(t->right) > 1)
        if(height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);//C1
        else
            doubleWithLeftChild(t);//C2
    else
    if(height(t->right) - height(t->left) > 1) {
        if(height(t->right->right ) >= height(t->right->left ))
            rotateWithRightChild(t);//C3

        else
            doubleWithRightChild(t);//C4
    }
    t->height = max(height(t->left),height(t->right)) + 1;

}

template<typename T>
void AVLtree<T>::insert(const T & x, AVLtree::AVLnode * & t) {
    if(t == nullptr)
        t = new AVLnode{x, nullptr, nullptr};
    else if(x < t->data)
        insert(x, t->left);
    else if( t->data < x)
        insert(x, t->right);
    //how do we want to handle duplicates as of now they are not inserted.
    balance(t);
}

template<typename T>
void AVLtree<T>::print(AVLtree<T>::AVLnode *&passed) {
    if(passed != nullptr){
        print(passed->left);
        std::cout << passed->data << "-->  " << passed->height << std::endl;
        print(passed->right);
    }
}

template<typename T>
bool AVLtree<T>::contains(T & passed, AVLtree::AVLnode *t) {
        while( t != nullptr )
            if( passed < t->data )
                t = t->left;
            else if( t->data < passed )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
}

template<typename T>
void AVLtree<T>::remove(const T & x, AVLtree::AVLnode *&t) {
    if( t == nullptr )
        return;   // Item not found; do nothing

    if( x < t->data )
        remove( x, t->left );
    else if( t->data < x )
        remove( x, t->right );
    else if( t->left != nullptr && t->right != nullptr ) // Two children
    {
        t->data = findMin( t->right )->data;
        remove( t->data, t->right );
    }
    else
    {
        AVLnode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }

    balance( t );
}

template<typename T>

T& AVLtree<T>::find(T &passed, AVLtree::AVLnode *t) {
    while( t != nullptr )
        if( passed < t->data )
            t = t->left;
        else if( t->data < passed )
            t = t->right;
        else
            return t->data;    // Match

    throw std::logic_error("not found"); // No match
}


#endif //INC_22S_FINAL_PROJ_AVLTREE_H
