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
    Node_ptr<KEY,VAL> leftest =tree.select(1);
    int tree_size=root->getRank();
    int index=0;
    DynamicArray<Pair<KEY,VAL>> arr(tree_size);
    reverseClimbTreeFromLeft(leftest,true,true,true,&index,arr,tree_size);    
    return List<Pair<KEY,VAL>>(arr);
}

template <typename KEY,typename VAL>
void reverseClimbTreeFromLeft(std::shared_ptr<AVL_NODE<KEY,VAL>> current,bool goUp,bool goLeft,bool goRight,int *index,DynamicArray<Pair<KEY,VAL>>& arr , int m){
    if (!current|| *index >= m)
    {
        return;
    }
    // go left 
    if (current->getLeft() && goLeft)
    {
        reverseClimbTreeFromLeft(current->getLeft(), false, true, true, index, arr, m);
    }

    if (*index >= m)
    {
        return;
    }

    // save this node
    arr[*index] = Pair(current->getKey(),current->getValue());
    *index += 1;

    // go right 
    if (current->getRight() && goRight)
    {
        reverseClimbTreeFromLeft(current->getRight(), false, true, true, index, arr, m);
    }

    // go up
    if (current->getParent() && goUp)
    {
        // decide if this is the right or left child so we don't return here
        if (current->getKey() > current->getParent()->getKey())
        {
            reverseClimbTreeFromRight(current->getParent(), true, true, false, index, arr, m);
        }
        else
        {
            reverseClimbTreeFromRight(current->getParent(), true, false, true, index, arr, m);
        }
    }

}

template <typename KEY,typename VAL>
void reverseClimbTreeFromRight(std::shared_ptr<AVL_NODE<KEY,VAL>> current,bool goUp,bool goLeft,bool goRight,int *index, DynamicArray<Pair<KEY,VAL>>& arr, int m){

    if (!current|| *index >= m)
    {
        return;
    }
    // go right
    if (current->getRight() && goRight)
    {
        reverseClimbTreeFromRight(current->getRight(), false, true, true, index, arr, m);
    }

    if (*index >= m)
    {
        return;
    }

    // save this node
    arr[*index] = Pair(current->getKey(),current->getValue());
    *index += 1;

    // go left
    if (current->getLeft() && goLeft)
    {
        reverseClimbTreeFromRight(current->getLeft(), false, true, true, index, arr, m);
    }

    // go up
    if (current->getParent() && goUp)
    {
        // decide if this is the right or left child so we don't return here
        if (current->getKey() > current->getParent()->getKey())
        {
            reverseClimbTreeFromRight(current->getParent(), true, true, false, index, arr, m);
        }
        else
        {
            reverseClimbTreeFromRight(current->getParent(), true, false, true, index, arr, m);
        }
    }
}

template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> merge_trees(AVL_Tree<KEY,VAL> tree1,AVL_Tree<KEY,VAL> tree2){
    List<Pair<KEY,VAL>> list1 = TreeToList(tree1);
    List<Pair<KEY,VAL>> list2 = TreeToList(tree2);
    List<Pair<KEY,VAL>> merged_list = mergeOrderedLists(list1,list2);
    return ListToTree(merged_list);
}



#endif