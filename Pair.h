#ifndef _PAIR_H
#define _PAIR_H

template <typename KEY, typename VALUE>
class Pair{
    KEY key;
    VALUE value;
    
    public:
    Pair(KEY key,VALUE value):key(key),value(value){};
    KEY getKey(){
        return key;
    }
    VALUE getValue(){
        return value;
    }
    void setKey(KEY& new_key){
        key=new_key;
    }
    void setValue(VALUE& new_value){
        value=new_value;
    }

    
};

#endif