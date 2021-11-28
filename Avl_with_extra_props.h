
#include "Avl.h"
/**
 * AVL_NODE_WEP - avl node with extra property. the property needs to be
 * such that it can be calculated in O(1) from its children if they have the property.
 * */

template <class KEY,class VAL>
class AVL_NODE_WEP: public AVL_NODE<KEY,VAL>{
    typedef struct std::shared_ptr<AVL_NODE_WEP<KEY,VAL>> Node_wep_ptr;
    Node_wep_ptr min_of_RT;
    Node_wep_ptr max_of_LT;
    public:
    Node__wep_ptr calc_min_of_RT();
    Node_wep_ptr calc_max_of_LT();
    void update_min_of_RT();
    void update_max_of_LT();
};

template <typename KEY,typename VAL>
using Node_wep_ptr=std::shared_ptr<AVL_NODE_WEP<KEY,VAL>>;


