#ifndef BTREE_FUNCTIONS_H
#define BTREE_FUNCTIONS_H

#include <cstdlib>

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

#endif // BTREE_FUNCTIONS_H
