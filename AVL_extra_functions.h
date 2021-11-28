#ifndef AVL_EXTRA_FUNC_H
#define AVL_EXTRA_FUNC_H

#include "List.h"
#include "Pair.h"
#include "Avl.h"

/* *
 * make an ordered list of Pairs (ordered by key of course) into a tree
 * 
 * 
 * */
template <typename KEY,typename VAL>
using Node_ptr=std::shared_ptr<AVL_NODE<KEY,VAL>>;

/**
 * gets an array. make an avl tree from all of it.
 * */
template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> ArrayToTree(DynamicArray<Pair<KEY,VAL>>& array){
    int size = array.getSize();
    return ArrayToTree(array,0,size-1);
}

/**
 * gets an array. make an avl tree of the element between start_index and end_index.
 * */
template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> ArrayToTree(DynamicArray<Pair<KEY,VAL>>& array,int start_index,int end_index){

    if(start_index>end_index){
        return AVL_Tree();
    }

    int size = end_index-start_index+1;
    int mid= start_index+size/2;
    AVL_Tree<KEY,VAL> tree();
    tree.insertNode(array[mid].getKey(),array[mid].getValue());
    if (start_index==end_index){
        return tree;
    }
    AVL_Tree<KEY,VAL> left_tree = ArrayToTree(array,start_index,mid-1);
    AVL_Tree<KEY,VAL> right_tree = ArrayToTree(array,mid+1,end_index);
    connectNodes(tree.getRoot(),left_tree->getRoot(),L);
    connectNodes(tree.getRoot(),right_tree->getRoot(),R);
    tree.root->updateHeight();
    tree.root->updateRank();
    return tree;
    
}

template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> ListToTree(List<Pair<KEY,VAL>>& list){

    DynamicArray<Pair<KEY,VAL>> array = listToArray(list);
    return ArrayToTree(array);
}

template <typename KEY,typename VAL>
List<Pair<KEY,VAL>> TreeToList(AVL_Tree<KEY,VAL>& tree){
    
}
/*
* ittarateOrder_intoList:
*   iterates over the tree from the root given by the order given and activates function 'f' on each vertex while doing so.
*   reverse- if set to true, the iteration is done backwards
*   
*/
template <typename KEY,typename VAL>
void inOrder_intoList(Node_ptr<KEY,VAL> root,Order order, void(*f)(Node_ptr<KEY,VAL>&),int n,bool reverse = false){
    if (root==nullptr){
        return;
    }
    if (isLeaf(root)){
        (*f)(root);
        return;
    }
    if (!reverse){
        if (order==IN){
            itterateOrder(root->getLeft(),IN,f);
            (*f)(root);
            itterateOrder(root->getRight(),IN,f);
        }
        if (order==POST){
            itterateOrder(root->getLeft(),POST,f);
            itterateOrder(root->getRight(),POST,f);
            (*f)(root);
        }
        if (order==PRE){
            (*f)(root);
            itterateOrder(root->getLeft(),PRE,f);
            itterateOrder(root->getRight(),PRE,f);
        }
    }
    else{
        if (order==IN){
            itterateOrder(root->getLeft(),IN,f,true);
            (*f)(root);
            itterateOrder(root->getRight(),IN,f,true);
        }
        if (order==POST){
            itterateOrder(root->getLeft(),POST,f,true);
            itterateOrder(root->getRight(),POST,f,true);
            (*f)(root);
        }
        if (order==PRE){
            (*f)(root);
            itterateOrder(root->getLeft(),PRE,f,true);
            itterateOrder(root->getRight(),PRE,f,true);
        }
    }
}
/**
 * non-recursive solution
 * O(logk + num)
 * */
template <typename KEY,typename VAL>
DynamicArray<Pair<KEY,VAL>> inOrder_into_array(Node_ptr<KEY,VAL> root,int num, bool reversed = false){
    DynamicArray<Pair<KEY,VAL>> res_array(num);
    DynamicArray<AVL_NODE<KEY,VAL>> node_stack(root->getHeight());
    Node_ptr itt=root;
    while(itt->getLeft()!=nullptr){
        node_stack.push(*itt);
    }
      

        
}
#endif