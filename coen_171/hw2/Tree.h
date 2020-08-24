
 
# ifndef TREE_H
# define TREE_H
# include <cstdlib>


template<class T>
class Node {
    T data;
    Node<T> *left;
    Node<T> *right;

public:
    Node(const T &amp);
    void insert(const T &amp);
    bool member(const T &amp) const;
};

//initializing the Node
template<class T>
Node<T>::Node(const T &amp){
    data = amp;
    left = NULL;
    right = NULL;
}


template <class T>
void Node<T>::insert(const T &amp){
    if (amp < data){      //insert to the left if amp is lesser than to current
        if(left == NULL)
            left = new Node<T>(amp);
        else
            left->insert(amp);
    }
    if (amp >= data){     //insert to right if amp is greater than or equal to current
        if(right == NULL)
            right = new Node<T>(amp);
        else right->insert(amp);
    }
}

template <class T>
bool Node<T>::member(const T &amp) const{
    if (amp < data){    //check to left is amp is less than data
        if(left == NULL)
            return false;
        else
            return left->member(amp);
    }
    if (amp > data){    //check to right if amp is greater than current data
        if(right == NULL)
            return false;
        else
            return right->member(amp);
    }
    return true;   //if all else returns do not happen then it is true
}



template<class T>
class Tree {
    Node<T> *root;

public:
    Tree(){root = NULL;};   //setting equal to NULL to avoid a seg fault
    void insert(const T &amp);
    bool member(const T &amp) const;
};

template<class T>
void Tree<T>::insert(const T&amp){
    if(root == NULL)
        root = new Node<T>(amp);   //root no longer null
    else
        root->insert(amp);     //use the roots insert function
}

template<class T>
bool Tree<T>::member(const T &amp) const{
    if(root == NULL)   //if it is equal to null then this wont work
        return false;
    else
        return root->member(amp);   //use the roots member function
}


# endif /* TREE_H */

