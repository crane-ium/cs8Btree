#include <iostream>
#include <iomanip>
#include <random>
#include "btree"
//#include "btree.h"
//#include "btree_node.h"

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
void test_btree_auto(int tree_size=5000, int how_many=500, bool report=false);
bool test_btree_auto(int how_many, bool report=true);
int get_rand(const int min, const int max);
void test_trees1(){
    using btr = BTree<int>;
    btr bt(2);
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
    bt3.remove(2);
    bt3.remove(-4);
    bt3.remove(-5);
    bt3.remove(-6);
    bt3.remove(-9);
    bt3.remove(-12);
    cout << bt3 << endl;
    cout << "Size: " << bt3.size() << endl;
    cout << "Valid? " << bt3.check_valid() << endl;
    int* arr = bt3.get_array();
    for(size_t i = 0; i < bt3.size(); i++)
        cout << setw(4) << arr[i];
    cout << endl;
    assert(bt.check_valid());
}
void recreate_bug(){
    using bt = BTree<int>;
    bt btr(1, false);
    btr.insert(286);
    btr.insert(281);
    btr.insert(284);
    btr.insert(283);
    btr.remove(281);
    btr.remove(286);
    cout << btr << endl;
}
void manual_input_test(){
    using bt = BTree<int>;
    bt btr(1,false);
    char command=' ';
    int input = 0;
    while(cin >> command){
        cin >> input;
        if(command=='r')
            btr.remove(input);
        else
            btr.insert(input);
        cout << btr << endl;
    }
}
int Random(int lo, int hi)
{
    int r = rand()%(hi-lo+1)+lo;

    return r;
}
int main()
{
    cout <<endl<<endl<<endl<< "===============================" << endl<<endl<<endl<<endl;

        //------------------------------------------
        srand(time(0));
        //------------------------------------------

    manual_input_test();
//    recreate_bug();
    //    test_BTree_insert_random();
    //    test_BTree_remove();
    //    test_BTree_interactive();
    //    test_BTree_big_three();
//        test_btree_auto(1000,1,false);
//    test_trees1();
    //    test_map();
    //    test_map_interactive();

    //    test_multimap();
    //    test_multimap_interactive();
    //    test_multimap_auto();

    //    test_iterator();
        cout <<endl<<endl<<endl<< "===============================" << endl;
    //test_trees1();
//    btree_node<int>* root = new btree_node<int>(1, true);
//    root->insert(1);
//    root->insert(5);
//    root->insert(10);
//    root->reorganize_root(root);
////    root->remove(5);
//    root->insert(15);
//    root->insert(20);
//    root->insert(7);
//    root->insert(25);
//    root->remove(5);
//    root->remove(7);
//    root->remove(20);
//    root->remove(10);
//    root->remove(15);
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
//    root->print(cout, 0);
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
void test_iterator(){
    const bool debug = false;
    BTree<int> bpt;
    for (int i= 0; i<125; i++)
        bpt.insert(Random(0,100));
    cout<<bpt<<endl;


    cout<<"------------------------------------------------------------"<<endl;
    int* arr = bpt.get_array();
    for(int* it = arr; (*it) < bpt.get_highest(); ++it){
        cout<<"["<<*it<<"] ";
        if (debug) cout<<endl;
    }
    cout<<"["<<bpt.get_highest()<<"] ";
    cout<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"test ++ operator: "<<endl;
    for (int i = 60; i<75; i++){
        int* val = bpt.find(i);
        if (val != nullptr)
            cout<<*val<<" was found."<<endl;
        else
            cout<<i<<" was not found"<<endl;
        }
    cout<<"===================================================================="<<endl;

}

void test_btree_auto(int tree_size, int how_many, bool report){
    bool verified = true;
    for (int i = 0; i< how_many; i++){
        if (report){
            cout<<"*********************************************************"<<endl;
            cout<<" T E S T:    "<<i<<endl;
            cout<<"*********************************************************"<<endl;
        }
        if (!test_btree_auto(tree_size, report)){
            cout<<"T E S T :   ["<<i<<"]    F A I L E D ! ! !"<<endl;
            verified = false;
            return;
        }

    }
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<<"             E N D     T E S T: "<<how_many<<" tests of "<<tree_size<<" items: ";
    cout<<(verified?"VERIFIED": "VERIFICATION FAILED")<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************************************************************"<<endl;

}

bool test_btree_auto(int how_many, bool report){
    const int MAX = 10000;
    assert(how_many < MAX);
    BTree<int> bpt;
    int a[MAX];
    int original[MAX];
    int deleted_list[MAX];

    int original_size;
    size_t size;
    int deleted_size = 0;

    //fill a[ ]
    for (int i= 0; i< how_many; i++){
        a[i] = i;
    }
    //shuffle a[ ]: Put this in a function!
    for (int i = 0; i< how_many; i++){
        int from = Random(0, how_many-1);
        int to = Random(0, how_many -1);
        int temp = a[to];
        a[to] = a[from];
        a [from] = temp;
    }
    //copy  a[ ] -> original[ ]:
    copy_array(original, a, how_many);
    size = how_many;
    original_size = how_many;
    for (int i=0; i<size; i++){
        bpt.insert(a[i]);

    }
    cout << "Inserted\n";
    if (report){
        cout<<"========================================================"<<endl;
        cout<<"  "<<endl;
        cout<<"========================================================"<<endl;
        cout<<bpt<<endl<<endl;
    }
    for (int i= 0; i<how_many; i++){
        size_t r = Random(0, how_many - i - 1);
        if (report){
            cout<<"========================================================"<<endl;
            cout<<bpt<<endl;
            cout<<". . . . . . . . . . . . . . . . . . . . . . . . . . . . "<<endl;
            cout<<"deleted: "; print_array(deleted_list, deleted_size);
            cout<<"   from: "; print_array(original, original_size);
            cout<<endl;
            cout<<"  REMOVING ["<<a[r]<<"]"<<endl;
            cout<<"========================================================"<<endl;
        }
        bpt.remove(a[r]);


        delete_item(a, r, size, deleted_list[deleted_size++]);
        if (!bpt.check_valid()){
            cout<<setw(6)<<i<<" I N V A L I D   T R E E"<<endl;
            cout<<"Original Array: "; print_array(original, original_size);
            cout<<"Deleted Items : "; print_array(deleted_list, deleted_size);
            cout<<endl<<endl<<bpt<<endl<<endl;
            return false;
        }

    }
    if (report) cout<<" V A L I D    T R E E"<<endl;
    cout << bpt << endl;

    return true;
}
