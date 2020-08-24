//#Name: Tanner Kaczmarek


#include <cstdlib>
#include <iostream>
#include "Tree.h"

int main(){
    
    Tree<int> *t;
    t = new Tree<int>();
    
    
    
    t->insert(5);
    t->insert(3);
    t->insert(9);
    t->insert(6);
    t->insert(1);
    t->insert(3);
    
    std::cout << t->member(2) << std::endl;  //0
    std::cout << t->member(5) << std::endl;  //1
    std::cout << t->member(9) << std::endl;  //1
    std::cout << t->member(3) << std::endl;  //1
    std::cout << t->member(7) << std::endl;  //0
    std::cout << t->member(4) << std::endl;  //0
    
}

