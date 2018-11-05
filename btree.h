/**
  *@file include/btree.h
  */
#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "btree_node.h"

using namespace std;

template<class T>
class BTree{
public:
    //CTOR
    BTree(size_t min=1, bool dupes=false);
    //BIG3
    ~BTree();
    BTree(const BTree<T>& copy);
    BTree<T>& operator =(const BTree<T> copy);
    //MEMBER FUNCTIONS
    void insert(const T& input);
    void remove(const T& input);
    bool exists(const T& input);
    T* find(const T& input);

    T& get(const T& input);
    T* get_ptr(const T& input);

    T* get_array();
    T& get_highest() const;

    void cleartree();
    void copy_tree(const BTree<T>& other);

    bool check_valid() const;

    //CONST MEMBER FUNCS
    size_t size() const;
    bool empty() const;
    //FRIENDS
    template<typename U>
    friend ostream& operator <<(ostream& outs, BTree<U>& bt);
private:
    size_t _min;
    bool __dupes;
    btree_node<T>* __head;
};

template<typename T>
BTree<T>::BTree(size_t min, bool dupes)
        : _min(min),__dupes(dupes), __head(new btree_node<T>(min,dupes)){

}
template<typename T>
BTree<T>::~BTree(){
    delete __head;
}
template<typename T>
BTree<T>::BTree(const BTree<T>& copy){
    _min = copy._min;
    __dupes = copy.__dupes;
    __head = new btree_node<T>((*copy.__head));
}
template<typename T>
BTree<T>& BTree<T>::operator =(const BTree<T> copy){
    if(this == &copy)
        return (*this);
    BTree<T> temp(copy);
    swap(this->_min, temp._min);
    swap(__dupes, temp.__dupes);
    swap(__head, temp.__head);
    return (*this);
}

template<typename T>
void BTree<T>::insert(const T &input){
    __head->insert(input);
    if(__head->maxed())
        __head->reorganize_root(__head);
}

template<typename T>
void BTree<T>::remove(const T& input){
    __head->remove(input);
}
template<typename T>
void BTree<T>::cleartree(){
    delete __head;
    __head = new btree_node<T>(_min, __dupes);
}
template<typename T>
void BTree<T>::copy_tree(const BTree<T>& other){
    (*this) = other;
}
template<typename T>
bool BTree<T>::exists(const T& input){
    return __head->exists(input);
}
template<typename T>
size_t BTree<T>::size() const{
    return __head->total_size();
}
template<typename T>
bool BTree<T>::empty() const{
    return __head->size();
}
template<typename T>
ostream& operator <<(ostream& outs, BTree<T>& bt){
    bt.__head->print(outs, 0);
    return outs;
}
template<typename T>
bool BTree<T>::check_valid() const{
    return __head->check_validity();
}
template<typename T>
T* BTree<T>::get_array(){
    //returns an array version of the tree
    T* arr = new T[__head->total_size()];
    size_t size=0;
    __head->get_array(arr, size);
    return arr;
}
template<typename T>
T& BTree<T>::get_highest() const{
    return __head->get_highest();
}
template<typename T>
T* BTree<T>::find(const T &input){
    return __head->find(input);
}
#endif // BTREE_H
