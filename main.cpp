#include <iostream>
#include <iomanip>
#include <random>
#include "btree.h"
#include "btree_node.h"

using namespace std;

struct tester{
    tester(const string& s="a"):_string(s){if(DEBUG)cout << "made " << _string << endl;}
    friend operator <=(const tester& lhs, const tester& rhs)
        {return (lhs._string.length()<=rhs._string.length());}
    friend operator ==(const tester& lhs, const tester& rhs)
        {return (lhs._string==rhs._string);}
    friend ostream& operator <<(ostream& outs, tester& t){
        outs << t._string;
        return outs;
    }
    string _string;
};

int get_rand(const int min, const int max);

int main()
{
//    btree_node<int>* root = new btree_node<int>(2, false);
    using btr = BTree<int>;
    btr bt(4);
    int max = 0;
    int min = 0;
    for(size_t i = 0; i < 100; i++){
        int z = get_rand(-99,99);
        if(z>max)
            max = z;
        else if(z<min)
            min = z;
        bt.insert(z);
    }
    cout << bt << endl;
    cout << "Size: " << bt.size() << endl;
    cout << "max: " << max << " min: " << min << endl;
    assert(bt.check_valid());
//    btree_node<tester>* root = new btree_node<tester>();
//    (*root).insert(tester("a"));
//    root->insert(tester("b"));
//    root->insert(tester("c"));
//    cout << (*root) << endl;
//    if(root->maxed())
//        root->reorganize_root(root);
//    root->insert(tester("dd"));
//    root->insert(tester("1"));
//    root->insert(tester("2"));
//    root->insert(tester("3"));
//    root->insert(tester("45"));
//    root->reorganize_root(root);
//    root->insert(tester("5"));
//    root->insert(tester("6"));
//    root->insert(tester("7"));
//    cout << (*root) << endl;
//    btree_node<tester> bntest(1,true);
//    tester* b = new tester("b");
//    bntest.insert((*b));
////    bntest.insert(tester("c"));
//    btree_node<tester> bnchild(1,true);
//    bnchild.insert(tester("d"));
////    bntest.insert_all(tester("c"), &bnchild);
////    bntest.insert(tester("e"));
////    bntest.insert(tester("e"));
////    delete b;
////    bntest.insert(2);
//    int i = int();
//    cout << "maxed: " << (i==0) << endl;

//    cout << bntest << endl;

    cout << "Done!\n";

    return 0;
}

int get_rand(const int min, const int max){
    return rand() % (max-min) + min;
}
