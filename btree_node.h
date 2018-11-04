/**
  *@file include/btree/btree_node.h
  */
#ifndef BTREE_NODE_H
#define BTREE_NODE_H

static const int DEBUG = 0; //1: debug 2: heavy-debug 3: ultra

#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "btree_functions.h"

using namespace std;

template<typename T>
struct btree_node{
    //CTOR
    btree_node(size_t min=1, bool dupes=false);
    //BIG3

    //MEMBER FUNCTIONS
    bool insert(const T& input);
    void remove(const T& input); //Remove the target input
    bool find(const T& input);
        //insert_all: insert an input/node pairing
    bool insert_all(const T &input, btree_node<T> *node=nullptr);
    bool is_leaf() const{return !(bool)(_children[0]);}
    void fix_excess(btree_node<T>* cnode);
    //insert_left: only needed for when creating new children
//    bool insert_left(const T& input, btree_node<T> *node=nullptr);
    void squeeze(); //pushes over children pointers to the left
//    void insert_child(btree_node<T> *node);
    bool check_validity() const; //checks that the node has valid arrays
    void reorganize_root(btree_node<T>* &root);

    bool maxed() const;
    bool dupes() const{return __dupes;}
    size_t size() const{return _data_size;}
    size_t total_size() const;
//    const T& max_data() const{return _data[_data_size-1];}
//    const T& min_data() const{return _data[0];}

    void print(ostream& outs, const size_t level, const size_t extra=0, const size_t sl=0) const;
    string data_string() const;

    template<typename U>
    friend ostream& operator <<(ostream& outs, const btree_node<U>& node);
private:
    size_t _min, _data_size; //datasize should not exceed  2*_min
    T* _data; //data array
    bool* _d_check; //checks the data is there after movement?
    btree_node<T>** _children; //children pointer array
    bool __dupes;
    //PRIVATE FUNCTIONS
};
namespace btf{
    template<typename T>
    size_t get_child(const T& input, T* data, const size_t size);
    template<typename T>
    bool check_dupe(const T& item, T* data, const size_t s);
}

template<typename T>
btree_node<T>::btree_node(size_t min, bool dupes)
        : _min(min), _data_size(0), __dupes(dupes){
    _data = new T[2*_min+1]; //2*min is limit; give it space to hold an extra past threshold
    _d_check = new bool[2*_min+1];
    _children = new btree_node<T>*[2*_min+2]; //2*min+1 is limit, extra to hold past threshold
    for(size_t i = 0; i < 2*_min+1; i++)
        _d_check[i] = false;
    for(size_t i = 0; i < 2*_min+2; i++)
        _children[i] = nullptr;
}

template<typename T>
bool btree_node<T>::insert(const T &input){
    //Zeroeth, check for dupes
    if(!__dupes && btf::check_dupe(input, _data, _data_size))
        return false;
    //First, Check if there are children to hand the input to
    if(_children[0]){
        if(DEBUG)
            cout << "Handing off to child\n";
        //Now find which child to give this to
        // equivalent to first_ge()
        size_t child = btf::get_child(input, _data, _data_size);
        (*_children[child]).insert(input);
        //Then check if your child was overburdened
        if((*_children[child]).maxed()){
            if(DEBUG)
                cout << "Reorganizing child\n";
            btree_node<T>* cnode = _children[child];
            fix_excess(cnode); //Reorganize children/parent
        }
        return true;
    }
    return insert_all(input);
}
template<typename T>
void btree_node<T>::fix_excess(btree_node<T>* cnode){
    size_t i;
    btree_node<T>* right = new btree_node<T>(_min, __dupes);
    for(i = 0; i < _min; i++){
        swap(cnode->_data[cnode->_data_size-_min+i]
                , right->_data[i]);
        swap(cnode->_children[cnode->_data_size-_min+i]
                , right->_children[i]);
        swap(cnode->_d_check[cnode->_data_size-_min+i]
                , right->_d_check[i]);
    }
    swap(cnode->_children[cnode->_data_size], right->_children[i]);
     cnode->_data_size -= _min;
    right->_data_size += _min;
    //move the middle element of child into new home
    this->insert_all(cnode->_data[cnode->_data_size - 1], right);
    cnode->_d_check[cnode->_data_size-1]=false;
    cnode->_data_size--;
}
template<typename T>
bool btree_node<T>::maxed() const{
    //returns if itself has a full data array, so a parent can reorganize
    if(_data_size > 2*_min)
        return true;
    return false;
}
template<typename T>
size_t btree_node<T>::total_size() const{
    size_t totes = 0;
    if(_children[0])
        for(size_t i = 0; i < _data_size+1; i++)
            totes += _children[i]->total_size();
    return totes+size();
}
template<typename T>
bool btree_node<T>::insert_all(const T& input, btree_node<T>* node){
    //When inserting, if shifting over to find insert, must shift children too
    size_t i = _data_size;
//    swap(_data[i], input);
    swap(_children[i+1], node);
    _d_check[i] = true;
    (_data[i]) = input;
//    _children[i+1] = node;
    _data_size++;
    if(DEBUG)
        cout << "Gonna run insertion sort: " << __FUNCTION__ << " : " << _data_size << endl;
    for(i = 0; i + 1 < _data_size; i++){
        if(input <= (_data[_data_size - i - 2])){//insertion sort
            if(DEBUG>=3)
                cout << "Swapping " << (_data[_data_size - i - 2])
                     << ", " << (_data[_data_size - i - 1]) << endl;
            swap(_data[_data_size - i - 1], _data[_data_size - i - 2]);
            swap(_d_check[_data_size - i - 1], _d_check[_data_size - i - 2]);
            swap(_children[_data_size - i], _children[_data_size - i - 1]);
            this->squeeze(); //this makes this function more general, but not sure this is useful anymore
        }else
            break; //stop swapping, it is now sorted
    }
    return true;
}
template<typename T>
void btree_node<T>::squeeze(){
    bool flag = false;
    while(_children[0]==nullptr){
        flag = true;
        for(size_t i = 1; i < 2*_min+2; i++){
            if(_children[i]){
                flag = false;
                swap(_children[i-1], _children[i]);
            }
        }
        if(flag)
            return;
    }
}
template<typename T>
ostream& operator <<(ostream& outs, const btree_node<T>& node){
    size_t i;
    outs << "[";
    for(i = 0; i < node._data_size; i++){
        if(i>0)
            outs << " ";
        outs << (node._data[i]);
    }
    outs << "]";
    return outs;
}
template<typename T>
void btree_node<T>::reorganize_root(btree_node<T>* & root){
    //If root has reached it's threshold, it needs to reorganize into new children
    btree_node<T>* left = root;
    root = new btree_node<T>(_min, __dupes);
    btree_node<T>* right = new btree_node<T>(_min, __dupes);
    //Split up the full child by moving the middle and paired child up
    // to the parent, then move the right half and paired children to become
    // a new child of the parent. Left node stays stationary
    //FIRST, move __min nodes and __min + 1 children to right
    size_t i;
    for(i = 0; i < _min; i++){
        swap(left->_data[_data_size-_min+i], right->_data[i]);
        swap(left->_children[_data_size-_min+i], right->_children[i]);
        swap(left->_d_check[_data_size-_min+i], right->_d_check[i]);
    }
    swap(left->_children[_data_size], right->_children[i]);
    left->_data_size -= _min;
    right->_data_size += _min;
    //SECOND, move middle node into the new root
    swap(left->_data[_data_size-1], root->_data[0]);
    swap(left->_d_check[_data_size-1], root->_d_check[0]);
    root->_data_size++;
    left->_data_size--;
    //THIRD! ...insert children
    root->insert_child(left);
    root->insert_child(right);
}
template<typename T>
void btree_node<T>::insert_child(btree_node<T>* node){
    //Used for building a new child.
    //Insert child at end of children
    btree_node<T>** w = _children;
    while((*w)!= nullptr)
        w++;
    swap(node, (*w));
}
template<typename T>
void btree_node<T>::print(ostream& outs, const size_t level, const size_t extra, const size_t sl) const{
    //print in reverse preorder
    if(DEBUG) cout << "PRINTING\n";
//    bool print_adjacent = !(bool)(_data_size%2);
    string str = this->data_string();
//    size_t slength = str.length();
    if(_children[0]==nullptr){
        for(size_t i = 0; i < (level)*10 + sl; i++)
            outs << " "; //how to get setw to set fixed space?
        outs << (*this) << endl;
        return;
    }
    for(size_t i = _data_size; i > _data_size/2; i--){
        _children[i]->print(outs, level+extra+1);
    }
    for(size_t i = 0; i < (level)*10 + sl; i++)
        outs << " "; //how to get setw to set fixed space?
    outs << (*this);
//    if(print_adjacent)
//        _children[_data_size/2]->print(outs, 0, level+extra+1, slength);
//    else
    outs << endl;
    for(int i = (_data_size)/2; i >= 0; i--){
        _children[i]->print(outs, level+extra+1);
    }
}
template<typename T>
string btree_node<T>::data_string() const{
    stringstream dstream;
    dstream << (*this);
    string dstr = dstream.str();

    return dstr;
}
template<typename T>
bool btree_node<T>::check_validity() const{
    bool flag = true;
    for(size_t i = 0; i < _data_size; i++)
        flag *= _d_check[i]; //boolean-and the data_check values;
    if(!(_children[0]))
        return flag;
    for(size_t i = 0; i < _data_size+1; i++)
        flag *= _children[i]->check_validity(); //recursively call
    return flag;
}
//--------- GENERAL FUNCTIONS ---------
template<typename T>
size_t btf::get_child(const T& input, T *data, const size_t size){
    for(size_t i = 0; i < size; i++)
        if(input <= (data[i]))
            return i;
    return size;
}
template<typename T>
bool btf::check_dupe(const T& item, T* data, const size_t s){
    for(size_t i = 0; i < s; i++)
        if(data[i]==item)
            return true;
    return false;
}
#endif // BTREE_NODE_H
