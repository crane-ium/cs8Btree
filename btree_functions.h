#ifndef BTREE_FUNCTIONS_H
#define BTREE_FUNCTIONS_H

#include <cstdlib>
#include <iomanip>
using namespace std;

template<typename T>
T* f_find(T* data, const size_t s, const T& input){
    for(size_t i = 0; i < s; i++){
        if(data[i] == input)
            return (data+i);
    }
    return nullptr;
}
template<typename T>
size_t first_ge(T* data, const size_t s, const T& input){
    for(size_t i = 0; i < s; i++){
        if(input<=data[i])
            return i;
    }
    return s;
}
template<typename T>
void copy_array(T a_new[], const T a_copy[], const size_t& s){
    for(size_t i = 0; i < s; i++)
        a_new[i] = a_copy[i];
}
template<typename T>
void print_array(T arr[], const T& s){
    for(size_t i = 0; i < s; i++){
        cout <<  "[" << setw(4)  << setfill('0') << arr[i] << "] ";
    }
    cout << endl;
}
template<typename T>
void delete_item(T data[], size_t& i, size_t& s, T& entry){
    swap(entry, data[i]);
    s--;
    for(size_t i = i; i < s; i++)
        swap(data[i], data[i+1]);
}

#endif // BTREE_FUNCTIONS_H
