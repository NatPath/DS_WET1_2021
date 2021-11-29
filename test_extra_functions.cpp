#include "AVL_extra_functions.h"



#define SIZE 50

void basicListCheck(){
    List<int> l;

    int* arr = new int[SIZE];
    for (int i=0 ; i<SIZE ;i++){
        arr[i]=i*2;
    }
    for (int i=SIZE-1; i>=0;i--){
        l.add(arr[i]);
    }
    l.printList();
    delete[] arr;
}
void dynamicArrayToListCheck(){
    DynamicArray<int> arr(SIZE);

    for (int i=0 ; i<SIZE ;i++){
        arr[i]=i*2;
    }
    List<int> l(arr);
    l.printList();


}
List<int> returnAList(){
    DynamicArray<int> arr(SIZE);

    for (int i=0 ; i<SIZE ;i++){
        arr[i]=i*2;
    }
    List<int> l(arr);
    return l;
    
}
//does list "own" the data it contains?
void checkReturnAList(){
    List<int> l=returnAList();
    l.printList();
}
void checkMergeLists(){
    DynamicArray<int> arr1(SIZE/2);
    DynamicArray<int> arr2(SIZE/2);
    for (int i=0 ; i<SIZE/2 ;i++){
        arr1[i]=i*2;
        arr2[i]=i*2+1;
    }
    List<int> l1(arr1);
    List<int> l2(arr2);
    List<int> l_merged=mergeOrderedLists(l1,l2);
    l_merged.printList();
}
void checkArrayToTree(){
    DynamicArray<Pair<int,int>> arr(SIZE);
    for (int i=0 ;i<SIZE;i++){
        arr[i] = Pair<int,int>(i,i);
    }
    AVL_Tree<int,int> tree = ArrayToTree<int,int>(arr);
    tree.printTree();

}
int main(){
    //basicListCheck();
    //dynamicArrayToListCheck();
    //checkReturnAList();
    //checkMergeLists();
    checkArrayToTree();

    return 0;
}