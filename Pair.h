#ifndef _PAIR_H
#define _PAIR_H

template <typename KEY, typename VALUE>
class Pair{
    KEY key;
    VALUE value;
    
    public:
    Pair()=default;
    Pair(KEY key,VALUE value):key(key),value(value){};
    Pair(Pair& to_copy)=default;
    Pair(const Pair& to_copy)=default;
    Pair& operator=(Pair& copy)=default;
    Pair& operator=(const Pair& copy)=default;
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