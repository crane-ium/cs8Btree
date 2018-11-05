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
void test_trees1(){
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
    cout << "10 exists? " << bt.exists(10) << " -94 exists?: "
         << bt.exists(-94) << " 100 exists?: " << bt.exists(100) << endl;
    btr bt2(bt);
    bt2.insert(10);
    btr bt3 = bt2;
    bt3.insert(-99);
    bt2.cleartree();
    cout << bt2 << endl;
    cout << "Size: " << bt2.size() << endl;
    cout << "Valid? " << bt2.check_valid() << endl;
    bt3.remove(-99);
    cout << bt3 << endl;
    cout << "Size: " << bt3.size() << endl;
    cout << "Valid? " << bt3.check_valid() << endl;
    assert(bt.check_valid());
}

int main()
{
    //test_trees1();
    btree_node<int>* root = new btree_node<int>(1, true);
    root->insert(1);
    root->insert(5);
    root->insert(10);
    root->reorganize_root(root);
//    root->remove(5);
    root->insert(15);
    root->insert(20);
    root->insert(7);
    root->insert(25);
    root->remove(5);
    root->remove(7);
    root->remove(20);
    root->remove(10);
    root->remove(15);
//    root->remove(20);
//    root->insert(25);
//    root->insert(25);
//    root->insert(25);
//    root->insert(25);
//    root->insert(25);
//    root->remove(15);
//    root->remove(20);
//    root->remove(10);
//    root->remove(1);
//    root->remove(25);
//    root->remove(1);
//    root->remove(15);
//    root->remove(5);
//    root->remove(10);
//    root->remove(20);
//    root->remove(25);
//    root->remove(0);
//    root->remove(15);
    root->print(cout, 0);
//    btree_node<int>* root = new btree_node<int>(2, false);

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
