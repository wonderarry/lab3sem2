#include <random>
#include "dynamicarray.h"
using std::cin;
using std::cout;

int is_auto;
std::random_device rd;
std::mt19937 mersenne(rd());


void bst(){
    BinarySearchTree<T> tester;
    cout << "\n1. Balancing + ordering in any order";
    cout <<"\n2. Printing out a subsequence";
    int b;
    T temp;
    cin >> b;
    int length;
    cout << "\n Enter the length of the sequence";
    cin >> length;
    for (int i = 0; i < length; ++i){
        if (is_auto){
            temp = -100.0 + (mersenne() % 20000) / 100.0
            cout << "temp for i = " << i << std::endl;
        }
        else{
            cin >> temp;
        }
        tester.InsertAt(tester.GetSize(), temp);
    }
    if (b == 1){
        cout << "\n Enter the sequence in which the tree will be traversed. 1 - node, 2 - left subtree, 3 - right. : ";
        std::string seqInput;
        cin >> seqInput;
        tester.AssessOrdering(seqInput);
        tester.Order();
    }
    if (b == 2){
        int specialNode;
        cout << "\nSelect a specific node index from which the subtree will be derived";
        cin >> specialNode;
        cout << "\n Enter the sequence in which the tree will be traversed. 1 - node, 2 - left subtree, 3 - right. : ";
        std::string seqInput;
        cin >> seqInput;
        tester.AssessOrdering(seqInput);
        tester.Order();
    }
}


void bheap(){
    BinaryHeap<T> tester;
    cout << "Enter an unsorted array\n";
    T temp;
    cout << "\n Specify the length: ";
    int length;
    cin >> length;
    for (int i = 0; i < length; ++i){
        cin >> temp;
        tester.InsertAt(tester.GetSize(), temp);
    }

    cout << "1. Heapify it and print it";
    cout << "\n2. Extract the subtree for a given node index";
    cout << "\n3. Check if a certain subtree is in the tree";
    int y;
    cin >> y;
    if (y == 1){
        tester.BuildHeap();
        for (int i = 0; i < length; ++i){
            cout << '\n' << tester.Get(i);
        }
    }
    if (y == 2){
        tester.BuildHeap();
        int z;
        cout << "\nSpecify the node: ";
        cin >> z;
        tester.SubheapExtraction(z);
        DynamicArray<T> tester2 = tester.GetSubheapKeeper();
        for (int i = 0; i < tester2.GetSize(); ++i){
            cout << '\n' << tester2.Get(i);
        }
    }
    if (y == 3){
        isSubheapIncluded();
    }
}

void menu(){
    cout << "Auto mode?";
    cin >> is_auto;
    cout << "\n BST(1) or Binary Heap(2)?";
    int a;

    cin >> a;
    if (a == 1){
        bst();
    }
    if (a == 2){
        bheap();
    }
}


int main(){
    menu();
}
